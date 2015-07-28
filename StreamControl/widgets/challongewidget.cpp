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
#include <QAuthenticator>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

#include "challongewidget.h"

static QString GRAND_FINAL = "grandFinal";
static QString GRAND_FINAL_RESET = "grandFinalReset";
static QString WINNERS_FINAL = "winnersFinal";
static QString WINNERS_SEMI_FINAL = "winnersSemiFinal";
static QString WINNERS_QUARTER_FINAL = "winnersQuarterFinal";
static QString LOSERS_FINAL = "losersFinal";
static QString LOSERS_SEMI_FINAL = "losersSemiFinal";
static QString TOP_6_LOSERS = "top6Losers";
static QString TOP_8_LOSERS = "top8Losers";
static QString TOP_12_LOSERS = "top12Losers";
static QString TOP_16_LOSERS = "top16Losers";

ChallongeWidget::ChallongeWidget(QWidget *parent) : QWidget(parent) {};

ChallongeWidgetImpl::ChallongeWidgetImpl(QWidget *parent,
                                           QMap<QString, QObject*>& widgetList,
                                           const QMap<QString, QString>& settings,
                                           QString playerOneWidgetId,
                                           QString playerTwoWidgetId,
                                           QString tournamentStageWidgetId,
                                           QString bracketWidgetId,
                                           QString outputFileName,
                                           QMap<QString, QStringList> bracketWidgets) :
    ChallongeWidget(parent), widgetList(widgetList), settings(settings),
    playerOneWidgetId(playerOneWidgetId), playerTwoWidgetId(playerTwoWidgetId),
    tournamentStageWidgetId(tournamentStageWidgetId), bracketWidgetId(bracketWidgetId),
    outputFileName(outputFileName), bracketWidgets(bracketWidgets)
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
    matchFetchButton->setText("Load Tournament Data");
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

    setUpTournamentNodes();
}

void ChallongeWidgetImpl::setUpTournamentNodes()
{
    // Set up top 16 structure for a double elimination tournament
    // Winners bracket prerequisite matches are commented out as there's no
    // need to traverse backwards from losers to winners, they are already covered
    doubleElimNodes.insert("grandFinal", TournamentTreeNode("winnersFinal", "losersFinal"));
    doubleElimNodes.insert("winnersFinal", TournamentTreeNode("winnersSemiFinal1", "winnersSemiFinal2"));

    doubleElimNodes.insert("winnersSemiFinal1", TournamentTreeNode("winnersQuarterFinal1", "winnersQuarterFinal2"));
    doubleElimNodes.insert("winnersSemiFinal2", TournamentTreeNode("winnersQuarterFinal3", "winnersQuarterFinal4"));

    doubleElimNodes.insert("winnersQuarterFinal1", TournamentTreeNode("", ""));
    doubleElimNodes.insert("winnersQuarterFinal2", TournamentTreeNode("", ""));
    doubleElimNodes.insert("winnersQuarterFinal3", TournamentTreeNode("", ""));
    doubleElimNodes.insert("winnersQuarterFinal4", TournamentTreeNode("", ""));

    doubleElimNodes.insert("losersFinal", TournamentTreeNode(""/*"winnersFinal"*/, "losersSemiFinal"));

    doubleElimNodes.insert("losersSemiFinal", TournamentTreeNode("top6Losers1", "top6Losers2"));

    doubleElimNodes.insert("top6Losers1", TournamentTreeNode("" /*winnersSemiFinal1*/, "top8Losers1"));
    doubleElimNodes.insert("top6Losers2", TournamentTreeNode("" /*winnersSemiFinal2*/, "top8Losers2"));

    doubleElimNodes.insert("top8Losers1", TournamentTreeNode("top12Losers1", "top12Losers2"));
    doubleElimNodes.insert("top8Losers2", TournamentTreeNode("top12Losers3", "top12Losers4"));

    doubleElimNodes.insert("top12Losers1", TournamentTreeNode("" /*winnersQuarterFinal1*/, "top16Losers1"));
    doubleElimNodes.insert("top12Losers2", TournamentTreeNode("" /*winnersQuarterFinal2*/, "top16Losers2"));
    doubleElimNodes.insert("top12Losers3", TournamentTreeNode("" /*winnersQuarterFinal3*/, "top16Losers3"));
    doubleElimNodes.insert("top12Losers4", TournamentTreeNode("" /*winnersQuarterFinal4*/, "top16Losers4"));

    doubleElimNodes.insert("top16Losers1", TournamentTreeNode("", ""));
    doubleElimNodes.insert("top16Losers2", TournamentTreeNode("", ""));
    doubleElimNodes.insert("top16Losers3", TournamentTreeNode("", ""));
    doubleElimNodes.insert("top16Losers4", TournamentTreeNode("", ""));
}

void ChallongeWidgetImpl::fetchTournaments()
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

void ChallongeWidgetImpl::fetchMatches()
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

QByteArray ChallongeWidgetImpl::getAuthHeader() const
{
    QString concatenated = settings["challonge>username"] + ":" +
                           settings["challonge>apiKey"];
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    return headerData.toLocal8Bit();
}

void ChallongeWidgetImpl::processTournamentListJson()
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

void ChallongeWidgetImpl::processTournamentJson()
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

    matchesBox->clear();
    //Loop through the players and add them to an id->name map
    playerIdMap.clear();
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

// Converts the tournament round of a single elimination tournament to a string
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

// Converts the tournament round of a double elimination tournament to a string
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
        roundName = "Bracket";
        stage = "Losers ";
    }

    if (currentRound < 0 && realRound == roundLimit - 3)
    {
        stage = "";
        roundName = "Top 8 Losers";
    }
    if (realRound == roundLimit - 2)
        roundName = "Quarter Final";
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
    }
}

QJsonArray getMatchesForRound(const QJsonArray& matches, int round)
{
    QJsonArray returnValue;
    for (QJsonArray::const_iterator iter = matches.constBegin();
         iter != matches.constEnd(); iter++)
    {
        const QJsonObject match = iter->toObject()["match"].toObject();

        if (match["round"] == round)
        {
            // if this match is a grand final reset then make sure it's last
            // in the returned array
            // The grand final, unlike the reset, has both previous matches
            // as the same id
            bool isGrandFinal = match["player1_prereq_match_id"].toInt() !=
                                match["player2_prereq_match_id"].toInt();

            isGrandFinal ? returnValue.prepend(match) : returnValue.append(match);
        }
    }
    return returnValue;
}

QJsonObject getMatchById(const QJsonArray& matches, QString matchId)
{
    for (QJsonArray::const_iterator iter = matches.constBegin();
         iter != matches.constEnd(); iter++)
    {
        const QJsonObject match = iter->toObject()["match"].toObject();

        if (QString::number(match["id"].toInt()) == matchId)
            return match;
    }

    // TODO: throw something here instead
    return QJsonObject();
}

QJsonArray getPrerequisiteMatches(const QJsonArray& allMatches,
                                  const QJsonObject& parentMatch)
{
    QJsonArray returnValue;

    const QString prerequisiteMatchIdString = parentMatch["prerequisite_match_ids_csv"].toString();
    QStringList prerequisiteMatchIds = prerequisiteMatchIdString.split(',');

    // ...and fetch the winners/losers final match objects from them

    for (QStringList::const_iterator matchIter = prerequisiteMatchIds.constBegin();
         matchIter != prerequisiteMatchIds.constEnd(); matchIter++)
    {
        const QJsonObject& match = getMatchById(allMatches, *matchIter);
        if ((parentMatch["round"].toInt() > 0 && match["round"].toInt() > 0) ||
            (parentMatch["round"].toInt() < 0 && match["round"].toInt() < 0) )
        {
            returnValue.append(match);
        }
    }

    return returnValue;
}


void fillBracketWithMatch(const QStringList boxes, const QJsonObject& match,
                          const QMap<int, QString>& playerIdMap,
                          QMap<QString, QObject*>& widgetList)
{
    const int playerOneId = match["player1_id"].toInt();
    const int playerTwoId = match["player2_id"].toInt();

    // Get competitor's names
    ((QLineEdit*)widgetList[boxes[0]])->setText( playerIdMap[playerOneId] );
    ((QLineEdit*)widgetList[boxes[2]])->setText( playerIdMap[playerTwoId] );

    const QStringList scores = match["scores_csv"].toString().split("-");
    if (scores.size() == 2)
    {
        ((QLineEdit*)widgetList[boxes[1]])->setText(scores[0]);
        ((QLineEdit*)widgetList[boxes[3]])->setText(scores[1]);
    }
}

void ChallongeWidgetImpl::clearBracketWidgets()
{
    foreach(const QStringList& widgets, bracketWidgets)
    {
        foreach(const QString& widgetId, widgets)
        {
            ((QLineEdit*)widgetList[widgetId])->setText( "" );
        }
    }
}

void ChallongeWidgetImpl::fillWidget(const QJsonArray& matches, QString matchId, const QJsonObject& match)
{
    if (!bracketWidgets.contains(matchId)) return;

    //fill match
    fillBracketWithMatch(bracketWidgets[matchId], match, playerIdMap, widgetList);

    //get tournament node
    const TournamentTreeNode& node = doubleElimNodes.value(matchId);

    if (!node.child1Id.isEmpty())
    {
        QString previousMatch = QString::number(match["player1_prereq_match_id"].toInt());
        if (!previousMatch.isEmpty())
        {
            const QJsonObject& childMatch = getMatchById(matches, previousMatch);
            fillWidget(matches, node.child1Id, childMatch);
        }
    }

    if (!node.child2Id.isEmpty())
    {
        QString previousMatch = QString::number(match["player2_prereq_match_id"].toInt());
        if (!previousMatch.isEmpty())
        {
            const QJsonObject& childMatch = getMatchById(matches, previousMatch);
            fillWidget(matches, node.child2Id, childMatch);
        }
    }
}

void ChallongeWidgetImpl::writeBracketToFile()
{
    QFile bracketFile(settings["outputPath"] + outputFileName);
    bracketFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    bracketFile.write(currentTournamentJson.toJson());
    bracketFile.close();
}

void ChallongeWidgetImpl::fillBracketWidgets()
{
    clearBracketWidgets();

    // Work backwards from grand finals
    const QJsonObject tournamentObject = currentTournamentJson.object()["tournament"].toObject();
    const QJsonArray participants = tournamentObject["participants"].toArray();
    const QJsonArray matches = tournamentObject["matches"].toArray();

    // The grand final is the round after winners final
    const int grandFinalRound = getWinnersRounds(participants.size()) + 1;

    // This should produce two matches - the first one being the initial match,
    // the second the reset
    const QJsonArray grandFinalMatches = getMatchesForRound(matches,
                                                            grandFinalRound);

    if (grandFinalMatches.size() == 2)
    {
        const QJsonObject& grandFinalResetMatch = grandFinalMatches.last().toObject();
        fillBracketWithMatch(bracketWidgets["grandFinalReset"], grandFinalResetMatch, playerIdMap, widgetList);
    }

    const QJsonObject& grandFinalMatch = grandFinalMatches.first().toObject();
    fillWidget(matches, "grandFinal", grandFinalMatch);
}

void ChallongeWidgetImpl::setBracketData()
{
    if (outputFileName.isEmpty())
        fillBracketWidgets();
    else
        writeBracketToFile();
}

void ChallongeWidgetImpl::setMatchData()
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

void ChallongeWidgetImpl::updateCustomIdBoxState()
{
    // The last entry in the tournaments box should always be the custom option
    bool boxEnabled = (tournamentsBox->currentIndex() == tournamentsBox->count() - 1);

    tournamentCustomLineEdit->setEnabled(boxEnabled);
}
