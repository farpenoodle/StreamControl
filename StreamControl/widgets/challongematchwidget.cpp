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
#include <QList>
#include <QComboBox>
#include <QtDebug>
#include <QAuthenticator>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "challongematchwidget.h"

ChallongeMatchWidget::ChallongeMatchWidget(QWidget *parent,
                                           QMap<QString, QObject*>& widgetList,
                                           const QMap<QString, QString>& settings,
                                           QString playerOneWidgetId,
                                           QString playerTwoWidgetId,
                                           QString tournamentStageWidgetId) :
    QWidget(parent), widgetList(widgetList), settings(settings),
    playerOneWidgetId(playerOneWidgetId), playerTwoWidgetId(playerTwoWidgetId),
    tournamentStageWidgetId(tournamentStageWidgetId)
{
    layout = new QGridLayout;
    tournamentsBox = new QComboBox();
    tournamentLabel = new QLabel();
    tournamentCustomLabel = new QLabel();
    tournamentCustomLineEdit = new QLineEdit();
    tournamentFetchButton = new QPushButton();
    matchesBox = new QComboBox();
    matchLabel = new QLabel();
    matchFetchButton = new QPushButton();
    setDataButton = new QPushButton();
    statusLabel = new QLabel();

    tournamentFetchButton->setText("Fetch Tournaments");
    matchFetchButton->setText("Fetch Matches");
    setDataButton->setText("Set Match Details");
    tournamentLabel->setText("Tournament");
    tournamentCustomLabel->setText("or Tournament ID:");
    matchLabel->setText("Match");

    statusLabel->setStyleSheet("QLabel { color : red; }");

    tournamentsBox->addItem("Custom...", "custom"),

    layout->addWidget(tournamentFetchButton, 0, 0,1,2);
    layout->addWidget(matchFetchButton, 0, 2, 1, 2);
    layout->addWidget(tournamentLabel, 1, 0);
    layout->addWidget(tournamentsBox, 1, 1, 1, 3);
    layout->addWidget(tournamentCustomLabel, 2, 0, 1, 1);
    layout->addWidget(tournamentCustomLineEdit, 2, 1, 1, 3);
    layout->addWidget(matchLabel, 3, 0);
    layout->addWidget(matchesBox, 3, 1, 1, 3);

    layout->addWidget(setDataButton, 4, 0, 1, 4);
    layout->addWidget(statusLabel, 5, 0, 1, -1);


    manager = new QNetworkAccessManager;

    connect(tournamentsBox, SIGNAL(currentIndexChanged(int)), this,
            SLOT(updateCustomIdBoxState()));

    connect(tournamentFetchButton, SIGNAL(clicked()), this, SLOT(fetchTournaments()));
    connect(matchFetchButton, SIGNAL(clicked()), this, SLOT(fetchMatches()));
    connect(setDataButton, SIGNAL(clicked()), this, SLOT(setData()));

    this->setLayout(layout);
}

void ChallongeMatchWidget::fetchTournaments()
{
    QString urlString =
        QString("https://api.challonge.com/v1/tournaments.json?state=in_progress");

    QString organization = settings["challonge>organization"];
    if (!organization.isEmpty())
        urlString.append(QString("&subdomain=%1").arg(organization));

    QNetworkRequest request(urlString);

    request.setRawHeader("Authorization", getAuthHeader());

    QNetworkReply *reply = manager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(processTournamentListJson()));
}

void ChallongeMatchWidget::fetchMatches()
{
    QString currentTournamentId;
    int currentIndex = tournamentsBox->currentIndex();

    // If custom is selected...
    if (tournamentsBox->currentIndex() == tournamentsBox->count() - 1)
        currentTournamentId = tournamentCustomLineEdit->text();
    else
        currentTournamentId = tournamentsBox->itemData(currentIndex).toString();

    QString urlString =
        QString("https://api.challonge.com/v1/tournaments/%1.json?include_matches=1&include_participants=1").arg(currentTournamentId);

    QNetworkRequest request(urlString);

    request.setRawHeader("Authorization", getAuthHeader());

    QNetworkReply *reply = manager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(processTournamentJson()));
}

QByteArray ChallongeMatchWidget::getAuthHeader() const
{
    QString concatenated = settings["challonge>username"] + ":" +
                           settings["challonge>apiKey"];
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    return headerData.toLocal8Bit();
}

void ChallongeMatchWidget::processTournamentListJson()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    QString replyData = reply->readAll();

    if (reply->error() != QNetworkReply::NoError)
    {
        statusLabel->setText("Error loading tournament data");
        return;
    }

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
    tournamentsBox->addItem("Custom...", "custom");

    updateCustomIdBoxState();
}

void ChallongeMatchWidget::processTournamentJson()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    QString replyData = reply->readAll();

    if (reply->error() != QNetworkReply::NoError)
    {
        statusLabel->setText("Error loading tournament data");
        return;
    }

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

            QVariantList matchDetails;
            matchDetails.append(tournamentObject["tournament_type"].toString());
            matchDetails.append(tournamentObject["participants_count"].toInt());
            matchDetails.append(match["round"].toInt());
            matchDetails.append(player1Name);
            matchDetails.append(player2Name);
            matchesBox->addItem(str, matchDetails);
        }
    }
}


QString getSingleEliminationMatchPhase(int currentRound, int tournamentEntrants)
{
    QString roundName = "";

    int maxRounds = 0;
    int counter = 1;
    while (counter < tournamentEntrants)
    {
        maxRounds += 1;
        counter *= 2;
    }

    switch (maxRounds - currentRound)
    {
        case 0:
            roundName = "Final";
            break;
        case 1:
            roundName = "Semi-Final";
            break;
        case 2:
            roundName = "Quarter Final";
            break;
        case 3:
            roundName = "Last 16";
            break;
        default:
            roundName = QString("Round %1").arg(currentRound);
    }

    return roundName;
}


// Returns how many rounds there will be in winners bracket in a DE tournament
int getWinnersRounds(int numPlayers)
{
    double participants = numPlayers;
    int matches = 0;
    while (participants > 1)
    {
        participants /= 2;
        matches += 1;
    }

    return matches;
}

// Returns how many rounds there will be in losers bracket in a DE tournament
int getLosersRounds(int numPlayers)
{
    if (numPlayers <= 2) return 0;

    int count = 2;
    int rounds = 2;
    int increment_diff = 2;
    bool will_increment = false;

    count += increment_diff;
    while (count < numPlayers)
    {
        count += increment_diff;
        rounds += 1;
        if (will_increment)
        {
            increment_diff *= 2;
            will_increment = false;
        }
        else
            will_increment = true;
    }
    return rounds;
}


QString getDoubleEliminationMatchPhase(int currentRound, int tournamentEntrants)
{
    int winnersRounds = getWinnersRounds(tournamentEntrants);
    int losersRounds = getLosersRounds(tournamentEntrants);

    int realRound = abs(currentRound);
    QString stage = "";

    QString roundName = QString("Round %1").arg(realRound - 1);

    int roundLimit = currentRound < 0 ? losersRounds : winnersRounds;

    if (currentRound >= 1)
    {
        stage = "Winners ";
        roundName = "Bracket";
    }
    if (currentRound < 0)
    {
        //roundName = QString("Round %1").arg(realRound);
        roundName = "Bracket";
        stage = "Losers ";
    }

    if (realRound == roundLimit - 1)
        roundName = "Semi-Final";
    if (realRound == roundLimit)
        roundName = "Final";
    if (currentRound == roundLimit + 1)
    {
        stage = "";
        roundName = "Grand Final";
    }

    return QString("%1%2").arg(stage, roundName).trimmed();
}



QString getPhase(TournamentType t, int currentRound, int tournamentEntrants)
{
    switch (t)
    {
        case ROUND_ROBIN:
        {
            QString templateString = "Round %1";
            return templateString.arg(currentRound);
            break;
        }
        case SINGLE_ELIMINATION:
        {
            return getSingleEliminationMatchPhase(currentRound, tournamentEntrants);
            break;
        }
        case DOUBLE_ELIMINATION:
        {
            return getDoubleEliminationMatchPhase(currentRound, tournamentEntrants);
            break;
        }
        default:
            return "ok";
    }
}

void ChallongeMatchWidget::setData()
{
    QVariant var = (matchesBox->itemData(matchesBox->currentIndex()));
    QVariantList matchDetails = var.toList();

    if (!matchDetails.empty())
    {
        if (widgetList[playerOneWidgetId] && widgetList[playerTwoWidgetId])
        {
            ///TODO: use a more generic set data method
            ((QLineEdit*)widgetList[playerOneWidgetId])->setText(matchDetails[3].toString());
            ((QLineEdit*)widgetList[playerTwoWidgetId])->setText(matchDetails[4].toString());
        }
        //Also calculate the current tournament stage
        int playerCount = matchDetails[1].toInt();
        int roundNumber = matchDetails[2].toInt();
        QString tournamentTypeString = matchDetails[0].toString();

        TournamentType tournamentType = DOUBLE_ELIMINATION;
        if (tournamentTypeString == "double elimination")
            tournamentType = DOUBLE_ELIMINATION;
        if (tournamentTypeString == "single elimination")
            tournamentType = SINGLE_ELIMINATION;
        if (tournamentTypeString == "round robin")
            tournamentType = ROUND_ROBIN;


        //TODO: Hard-coded for now - externalize the strings
        QString phase = getPhase(tournamentType, roundNumber, playerCount);

        QLineEdit* widget= ((QLineEdit*)widgetList[tournamentStageWidgetId]);
        if (widget) widget->setText(phase);
    }

}

void ChallongeMatchWidget::updateCustomIdBoxState()
{
    // The last entry in the tournaments box should always be the custom option
    bool boxEnabled = (tournamentsBox->currentIndex() == tournamentsBox->count() - 1);

    tournamentCustomLineEdit->setEnabled(boxEnabled);
}
