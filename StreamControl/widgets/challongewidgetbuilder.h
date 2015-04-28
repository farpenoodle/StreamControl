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

#ifndef WIDGETS_CHALLONGEWIDGETBUILDER_H
#define WIDGETS_CHALLONGEWIDGETBUILDER_H

#include <QWidget>
#include <QMap>
#include <QMultiMap>

class ChallongeWidget;

class ChallongeWidgetBuilder
{
public:
    ChallongeWidgetBuilder(QWidget *parent, QMap<QString, QObject*>& widgetList,
                           const QMap<QString, QString>& settings);

    void setPlayerNameWidgets(QString playerOneWidget, QString playerTwoWidget);
    void setTournamentStageWidget(QString widgetId);
    void setBracketStageWidget(QString widgetId);
    void setOutputFileName(QString fileName);

    void addMatchWidget(QString tournamentStage,
        QString playerOneNameWidget, QString playerOneScoreWidget,
        QString playerTwoNameWidget, QString playerTwoScoreWidget);
    ChallongeWidget* build() const;

private:
    QWidget *parent;
    QMap<QString, QObject*>& widgetList;
    const QMap<QString, QString>& settings;
    QString playerOneWidget, playerTwoWidget;
    QString tournamentStageWidget, bracketStageWidget;
    QMultiMap<QString, QStringList> matchWidgets;
    QString outputFileName;
};

#endif // WIDGETS_CHALLONGEWIDGETBUILDER_H
