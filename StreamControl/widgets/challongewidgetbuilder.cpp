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

#include "challongewidgetbuilder.h"
#include "challongewidget.h"

ChallongeWidgetBuilder::ChallongeWidgetBuilder(QWidget *parent,
                                               QMap<QString, QObject*>& widgetList,
                                               const QMap<QString, QString>& settings)
    : parent(parent), widgetList(widgetList), settings(settings)
{

}

void ChallongeWidgetBuilder::setPlayerNameWidgets(QString playerOneWidgetId,
                                                  QString playerTwoWidgetId)
{
    playerOneWidget = playerOneWidgetId;
    playerTwoWidget = playerTwoWidgetId;
}

void ChallongeWidgetBuilder::setTournamentStageWidget(QString widgetId)
{
    tournamentStageWidget = widgetId;
}

void ChallongeWidgetBuilder::setBracketStageWidget(QString widgetId)
{
    bracketStageWidget = widgetId;
}

void ChallongeWidgetBuilder::setOutputFileName(QString fileName)
{
    outputFileName = fileName;
}

void ChallongeWidgetBuilder::addMatchWidget(QString tournamentStage,
                                            QString playerOneNameWidget,
                                            QString playerOneScoreWidget,
                                            QString playerTwoNameWidget,
                                            QString playerTwoScoreWidget)
{
    QStringList l;
    l.append(playerOneNameWidget);
    l.append(playerOneScoreWidget);
    l.append(playerTwoNameWidget);
    l.append(playerTwoScoreWidget);
    matchWidgets.insertMulti(tournamentStage, l);
}


ChallongeWidget* ChallongeWidgetBuilder::build() const
{
    QMap<QString, QStringList> bracketWidgets;

    foreach (const QString& key, matchWidgets.uniqueKeys() )
    {
        int i = matchWidgets.values(key).size();
        foreach (const QStringList& widgetDetails, matchWidgets.values(key) )
        {
            // values() lists values in reverse order so we do the below stuff backwards

            bracketWidgets.insert(key + (matchWidgets.values(key).size() > 1 ? QString::number(i) : ""), widgetDetails);
            i--;
        }
    }

    ChallongeWidget* widget =  new ChallongeWidgetImpl(parent, widgetList, settings,
                                                       playerOneWidget, playerTwoWidget,
                                                       tournamentStageWidget,
                                                       bracketStageWidget,
                                                       outputFileName,
                                                       bracketWidgets);

    return widget;
}
