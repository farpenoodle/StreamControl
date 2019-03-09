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

#include "providerwidgetbuilder.h"
#include "providerwidget.h"
#include "challongewidget.h"
#include "smashggwidget.h"

ProviderWidgetBuilder::ProviderWidgetBuilder(QWidget *parent,
                                               QMap<QString, QObject*>& widgetList,
                                               const QMap<QString, QString>& settings)
    : parent(parent), widgetList(widgetList), settings(settings)
{

}

void ProviderWidgetBuilder::setPlayerNameWidgets(QString playerOneWidgetId,
                                                  QString playerTwoWidgetId)
{
    playerOneWidget = playerOneWidgetId;
    playerTwoWidget = playerTwoWidgetId;
}

void ProviderWidgetBuilder::setPlayerCountryWidgets(QString playerOneCountryWidgetId,
                                                    QString playerTwoCountryWidgetId)
{
    playerOneCountryWidget = playerOneCountryWidgetId;
    playerTwoCountryWidget = playerTwoCountryWidgetId;
}

void ProviderWidgetBuilder::setTournamentStageWidget(QString widgetId)
{
    tournamentStageWidget = widgetId;
}

void ProviderWidgetBuilder::setBracketStageWidget(QString widgetId)
{
    bracketStageWidget = widgetId;
}

void ProviderWidgetBuilder::setClearWidgets(QList<QString> widgetIds)
{
    clearWidgets = widgetIds;
}

void ProviderWidgetBuilder::setOutputFileName(QString fileName)
{
    outputFileName = fileName;
}

void ProviderWidgetBuilder::addMatchWidget(QString tournamentStage,
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


ProviderWidget* ProviderWidgetBuilder::build(ProviderWidgetBuilder::Provider provider) const
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

    if (provider == Provider::Challonge) {
        return new ChallongeWidget(parent, widgetList, settings,
                                   playerOneWidget, playerTwoWidget,
                                   playerOneCountryWidget, playerTwoCountryWidget,
                                   tournamentStageWidget,
                                   bracketStageWidget,
                                   outputFileName,
                                   bracketWidgets,
                                   clearWidgets);
    } else if (provider == Provider::Smashgg) {
        return new SmashggWidget(parent, widgetList, settings,
                                 playerOneWidget, playerTwoWidget,
                                 playerOneCountryWidget, playerTwoCountryWidget,
                                 tournamentStageWidget,
                                 bracketStageWidget,
                                 outputFileName,
                                 bracketWidgets,
                                 clearWidgets);
    }
}
