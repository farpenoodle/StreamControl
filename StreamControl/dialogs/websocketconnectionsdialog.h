#ifndef DIALOG_WEBSOCKETCONNECTIONSDIALOG_H
#define DIALOG_WEBSOCKETCONNECTIONSDIALOG_H

#include <QDialog>
#include <QPointer>

class QLabel;
class QTableWidget;
class QPushButton;
class WebSocketServer;

class WebSocketConnectionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WebSocketConnectionsDialog(QWidget *parent = 0);

    void setServer(WebSocketServer *server);

public slots:
    void refresh();
    void disconnectSelected();
    void selectionChanged();

protected:
    void showEvent(QShowEvent *event) override;

private:
    QPointer<WebSocketServer> wsServer;

    QLabel *statusLabel;
    QTableWidget *table;
    QPushButton *disconnectButton;
};

#endif // DIALOG_WEBSOCKETCONNECTIONSDIALOG_H
