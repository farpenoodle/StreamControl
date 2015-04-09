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

#ifndef WIDGETS_CHALLONGEWIDGET_H
#define WIDGETS_CHALLONGEWIDGET_H

#include <QWidget>
#include <QMap>
#include <QJsonDocument>

class QPushButton;
class QLabel;
class QComboBox;
class QGridLayout;
class QNetworkAccessManager;
class QNetworkReply;
class QAuthenticator;
class QLineEdit;

enum TournamentType {SINGLE_ELIMINATION, DOUBLE_ELIMINATION, ROUND_ROBIN};

class ChallongeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChallongeWidget(QWidget *parent,
                                  QMap<QString, QObject*>& widgets,
                                  const QMap<QString, QString>& settings,
                                  QString playerOneWidget,
                                  QString playerTwoWidget,
                                  QString bracketWidgetId,
                                  QString tournamentStageWidget);


signals:

private:
    QGridLayout     *layout;

    QComboBox       *tournamentsBox;
    QLabel          *tournamentLabel;
    QLabel          *currentTournamentLabel;
    QLabel          *tournamentCustomLabel;
    QLineEdit       *tournamentCustomLineEdit;
    QPushButton     *tournamentFetchButton;

    QComboBox       *matchesBox;
    QLabel          *matchLabel;
    QPushButton     *matchFetchButton;

    QPushButton     *setMatchDataButton;
    QPushButton     *setBracketDataButton;

    QNetworkAccessManager   *manager;
    QLabel          *statusLabel;

    // Stores the json response of a tournament when fetched
    // Used to save bracket data to a file when the button is pressed
    QJsonDocument currentTournamentJson;

    // A map of player ids to names for the current tournament data
    QMap<int, QString> playerIdMap;

    // So we can set the target widgets with the bracket data
    QMap<QString, QObject*>& widgetList;

    // Needed to get the challonge username/api key
    const QMap<QString, QString>& settings;

    const QString playerOneWidgetId, playerTwoWidgetId, tournamentStageWidgetId,
      bracketWidgetId;

    QByteArray getAuthHeader() const;

public slots:
    void fetchTournaments();
    void fetchMatches();
    void processTournamentListJson();
    void processTournamentJson();
    void setMatchData();
    void setBracketData();
    void updateCustomIdBoxState();
};

#endif // WIDGETS_CHALLONGEWIDGET_H
