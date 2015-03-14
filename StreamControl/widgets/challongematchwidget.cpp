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
#include <QFile>

#include "challongematchwidget.h"

ChallongeMatchWidget::ChallongeMatchWidget(QWidget *parent,
                                           QMap<QString, QObject*>& widgetList,
                                           const QMap<QString, QString>& settings,
                                           QString playerOneWidgetId,
                                           QString playerTwoWidgetId,
                                           QString tournamentStageWidgetId,
                                           QString bracketWidgetId) :
    QWidget(parent), widgetList(widgetList), settings(settings),
    playerOneWidgetId(playerOneWidgetId), playerTwoWidgetId(playerTwoWidgetId),
    tournamentStageWidgetId(tournamentStageWidgetId), bracketWidgetId(bracketWidgetId)
{
    layout = new QGridLayout;
    tournamentsBox = new QComboBox();
    tournamentLabel = new QLabel();
    tournamentCustomLabel = new QLabel();
    tournamentCustomLineEdit = new QLineEdit();
    tournamentFetchButton = new QPushButton();
    matchesBox = new QComboBox();
    currentTournamentLabel = new QLabel();
    matchLabel = new QLabel();
    matchFetchButton = new QPushButton();
    setMatchDataButton = new QPushButton();
    setBracketDataButton = new QPushButton();
    statusLabel = new QLabel();

    QFrame* frame = new QFrame();
    frame->setFrameStyle(QFrame::Panel);
    frame->setFrameShadow(QFrame::Sunken);

    tournamentFetchButton->setText("Fetch");
    matchFetchButton->setText("Load Tournament Data/Matches");
    setMatchDataButton->setText("Set Match Details");
    setBracketDataButton->setText("Set Bracket Data");
    tournamentLabel->setText("Tournament");
    currentTournamentLabel->setText("Current Tournament: (none)");
    tournamentCustomLabel->setText("or Tournament ID:");
    matchLabel->setText("Match");

    statusLabel->setStyleSheet("QLabel { color : red; }");

    tournamentsBox->addItem("Custom...", "custom"),

    layout->addWidget(tournamentLabel, 0, 0, 1, 1);
    layout->addWidget(tournamentsBox, 0, 1, 1, 2);
    layout->addWidget(tournamentFetchButton, 0, 3, 1, 1);

    layout->addWidget(tournamentCustomLabel, 1, 0, 1, 1);
    layout->addWidget(tournamentCustomLineEdit, 1, 1, 1, 3);

    layout->addWidget(matchFetchButton, 2, 0, 1, -1);

    layout->addWidget(frame, 3, 0, 1, -1);

    QGridLayout* frameLayout = new QGridLayout;
    frameLayout->addWidget(currentTournamentLabel, 0, 0, 1, -1);
    frameLayout->addWidget(matchLabel, 1, 0, 1, 1);
    frameLayout->addWidget(matchesBox, 1, 1, 1, 1);
    frameLayout->addWidget(setMatchDataButton, 2, 0, 1, -1);
    frameLayout->addWidget(setBracketDataButton, 3, 0, 1, -1);
    frame->setLayout(frameLayout);

    layout->addWidget(statusLabel, 4, 0, 1, -1);


    manager = new QNetworkAccessManager;

    connect(tournamentsBox, SIGNAL(currentIndexChanged(int)), this,
            SLOT(updateCustomIdBoxState()));

    connect(tournamentFetchButton, SIGNAL(clicked()), this, SLOT(fetchTournaments()));
    connect(matchFetchButton, SIGNAL(clicked()), this, SLOT(fetchMatches()));
    connect(setMatchDataButton, SIGNAL(clicked()), this, SLOT(setMatchData()));
    connect(setBracketDataButton, SIGNAL(clicked()), this, SLOT(setBracketData()));

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

    currentTournamentJson = QJsonDocument::fromJson(replyData.toUtf8());
    const QJsonObject tournamentObject = currentTournamentJson.object()["tournament"].toObject();

    QString tournamentName = tournamentObject["name"].toString();
    currentTournamentLabel->setText(QString("Current Tournament: %1").arg(tournamentName));

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

void ChallongeMatchWidget::setBracketData()
{
    QFile bracketFile(settings["outputPath"] + "bracket.json");
    bracketFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    bracketFile.write(currentTournamentJson.toJson());
    bracketFile.close();
}

void ChallongeMatchWidget::setMatchData()
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


        QLineEdit* tournamentStageWidget = (QLineEdit*)widgetList[tournamentStageWidgetId];
        if (tournamentStageWidget)
        {
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
            tournamentStageWidget->setText(phase);
        }

        QLineEdit* bracketWidget = (QLineEdit*)widgetList[bracketWidgetId];
        if (bracketWidget)
        {
            bracketWidget->setText(currentTournamentJson.object()["tournament"].toObject()["url"].toString());
        }

    }

}

void ChallongeMatchWidget::updateCustomIdBoxState()
{
    // The last entry in the tournaments box should always be the custom option
    bool boxEnabled = (tournamentsBox->currentIndex() == tournamentsBox->count() - 1);

    tournamentCustomLineEdit->setEnabled(boxEnabled);
}
