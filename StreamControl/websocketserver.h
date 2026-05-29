#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QList>
#include <QByteArray>
#include <QWebSocketServer>
#include <QWebSocket>

class WebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketServer(quint16 port,QObject *parent = nullptr);
    ~WebSocketServer();

    void broadcast(const QString &message);
    void setLastMessage(const QString &message);

signals:
    void closed();

private slots:
    void onNewConnection();
    void processTextMessage(QString message);
    //void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    QString m_lastMessage;
};

#endif // WEBSOCKETSERVER_H
