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
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QList>
#include <QComboBox>
#include <QFile>

#include "providerwidget.h"

ProviderWidget::ProviderWidget(QWidget *parent,
                               QMap<QString, QObject*>& widgetList,
                               const QMap<QString, QString>& settings,
                               QString playerOneWidgetId,
                               QString playerTwoWidgetId,
                               QString tournamentStageWidgetId,
                               QString bracketWidgetId,
                               QString outputFileName,
                               QMap<QString, QStringList> bracketWidgets,
                               QString tournamentCustomLabelText) :
    QWidget(parent), widgetList(widgetList), settings(settings),
    playerOneWidgetId(playerOneWidgetId), playerTwoWidgetId(playerTwoWidgetId),
    tournamentStageWidgetId(tournamentStageWidgetId), bracketWidgetId(bracketWidgetId),
    bracketWidgets(bracketWidgets), outputFileName(outputFileName)
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
    tournamentCustomLabel->setText(tournamentCustomLabelText);
    matchLabel->setText("Match");

    statusLabel->setStyleSheet("QLabel { color : red; }");

    tournamentsBox->addItem("Custom...", "custom");

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

    connect(tournamentsBox, SIGNAL(currentIndexChanged(int)), dynamic_cast<QObject*>(this),
            SLOT(updateCustomIdBoxState()));

    connect(tournamentFetchButton, SIGNAL(clicked()), dynamic_cast<QObject*>(this), SLOT(fetchTournaments()));
    connect(matchFetchButton, SIGNAL(clicked()), dynamic_cast<QObject*>(this), SLOT(fetchMatches()));
    connect(setMatchDataButton, SIGNAL(clicked()), dynamic_cast<QObject*>(this), SLOT(setMatchData()));
    connect(setBracketDataButton, SIGNAL(clicked()), dynamic_cast<QObject*>(this), SLOT(setBracketData()));

    dynamic_cast<QWidget*>(this)->setLayout(layout);
};

void ProviderWidget::clearBracketWidgets()
{
    foreach(const QStringList& widgets, bracketWidgets)
    {
        foreach(const QString& widgetId, widgets)
        {
            ((QLineEdit*)widgetList[widgetId])->setText( "" );
        }
    }
}

void ProviderWidget::fillBracketMatchWidget(QString matchId,
                                            QString playerOne, QString playerTwo,
                                            QString scoreOne, QString scoreTwo)
{
    if (bracketWidgets.contains(matchId)) {
        dynamic_cast<QLineEdit*>(widgetList[bracketWidgets[matchId][0]])->setText((playerOne));
        dynamic_cast<QLineEdit*>(widgetList[bracketWidgets[matchId][2]])->setText((playerTwo));
        dynamic_cast<QLineEdit*>(widgetList[bracketWidgets[matchId][1]])->setText((scoreOne));
        dynamic_cast<QLineEdit*>(widgetList[bracketWidgets[matchId][3]])->setText((scoreTwo));
    }
}

bool ProviderWidget::writeBracketToFile()
{
    if (outputFileName.isEmpty())
        return false;
    QFile bracketFile(settings["outputPath"] + outputFileName);
    bracketFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    bracketFile.write(currentTournamentJson.toJson());
    bracketFile.close();
    return true;
}

void ProviderWidget::fillMatchWidgets(QString playerOne,
                                      QString playerTwo,
                                      QString tournamentStage,
                                      QString bracket)
{
    QLineEdit* playerOneWidget = dynamic_cast<QLineEdit*>(widgetList[playerOneWidgetId]);
    QLineEdit* playerTwoWidget = dynamic_cast<QLineEdit*>(widgetList[playerTwoWidgetId]);
    QLineEdit* tournamentStageWidget = dynamic_cast<QLineEdit*>(widgetList[tournamentStageWidgetId]);
    QLineEdit* bracketWidget = dynamic_cast<QLineEdit*>(widgetList[bracketWidgetId]);
    if (playerOneWidget && playerTwoWidget) {
        playerOneWidget->setText(playerOne);
        playerTwoWidget->setText(playerTwo);
    }
    if (tournamentStageWidget)
        tournamentStageWidget->setText(tournamentStage);
    if (bracketWidget)
        bracketWidget->setText(bracket);
}

void ProviderWidget::updateCustomIdBoxState()
{
    // The last entry in the tournaments box should always be the custom option
    bool boxEnabled = (tournamentsBox->currentIndex() == tournamentsBox->count() - 1);

    tournamentCustomLineEdit->setEnabled(boxEnabled);
}
