/**********************************************************************************

Copyright (c) 2015, Antony Clarke
Copyright (c) 2019, Miguel Müller <miguel.muller@tutanota.com>
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

#include "smashggwidget.h"

SmashggWidget::SmashggWidget(QWidget *parent,
                                 QMap<QString, QObject*>& widgetList,
                                 const QMap<QString, QString>& settings,
                                 QString playerOneWidgetId,
                                 QString playerTwoWidgetId,
                                 QString tournamentStageWidgetId,
                                 QString bracketWidgetId,
                                 QString outputFileName,
                                 QMap<QString, QStringList> bracketWidgets) :
    ProviderWidget(parent, widgetList, settings, playerOneWidgetId,
                   playerTwoWidgetId, tournamentStageWidgetId, bracketWidgetId,
                   outputFileName, bracketWidgets, "or Tournament Slug:")
{
    manager = new QNetworkAccessManager;
};

void SmashggWidget::fetchTournaments()
{
    QString ownerId = settings["smashgg>ownerId"];
    QJsonObject variables {
        {"ownerId", ownerId},
        {"perPage", 10}
    };

    QNetworkRequest request(urlString);
    QString data = smashggRequest(request, tourneysRequest, variables);

    QNetworkReply *reply = manager->post(request, data.toLocal8Bit());

    connect(reply, SIGNAL(finished()), this, SLOT(processTournamentListJson()));
}

void SmashggWidget::fetchMatches()
{
    QString currentTournamentSlug;
    int currentIndex = tournamentsBox->currentIndex();

    // If custom is selected...
    if (tournamentsBox->currentIndex() == tournamentsBox->count() - 1)
        currentTournamentSlug = tournamentCustomLineEdit->text();
    else
        currentTournamentSlug = tournamentsBox->itemData(currentIndex).toString();

    QJsonObject variables {
        {"tourneySlug", currentTournamentSlug}
    };

    QNetworkRequest request(urlString);

    QString data = smashggRequest(request, streamQueueBySlugRequest, variables);
    QNetworkReply *reply = manager->post(request, data.toLocal8Bit());

    connect(reply, SIGNAL(finished()), this, SLOT(processTournamentJson()));
}

QByteArray SmashggWidget::getAuthHeader() const
{
    QString headerData = "Bearer " + settings["smashgg>authenticationToken"];
    return headerData.toLocal8Bit();
}

QString SmashggWidget::smashggRequest(QNetworkRequest& request, QString smashggRequestString, QJsonObject variables)
{
    request.setRawHeader("Authorization", getAuthHeader());
    request.setRawHeader("Content-Type", "application/json");
    QJsonObject data {
        {"query", smashggRequestString},
        {"variables", variables}
    };
    return QJsonDocument(data).toJson(QJsonDocument::Compact);
}

void SmashggWidget::processTournamentListJson()
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

    QJsonArray tournamentsArray = response.object()["data"]
                                          .toObject()["tournaments"]
                                          .toObject()["nodes"]
                                          .toArray();
    if (tournamentsArray.isEmpty())
    {
        statusLabel->setText(labelText.arg("No tournaments found with this owner."));
    }
    else
    {
        for (QJsonArray::const_iterator iter = tournamentsArray.constBegin();
             iter != tournamentsArray.constEnd(); iter++)
        {
            QJsonObject tournamentObject = iter->toObject();
            tournamentsBox->addItem(tournamentObject["name"].toString(),
                                    tournamentObject["slug"].toString());
        }
    }
    tournamentsBox->addItem("Custom...", "custom");

    updateCustomIdBoxState();
}

void SmashggWidget::processTournamentJson()
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

    QJsonObject replyDataJson = QJsonDocument::fromJson(replyData.toUtf8()).object();
    QJsonObject tournamentJson = replyDataJson["data"].toObject()["tournament"].toObject();
    QString tournamentName = tournamentJson["name"].toString();
    currentTournamentLabel->setText(QString("Current Tournament: %1").arg(tournamentName));

    QJsonArray setsJson = tournamentJson["streamQueue"].toArray()[0].toObject()["sets"].toArray();

    matchesBox->clear();

    for (QJsonArray::const_iterator iter = setsJson.constBegin();
         iter != setsJson.constEnd(); iter++)
    {
        QJsonArray players = iter->toObject()["slots"].toArray();
        QJsonObject p1Json = players[0].toObject()["entrant"].toObject();
        QJsonObject p2Json = players[1].toObject()["entrant"].toObject();
        QString p1Name = p1Json["name"].toString();
        QString p2Name = p2Json["name"].toString();
        QString str = QString("%1 vs %2").arg(p1Name, p2Name);
        QVariantList matchDetails;
        matchDetails.append("double elimination");
        matchDetails.append(tournamentName);
        matchDetails.append(iter->toObject()["fullRoundText"].toString());
        matchDetails.append(p1Name);
        matchDetails.append(p2Name);
        QJsonObject match = iter->toObject()["match"].toObject();
        matchesBox->addItem(str, matchDetails);
    }
}

void SmashggWidget::setBracketData()
{

}

void SmashggWidget::setMatchData()
{
    QVariant var = (matchesBox->itemData(matchesBox->currentIndex()));
    QVariantList matchDetails = var.toList();

    if (!matchDetails.empty()) {
        fillMatchWidgets(matchDetails[3].toString(),
                         matchDetails[4].toString(),
                         matchDetails[2].toString(),
                         matchDetails[1].toString());
    }
}
