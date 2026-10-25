#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>

#include "../websocketserver.h"
#include "websocketconnectionsdialog.h"

enum Column {
    ColAddress,
    ColPort,
    ColOrigin,
    ColPath,
    ColConnected,
    ColAuthed,
    ColMessages,
    ColCount
};

WebSocketConnectionsDialog::WebSocketConnectionsDialog(QWidget *parent)
    : QDialog(parent)
{
    statusLabel = new QLabel;

    table = new QTableWidget(0, ColCount);
    table->setHorizontalHeaderLabels(QStringList()
                                     << tr("Address") << tr("Port") << tr("Origin") << tr("Path")
                                     << tr("Connected") << tr("Control auth") << tr("Messages"));
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setStretchLastSection(true);

    disconnectButton = new QPushButton(tr("Disconnect"));
    disconnectButton->setEnabled(false);
    QPushButton *refreshButton = new QPushButton(tr("Refresh"));
    QPushButton *closeButton = new QPushButton(tr("Close"));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(disconnectButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(refreshButton);
    buttonLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(table);
    mainLayout->addLayout(buttonLayout);

    connect(disconnectButton, SIGNAL(clicked()), this, SLOT(disconnectSelected()));
    connect(refreshButton, SIGNAL(clicked()), this, SLOT(refresh()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(table, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));

    setLayout(mainLayout);
    resize(700, 300);

    setWindowTitle(tr("WebSocket Connections"));
}

void WebSocketConnectionsDialog::setServer(WebSocketServer *server)
{
    if (wsServer == server)
        return;

    if (wsServer)
        disconnect(wsServer, nullptr, this, nullptr);

    wsServer = server;

    if (wsServer)
        connect(wsServer, &WebSocketServer::connectionsChanged, this, &WebSocketConnectionsDialog::refresh);

    refresh();
}

void WebSocketConnectionsDialog::showEvent(QShowEvent *event)
{
    refresh();
    QDialog::showEvent(event);
}

void WebSocketConnectionsDialog::refresh()
{
    // the server signals on every message, so don't rebuild while nobody is looking
    if (!isVisible())
        return;

    QWebSocket *selected = nullptr;
    QList<QTableWidgetItem*> selectedItems = table->selectedItems();
    if (!selectedItems.isEmpty())
        selected = table->item(selectedItems.first()->row(), ColAddress)->data(Qt::UserRole).value<QWebSocket*>();

    table->setRowCount(0);

    if (!wsServer) {
        statusLabel->setText(tr("WebSocket server is not enabled. Enable it in Configuration."));
        selectionChanged();
        return;
    }

    QList<WebSocketServer::ConnectionInfo> connections = wsServer->connections();

    if (wsServer->isListening()) {
        statusLabel->setText(tr("Listening on port %1 - %n connection(s)", "", connections.size())
                             .arg(wsServer->port()));
    } else {
        statusLabel->setText(tr("WebSocket server is not listening (is the port already in use?)"));
    }

    table->setRowCount(connections.size());
    for (int row = 0; row < connections.size(); row++) {
        const WebSocketServer::ConnectionInfo &info = connections[row];

        QTableWidgetItem *addressItem = new QTableWidgetItem(info.address);
        addressItem->setData(Qt::UserRole, QVariant::fromValue(info.socket));
        table->setItem(row, ColAddress, addressItem);
        table->setItem(row, ColPort, new QTableWidgetItem(QString::number(info.port)));
        table->setItem(row, ColOrigin, new QTableWidgetItem(info.origin));
        table->setItem(row, ColPath, new QTableWidgetItem(info.resource));
        table->setItem(row, ColConnected, new QTableWidgetItem(info.connectedAt.toString("HH:mm:ss")));
        table->setItem(row, ColAuthed, new QTableWidgetItem(info.authed ? tr("Yes") : tr("No")));
        table->setItem(row, ColMessages, new QTableWidgetItem(QString::number(info.messages)));

        if (info.socket == selected)
            table->selectRow(row);
    }

    selectionChanged();
}

void WebSocketConnectionsDialog::selectionChanged()
{
    disconnectButton->setEnabled(wsServer && !table->selectedItems().isEmpty());
}

void WebSocketConnectionsDialog::disconnectSelected()
{
    QList<QTableWidgetItem*> selectedItems = table->selectedItems();
    if (!wsServer || selectedItems.isEmpty())
        return;

    QWebSocket *socket = table->item(selectedItems.first()->row(), ColAddress)->data(Qt::UserRole).value<QWebSocket*>();
    wsServer->disconnectClient(socket);
}
