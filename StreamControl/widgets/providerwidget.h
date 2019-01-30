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

#ifndef WIDGETS_PROVIDERWIDGET_H
#define WIDGETS_PROVIDERWIDGET_H

#include <QWidget>
#include <QMap>
#include <QJsonDocument>
#include "tournamenttreenode.h"

class QPushButton;
class QLabel;
class QComboBox;
class QGridLayout;
class QLineEdit;

enum TournamentType {SINGLE_ELIMINATION, DOUBLE_ELIMINATION, ROUND_ROBIN};

class ProviderWidget : public QWidget
{
    Q_OBJECT
public:
    virtual ~ProviderWidget(){}
    explicit ProviderWidget(QWidget *parent, QMap<QString, QObject*>& widgetList,
                            const QMap<QString, QString>& settings,
                            QString playerOneWidgetId,
                            QString playerTwoWidgetId,
                            QString tournamentStageWidgetId,
                            QString bracketWidgetId,
                            QString outputFileName,
                            QMap<QString, QStringList> bracketWidgets);

signals:

public slots:
    virtual void fetchTournaments() = 0;
    virtual void fetchMatches() = 0;
    virtual void processTournamentListJson() = 0;
    virtual void processTournamentJson() = 0;
    virtual void setMatchData();// = 0;
    virtual void setBracketData();// = 0;
    virtual void updateCustomIdBoxState();// = 0;

protected:
    QComboBox       *tournamentsBox;
    QLabel          *currentTournamentLabel;
    QLineEdit       *tournamentCustomLineEdit;

    QComboBox       *matchesBox;

    QLabel          *statusLabel;

    // Stores the json response of a tournament when fetched
    // Used to save bracket data to a file when the button is pressed
    QJsonDocument currentTournamentJson;

    // A map of player ids to names for the current tournament data
    QMap<int, QString> playerIdMap;

    // Needed to get the challonge username/api key and the outputPath
    const QMap<QString, QString>& settings;

private:
    QGridLayout     *layout;

    QLabel          *tournamentLabel;
    QLabel          *tournamentCustomLabel;
    QPushButton     *tournamentFetchButton;

    QLabel          *matchLabel;
    QPushButton     *matchFetchButton;

    QPushButton     *setMatchDataButton;
    QPushButton     *setBracketDataButton;

    // So we can set the target widgets with the bracket data
    QMap<QString, QObject*>& widgetList;

    const QString playerOneWidgetId, playerTwoWidgetId, tournamentStageWidgetId,
      bracketWidgetId;

    // ids of widgets to fill
    QMap<QString, QStringList> bracketWidgets;

    // Where to save challonge bracket data
    QString outputFileName;

    // Sets up tournament structures in terms of tournament nodes
    void setUpTournamentNodes();

    // Fills other stream control widgets with the data from a challonge bracket
    void fillBracketWidgets();

    // Clears all challonge associated widgets specified in the layout file
    void clearBracketWidgets();

    void fillWidget(const QJsonArray& matches, QString matchId, const QJsonObject& match);

    // Saves challonge bracket data to a file in json format
    void writeBracketToFile();

    QMap<QString, TournamentTreeNode> doubleElimNodes;
};

#endif // WIDGETS_PROVIDERWIDGET_H
