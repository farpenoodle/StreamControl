#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>
#include <QWebSocketServer>
#include <QWebSocket>
#include <functional>

class WebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketServer(quint16 port,QObject *parent = nullptr);
    ~WebSocketServer();

    void broadcast(const QString &message);
    void setLastMessage(const QString &message);

    // Control auth: secret = base64(sha256(password + salt)), with a fresh salt per password.
    // Control is off when disabled or the password is empty.
    void setAuth(const QString &password, bool enabled);
    void setBatchHandler(std::function<QJsonArray(const QJsonArray&)> handler);

    static QString makeSecret(const QString &password, const QString &salt);
    static QString makeSalt();

    struct ConnectionInfo {
        QWebSocket *socket = nullptr;
        QString address;
        quint16 port = 0;
        QString origin;
        QString resource;
        QDateTime connectedAt;
        bool authed = false;
        int messages = 0;
    };

    QList<ConnectionInfo> connections() const;
    quint16 port() const;
    bool isListening() const;
    void disconnectClient(QWebSocket *socket);

signals:
    void closed();
    void connectionsChanged();

private slots:
    void onNewConnection();
    void processTextMessage(QString message);
    //void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    struct ClientState {
        QByteArray challenge;
        bool authed = false;
        int failures = 0;
        QDateTime connectedAt;
        int messages = 0;
    };

    void sendJson(QWebSocket *client, const QJsonObject &obj);
    void sendError(QWebSocket *client, const QString &error);

    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    QHash<QWebSocket *, ClientState> m_clientStates;
    QString m_lastMessage;
    QString m_password;
    bool m_controlEnabled = false;
    QString m_salt;
    QString m_secret;
    std::function<QJsonArray(const QJsonArray&)> m_batchHandler;
};

#endif // WEBSOCKETSERVER_H
