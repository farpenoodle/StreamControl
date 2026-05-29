#include "websocketserver.h"
#include <QDebug>

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

void WebSocketServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();
    connect(pSocket, &QWebSocket::textMessageReceived, this, &WebSocketServer::processTextMessage);
    //connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &WebSocketServer::socketDisconnected);

    m_clients << pSocket;

    if (!m_lastMessage.isEmpty()) {
        pSocket->sendTextMessage(m_lastMessage);
    }

    qDebug() << "Client connected";
}

void WebSocketServer::processTextMessage(QString message)
{
    Q_UNUSED(message);
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
        pClient->deleteLater();
        qDebug() << "Client disconnected";
    }
}
