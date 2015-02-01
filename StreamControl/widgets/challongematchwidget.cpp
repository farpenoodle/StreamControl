/**********************************************************************************

Copyright (c) 2015, Antony Clarke
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

**********************************************************************************/

#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QStringList>
#include <QComboBox>
#include <QtDebug>
#include <QAuthenticator>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "widgets/challongematchwidget.h"

ChallongeMatchWidget::ChallongeMatchWidget(QWidget *parent,
                                           QMap<QString, QObject*>& widgetList,
                                           QString playerOneWidgetId,
                                           QString playerTwoWidgetId) :
    QWidget(parent), widgetList(widgetList), playerOneWidgetId(playerOneWidgetId),
    playerTwoWidgetId(playerTwoWidgetId)
{
    layout = new QGridLayout;
    tournamentsBox = new QComboBox();
    tournamentLabel = new QLabel();
    tournamentFetchButton = new QPushButton();
    matchesBox = new QComboBox();
    matchLabel = new QLabel();
    matchFetchButton = new QPushButton();
    setDataButton = new QPushButton();

    tournamentFetchButton->setText("Fetch Tournaments");
    matchFetchButton->setText("Fetch Matches");
    setDataButton->setText("Set Match Details");
    tournamentLabel->setText("Tournament");
    matchLabel->setText("Match");

    layout->addWidget(tournamentFetchButton,0, 0,1,2);
    layout->addWidget(matchFetchButton,0,2,1,2);

    layout->addWidget(tournamentLabel,1,0);
    layout->addWidget(matchLabel,2,0);
    layout->addWidget(tournamentsBox,1,1,1,3);
    layout->addWidget(matchesBox,2,1,1,3);

    layout->addWidget(setDataButton,3,0, 1, 4);


    manager = new QNetworkAccessManager;

    connect(tournamentFetchButton, SIGNAL(clicked()), this, SLOT(fetchTournaments()));
    connect(matchFetchButton, SIGNAL(clicked()), this, SLOT(fetchMatches()));
    connect(setDataButton, SIGNAL(clicked()), this, SLOT(setData()));

    this->setLayout(layout);
}

void ChallongeMatchWidget::fetchTournaments()
{
    QNetworkRequest request(QUrl("https://api.challonge.com/v1/tournaments.json?state=in_progress"));

    request.setRawHeader("Authorization", getAuthHeader());

    QNetworkReply *reply = manager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(processTournamentListJson()));
}

void ChallongeMatchWidget::fetchMatches()
{
    QString currentTournamentId =
        tournamentsBox->itemData(tournamentsBox->currentIndex()).toString();

    QUrl urlString = QString("https://api.challonge.com/v1/tournaments/%1.json?include_matches=1&include_participants=1").arg(currentTournamentId);


    QNetworkRequest request(urlString);

    request.setRawHeader("Authorization", getAuthHeader());

    QNetworkReply *reply = manager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(processTournamentJson()));
}

QByteArray ChallongeMatchWidget::getAuthHeader() const
{
    QString concatenated = "";
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    return headerData.toLocal8Bit();
}

void ChallongeMatchWidget::processTournamentListJson()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    QString replyData = reply->readAll();

    QJsonDocument response = QJsonDocument::fromJson(replyData.toUtf8());
    QJsonArray tournamentsArray = response.array();

    tournamentsBox->clear();
    matchesBox->clear();

    for (QJsonArray::const_iterator iter = tournamentsArray.constBegin();
         iter != tournamentsArray.constEnd(); iter++)
    {
        QJsonObject tournamentRecord = iter->toObject();
        QJsonObject tournamentObject = tournamentRecord["tournament"].toObject();
        tournamentsBox->addItem(tournamentObject["name"].toString(),
                                QString::number(tournamentObject["id"].toInt()));
    }
}

void ChallongeMatchWidget::processTournamentJson()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    QString replyData = reply->readAll();


    const QJsonDocument response = QJsonDocument::fromJson(replyData.toUtf8());
    const QJsonObject tournamentObject = response.object()["tournament"].toObject();

    QJsonArray participants = tournamentObject["participants"].toArray();
    QJsonArray matches = tournamentObject["matches"].toArray();

    QMap<int, QString> playerIdMap;

    matchesBox->clear();
    //Loop through the players and add them to an id->name map
    for (QJsonArray::const_iterator iter = participants.constBegin();
         iter != participants.constEnd(); iter++)
    {
        QJsonObject participant = iter->toObject()["participant"].toObject();
        playerIdMap.insert(participant["id"].toInt(),
                           participant["name"].toString());
    }

    for (QJsonArray::const_iterator iter = matches.constBegin();
         iter != matches.constEnd(); iter++)
    {
        QJsonObject match = iter->toObject()["match"].toObject();

        if (match["state"].toString() == "open")
        {
            QString player1Name = playerIdMap.value(match["player1_id"].toInt());
            QString player2Name = playerIdMap.value(match["player2_id"].toInt());

            QString str = QString("%1 vs %2").arg(player1Name, player2Name);

            QStringList playerNames;
            playerNames.append(player1Name);
            playerNames.append(player2Name);
            matchesBox->addItem(str, playerNames);
        }
    }
}

void ChallongeMatchWidget::setData()
{
    QVariant var = (matchesBox->itemData(matchesBox->currentIndex()));
    QStringList playerNames = var.toStringList();

    if (!playerNames.empty())
    {
        if (widgetList[playerOneWidgetId] && widgetList[playerTwoWidgetId])
        {
            ///TODO: use a more generic set data method
            ((QLineEdit*)widgetList[playerOneWidgetId])->setText(playerNames[0]);
            ((QLineEdit*)widgetList[playerTwoWidgetId])->setText(playerNames[1]);
        }
    }
}
