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
#include <QLabel>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QList>
#include <QComboBox>
#include <QAuthenticator>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "challongewidget.h"

QString getPhase(TournamentType t, int currentRound, int tournamentEntrants);

ChallongeWidget::ChallongeWidget(QWidget *parent,
                                 QMap<QString, QObject*>& widgetList,
                                 const QMap<QString, QString>& settings,
                                 QString playerOneWidgetId,
                                 QString playerTwoWidgetId,
                                 QString tournamentStageWidgetId,
                                 QString bracketWidgetId,
                                 QString outputFileName,
                                 QMap<QString, QStringList> bracketWidgets) :
    ProviderWidget(parent, widgetList, settings, playerOneWidgetId, playerTwoWidgetId,
                   tournamentStageWidgetId, bracketWidgetId, outputFileName, bracketWidgets)
{
    manager = new QNetworkAccessManager;
};

void ChallongeWidget::fetchTournaments()
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

void ChallongeWidget::fetchMatches()
{
    QString currentTournamentId;
    int currentIndex = tournamentsBox->currentIndex();

    // If custom is selected...
    if (tournamentsBox->currentIndex() == tournamentsBox->count() - 1)
        currentTournamentId = tournamentCustomLineEdit->text();
    else
        currentTournamentId = tournamentsBox->itemData(currentIndex).toString();

    const QString urlString =
        QString("https://api.challonge.com/v1/tournaments/%1.json?include_matches=1&include_participants=1").arg(currentTournamentId);

    QNetworkRequest request(urlString);

    request.setRawHeader("Authorization", getAuthHeader());

    QNetworkReply *reply = manager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(processTournamentJson()));
}

QByteArray ChallongeWidget::getAuthHeader() const
{
    QString concatenated = settings["challonge>username"] + ":" +
                           settings["challonge>apiKey"];
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    return headerData.toLocal8Bit();
}

void ChallongeWidget::processTournamentListJson()
{
    statusLabel->setText("");
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    const QString replyData = reply->readAll();
    const QJsonDocument response = QJsonDocument::fromJson(replyData.toUtf8());
    const QString labelText = "Error loading tournament list:\n%1";

    if (reply->error() != QNetworkReply::NoError)
    {
        if (response.isEmpty())
        {
            statusLabel->setText(labelText.arg(replyData));
        }
        else
        {
            const QJsonArray errorList = response.object()["errors"].toArray();

            QStringList errors;
            for (QJsonArray::const_iterator iter = errorList.constBegin();
                 iter != errorList.constEnd(); iter++)
            {
                errors.append(iter->toString());
            }

            statusLabel->setText(labelText.arg(errors.join("\n")));
        }
        return;
    }

    qDebug() << "Tournament list response: " << replyData;

    tournamentsBox->clear();
    matchesBox->clear();

    QJsonArray tournamentsArray = response.array();
    if (tournamentsArray.isEmpty())
    {
        statusLabel->setText(labelText.arg("There are no tournaments currently in progress."));
    }
    else
    {
        for (QJsonArray::const_iterator iter = tournamentsArray.constBegin();
             iter != tournamentsArray.constEnd(); iter++)
        {
            QJsonObject tournamentRecord = iter->toObject();
            QJsonObject tournamentObject = tournamentRecord["tournament"].toObject();
            tournamentsBox->addItem(tournamentObject["name"].toString(),
                                    QString::number(tournamentObject["id"].toInt()));
        }
    }
    tournamentsBox->addItem("Custom...", "custom");

    updateCustomIdBoxState();
}

void ChallongeWidget::processTournamentJson()
{
    statusLabel->setText("");
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    QString replyData = reply->readAll();

    if (reply->error() != QNetworkReply::NoError)
    {
        QString labelText = "Error loading tournament data:\n%1";

        QJsonDocument errorJson = QJsonDocument::fromJson(replyData.toUtf8());

        qDebug() << replyData;


        const QJsonArray errorList = errorJson.object()["errors"].toArray();

        QStringList errors;
        for (QJsonArray::const_iterator iter = errorList.constBegin();
             iter != errorList.constEnd(); iter++)
        {
            errors.append(iter->toString());
        }

        statusLabel->setText(labelText.arg(errors.join("\n")));

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
