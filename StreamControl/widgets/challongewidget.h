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

#ifndef WIDGETS_CHALLONGEWIDGET_H
#define WIDGETS_CHALLONGEWIDGET_H

#include <QWidget>
#include <QMap>
#include <QJsonDocument>
#include "providerwidget.h"

class QPushButton;
class QLabel;
class QComboBox;
class QGridLayout;
class QNetworkAccessManager;
class QNetworkReply;
class QAuthenticator;
class QLineEdit;

enum TournamentType {SINGLE_ELIMINATION, DOUBLE_ELIMINATION, ROUND_ROBIN};

class ChallongeWidget : public ProviderWidget
{
    Q_OBJECT
public:
    explicit ChallongeWidget(QWidget *parent,
                                 QMap<QString, QObject*>& widgets,
                                 const QMap<QString, QString>& settings,
                                 QString playerOneWidget,
                                 QString playerTwoWidget,
                                 QString tournamentStageWidget,
                                 QString bracketWidgetId,
                                 QString outputFileName,
                                 QMap<QString, QStringList> bracketWidgets);

signals:

public slots:
    virtual void fetchTournaments();
    virtual void fetchMatches();
    virtual void processTournamentListJson();
    virtual void processTournamentJson();
    virtual void setMatchData();
    virtual void setBracketData();

private:
    QNetworkAccessManager   *manager;

    // A map of player ids to names for the current tournament data
    QMap<int, QString> playerIdMap;

    QByteArray getAuthHeader() const;

    // Sets up tournament structures in terms of tournament nodes
    void setUpTournamentNodes();

    // Fills other stream control widgets with the data from a challonge bracket
    void fillBracketWidgets();
    void fillBracketWithMatch(const QString matchId, const QJsonObject& match,
                              const QMap<int, QString>& playerIdMap);

    void fillWidget(const QJsonArray& matches, QString matchId, const QJsonObject& match);

    QMap<QString, TournamentTreeNode> doubleElimNodes;
};

#endif // WIDGETS_CHALLONGEWIDGET_H
