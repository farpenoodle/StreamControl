#include "websocketserver.h"
#include <QDebug>
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QJsonDocument>

static const int maxAuthFailures = 5;

static QByteArray randomBytes(int count)
{
    QByteArray bytes(count, Qt::Uninitialized);
    QRandomGenerator *rng = QRandomGenerator::system();
    for (int i = 0; i < count; i++) {
        bytes[i] = static_cast<char>(rng->bounded(256));
    }
    return bytes;
}

static QByteArray sha256Base64(const QByteArray &data)
{
    return QCryptographicHash::hash(data, QCryptographicHash::Sha256).toBase64();
}

static bool constantTimeEquals(const QByteArray &a, const QByteArray &b)
{
    if (a.size() != b.size())
        return false;
    unsigned char diff = 0;
    for (int i = 0; i < a.size(); i++) {
        diff |= static_cast<unsigned char>(a[i] ^ b[i]);
    }
    return diff == 0;
}

WebSocketServer::WebSocketServer(quint16 port, QObject *parent)
    : QObject{parent},
      m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Streamcontrol Socket Server"),
                                              QWebSocketServer::NonSecureMode, this))
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        qDebug() << "Listening on " << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &WebSocketServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WebSocketServer::closed);
    }
}

WebSocketServer::~WebSocketServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

QString WebSocketServer::makeSecret(const QString &password, const QString &salt)
{
    return QString::fromLatin1(sha256Base64(password.toUtf8() + salt.toUtf8()));
}

QString WebSocketServer::makeSalt()
{
    return QString::fromLatin1(randomBytes(16).toBase64());
}

void WebSocketServer::setAuth(const QString &password, bool enabled)
{
    if (password == m_password && enabled == m_controlEnabled)
        return;

    m_password = password;
    m_controlEnabled = enabled;
    m_salt = makeSalt();
    m_secret = (enabled && !password.isEmpty()) ? makeSecret(password, m_salt) : QString();

    // credentials changed, so every escalated connection has to authenticate again
    for (ClientState &state : m_clientStates) {
        state.authed = false;
        state.challenge.clear();
    }
    emit connectionsChanged();
}

QList<WebSocketServer::ConnectionInfo> WebSocketServer::connections() const
{
    QList<ConnectionInfo> list;
    for (QWebSocket *pClient : m_clients) {
        const ClientState state = m_clientStates.value(pClient);
        ConnectionInfo info;
        info.socket = pClient;
        info.address = pClient->peerAddress().toString();
        info.port = pClient->peerPort();
        info.origin = pClient->origin();
        info.resource = pClient->requestUrl().path();
        info.connectedAt = state.connectedAt;
        info.authed = state.authed;
        info.messages = state.messages;
        list << info;
    }
    return list;
}

quint16 WebSocketServer::port() const
{
    return m_pWebSocketServer->serverPort();
}

bool WebSocketServer::isListening() const
{
    return m_pWebSocketServer->isListening();
}

void WebSocketServer::disconnectClient(QWebSocket *socket)
{
    if (m_clients.contains(socket)) {
        socket->close(QWebSocketProtocol::CloseCodeNormal, "disconnected by StreamControl");
    }
}

void WebSocketServer::setBatchHandler(std::function<QJsonArray(const QJsonArray&)> handler)
{
    m_batchHandler = handler;
}

void WebSocketServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();
    connect(pSocket, &QWebSocket::textMessageReceived, this, &WebSocketServer::processTextMessage);
    //connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &WebSocketServer::socketDisconnected);

    m_clients << pSocket;
    ClientState state;
    state.connectedAt = QDateTime::currentDateTime();
    m_clientStates.insert(pSocket, state);

    if (!m_lastMessage.isEmpty()) {
        pSocket->sendTextMessage(m_lastMessage);
    }

    qDebug() << "Client connected";
    emit connectionsChanged();
}

void WebSocketServer::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (!pClient || !m_clientStates.contains(pClient))
        return;

    m_clientStates[pClient].messages++;
    emit connectionsChanged();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8(), &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        sendError(pClient, "invalid JSON message");
        return;
    }

    QJsonObject msg = doc.object();
    QString op = msg["op"].toString();
    ClientState &state = m_clientStates[pClient];

    if (op == "authRequest") {
        if (m_secret.isEmpty()) {
            sendError(pClient, "remote control is disabled");
            return;
        }
        state.challenge = randomBytes(32).toBase64();

        QJsonObject reply;
        reply["op"] = "authChallenge";
        reply["salt"] = m_salt;
        reply["challenge"] = QString::fromLatin1(state.challenge);
        sendJson(pClient, reply);

    } else if (op == "auth") {
        QJsonObject reply;
        reply["op"] = "authResult";

        if (m_secret.isEmpty() || state.challenge.isEmpty()) {
            reply["ok"] = false;
            reply["error"] = m_secret.isEmpty() ? "remote control is disabled"
                                                : "no challenge issued; send authRequest first";
            sendJson(pClient, reply);
            return;
        }

        QByteArray expected = sha256Base64(m_secret.toUtf8() + state.challenge);
        QByteArray given = msg["auth"].toString().toLatin1();
        state.challenge.clear(); // single use

        if (constantTimeEquals(expected, given)) {
            state.authed = true;
            state.failures = 0;
            reply["ok"] = true;
            sendJson(pClient, reply);
            qDebug() << "Client authenticated";
            emit connectionsChanged();
        } else {
            state.authed = false;
            state.failures++;
            reply["ok"] = false;
            reply["error"] = "authentication failed";
            sendJson(pClient, reply);
            emit connectionsChanged();
            if (state.failures >= maxAuthFailures) {
                qDebug() << "Closing client after too many auth failures";
                pClient->close(QWebSocketProtocol::CloseCodePolicyViolated, "too many authentication failures");
            }
        }

    } else if (op == "batch") {
        if (!state.authed) {
            sendError(pClient, "not authenticated");
            return;
        }
        if (!msg["actions"].isArray()) {
            sendError(pClient, "batch requires an 'actions' array");
            return;
        }

        QJsonArray results;
        if (m_batchHandler) {
            results = m_batchHandler(msg["actions"].toArray());
        }

        // the handler may have triggered a save, which can't remove clients, but check anyway
        if (!m_clientStates.contains(pClient))
            return;

        QJsonObject reply;
        reply["op"] = "batchResult";
        if (msg.contains("id"))
            reply["id"] = msg["id"];
        reply["results"] = results;
        sendJson(pClient, reply);

    } else {
        sendError(pClient, "unknown op '" + op + "'");
    }
}

void WebSocketServer::sendJson(QWebSocket *client, const QJsonObject &obj)
{
    client->sendTextMessage(QString::fromUtf8(QJsonDocument(obj).toJson(QJsonDocument::Compact)));
}

void WebSocketServer::sendError(QWebSocket *client, const QString &error)
{
    QJsonObject reply;
    reply["op"] = "error";
    reply["error"] = error;
    sendJson(client, reply);
}

void WebSocketServer::broadcast(const QString &message)
{
    m_lastMessage = message;
    for (QWebSocket *pClient : std::as_const(m_clients)) {
        pClient->sendTextMessage(message);
    }
}

void WebSocketServer::setLastMessage(const QString &message)
{
    m_lastMessage = message;
}

void WebSocketServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {
        m_clients.removeAll(pClient);
        m_clientStates.remove(pClient);
        pClient->deleteLater();
        qDebug() << "Client disconnected";
        emit connectionsChanged();
    }
}
