/**********************************************************************************

Copyright (c) 2012, Tan Yu Sheng
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

#include <QFile>
#include <QtXml/QDomDocument>
#include <QTextStream>
#include <QDateTime>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configwindow.h"
#include <QtDebug>
#include <QShortcut>
#include <QMessageBox>
#include <QComboBox>
#include <QAction>
#include <QLabel>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //code to add non buttons to toolbar
    gameComboBox = new QComboBox(this);
    gameComboBox->setMinimumContentsLength(20);
    QLabel* spaceLabel = new QLabel("   ");
    QLabel* gameLabel = new QLabel("Game ");

    QAction* actionAddGame = new QAction(this);
    actionAddGame->setObjectName(QString("actionAddGame"));
    QIcon addIcon;
    addIcon.addFile(QString::fromUtf8(":/StreamControl/icons/fugue/bonus/icons-24/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionAddGame->setIcon(addIcon);

    QAction* actionDelGame = new QAction(this);
    actionDelGame->setObjectName(QString("actionDelGame"));
    QIcon delIcon;
    delIcon.addFile(QString::fromUtf8(":/StreamControl/icons/fugue/bonus/icons-24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionDelGame->setIcon(delIcon);

    ui->toolBar->addWidget(spaceLabel);
    ui->toolBar->addWidget(gameLabel);
    ui->toolBar->addWidget(gameComboBox);
    ui->toolBar->addAction(actionAddGame);
    ui->toolBar->addAction(actionDelGame);


    connect(ui->actionConfig,SIGNAL( triggered() ),this,SLOT( openConfig() ));
    connect(ui->actionSave,SIGNAL( triggered() ),this,SLOT( saveData() ));
    connect(ui->resetButton,SIGNAL( clicked() ),this,SLOT( resetScores() ));
    connect(ui->swapButton,SIGNAL( clicked() ),this,SLOT( swapNames() ));
    connect(actionAddGame,SIGNAL( triggered() ),this,SLOT( addGame() ));
    connect(actionDelGame,SIGNAL( triggered() ),this,SLOT( delGame() ));

    cWindow = new ConfigWindow(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSettings() {

    QFile file("settings.xml");
    QString xsplitPath;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        QDomDocument doc;
        doc.setContent(&file);

        file.close();

        QDomElement settingsXML = doc.namedItem("settings").toElement();

        QDomElement xsplitPathE = settingsXML.namedItem("xsplitPath").toElement();

        xsplitPath = xsplitPathE.text();

        QDomElement useCDATAE = settingsXML.namedItem("useCDATA").toElement();

        if (useCDATAE.text() == "1") {
            useCDATA = true;
            settings["useCDATA"] = "1";
        } else {
            useCDATA = false;
            settings["useCDATA"] = "0";
        }

        QDomElement gamesE = settingsXML.namedItem("games").toElement();

        for(QDomNode n = gamesE.firstChild(); !n.isNull(); n = n.nextSibling())
        {
           QDomElement gameE = n.toElement();
           gameComboBox->addItem(gameE.text());
        }

        settings["xsplitPath"] = xsplitPath;


    } else {
        QFile xsplitExe32("C:\\Program Files\\SplitMediaLabs\\XSplit\\XSplit.Core.exe");
        QFile xsplitExe("C:\\Program Files (x86)\\SplitMediaLabs\\XSplit\\XSplit.Core.exe");
        if (xsplitExe.exists() || xsplitExe32.exists()) {
            if (xsplitExe.exists()) {
                xsplitPath = "C:\\Program Files (x86)\\SplitMediaLabs\\XSplit\\";
            } else {
                xsplitPath = "C:\\Program Files\\SplitMediaLabs\\XSplit\\";
            }
            QMessageBox msgBox;

            msgBox.setText("XSplit Installation detected at default location. Saving settings.");
            msgBox.exec();

            settings["xsplitPath"] = xsplitPath;

        } else {
            QMessageBox msgBox;
            msgBox.setText("Please be sure to configure StreamControl before you start.");
            msgBox.exec();
            xsplitPath = "";
        }


        //set some default games if none already set
        gameComboBox->addItem("Super Street Fighter IV");
        gameComboBox->addItem("Ultimate Marvel vs Capcom 3");
        gameComboBox->addItem("Persona 4: Arena");
        gameComboBox->addItem("Tekken Tag Tournament 2");
        gameComboBox->addItem("Soul Calibur V");
        gameComboBox->addItem("King of Fighters XIII");

        saveSettings();
    }

}

void MainWindow::saveSettings() {
    QFile file("settings.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QDomDocument doc ("StreamControl");

    QDomElement settingsXML = doc.createElement("settings");
    doc.appendChild(settingsXML);

    QDomElement xsplitPathE = doc.createElement("xsplitPath");
    settingsXML.appendChild(xsplitPathE);

    QDomCDATASection xsplitPathT = doc.createCDATASection(settings["xsplitPath"]);
    xsplitPathE.appendChild(xsplitPathT);

    QDomElement useCDATAE = doc.createElement("useCDATA");
    settingsXML.appendChild(useCDATAE);

    QDomText useCDATAT = doc.createTextNode(settings["useCDATA"]);
    useCDATAE.appendChild(useCDATAT);

    QDomElement gamesE = doc.createElement("games");
    settingsXML.appendChild(gamesE);


    for (int i = 0; i < gameComboBox->count(); ++i) {
        QDomElement gameE = doc.createElement("game");
        gamesE.appendChild(gameE);
        QDomCDATASection gameText = doc.createCDATASection(gameComboBox->itemText(i));
        gameE.appendChild(gameText);
    }


    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << doc.toString();
    file.close();
}

void MainWindow::loadData()
{
    QFile file(settings["xsplitPath"] + "streamcontrol.xml");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QDomDocument doc;
    doc.setContent(&file);

    file.close();

    QDomElement items = doc.namedItem("items").toElement();

    QDomElement pName1 = items.namedItem("pName1").toElement();
    QDomElement pName2 = items.namedItem("pName2").toElement();
    QDomElement pScore1 = items.namedItem("pScore1").toElement();
    QDomElement pScore2 = items.namedItem("pScore2").toElement();
    QDomElement rounds = items.namedItem("rounds").toElement();
    QDomElement cTitle1 = items.namedItem("cTitle1").toElement();
    QDomElement cTitle2 = items.namedItem("cTitle2").toElement();
    QDomElement mText1 = items.namedItem("mText1").toElement();
    QDomElement mText2 = items.namedItem("mText2").toElement();
    QDomElement mText3 = items.namedItem("mText3").toElement();
    QDomElement mText4 = items.namedItem("mText4").toElement();
    QDomElement game = items.namedItem("game").toElement();

    ui->pName1->setText(pName1.text());
    ui->pScore1->setValue(pScore1.text().toInt());
    ui->pName2->setText(pName2.text());
    ui->pScore2->setValue(pScore2.text().toInt());
    ui->rounds->setValue(rounds.text().toInt());
    ui->cTitle1->setText(cTitle1.text());
    ui->cTitle2->setText(cTitle2.text());
    ui->mText1->setText(mText1.text());
    ui->mText2->setText(mText2.text());
    ui->mText3->setText(mText3.text());
    ui->mText4->setText(mText4.text());

    int gameIndex = gameComboBox->findText(game.text());
    if (gameIndex != -1) {
        gameComboBox->setCurrentIndex(gameIndex);
    } else if (game.text() != "") {
        gameComboBox->addItem(game.text());
        gameComboBox->setCurrentIndex(gameComboBox->findText(game.text()));
        saveSettings();
    }

}


void MainWindow::saveData()
{
    QFile file(settings["xsplitPath"] + "streamcontrol.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QDomDocument doc ("StreamControl");

    QDomElement items = doc.createElement("items");
    doc.appendChild(items);


    QDateTime current = QDateTime::currentDateTime();
    uint timestamp_t = current.toTime_t();

    QDomElement timestamp = doc.createElement("timestamp");
    items.appendChild(timestamp);

    QDomText timestampt = doc.createTextNode(QString::number(timestamp_t));;
    timestamp.appendChild(timestampt);

    QDomElement pName1 = doc.createElement("pName1");
    items.appendChild(pName1);

    if (useCDATA) {
        QDomCDATASection pName1t = doc.createCDATASection(ui->pName1->text());
        pName1.appendChild(pName1t);
    } else {
        QDomText pName1t = doc.createTextNode(ui->pName1->text());
        pName1.appendChild(pName1t);
    }

    QDomElement pScore1 = doc.createElement("pScore1");
    items.appendChild(pScore1);

    QDomText pScore1t = doc.createTextNode(ui->pScore1->text());
    pScore1.appendChild(pScore1t);



    QDomElement pName2 = doc.createElement("pName2");
    items.appendChild(pName2);

    if (useCDATA) {
        QDomCDATASection pName2t = doc.createCDATASection(ui->pName2->text());
        pName2.appendChild(pName2t);
    } else {
        QDomText pName2t = doc.createTextNode(ui->pName2->text());
        pName2.appendChild(pName2t);
    }

    QDomElement pScore2 = doc.createElement("pScore2");
    items.appendChild(pScore2);

    QDomText pScore2t = doc.createTextNode(ui->pScore2->text());
    pScore2.appendChild(pScore2t);



    QDomElement rounds = doc.createElement("rounds");
    items.appendChild(rounds);

    QDomText roundst = doc.createTextNode(ui->rounds->text());
    rounds.appendChild(roundst);



    QDomElement cTitle1 = doc.createElement("cTitle1");
    items.appendChild(cTitle1);

    if (useCDATA) {
        QDomCDATASection cTitle1t = doc.createCDATASection(ui->cTitle1->text());
        cTitle1.appendChild(cTitle1t);
    } else {
        QDomText cTitle1t = doc.createTextNode(ui->cTitle1->text());
        cTitle1.appendChild(cTitle1t);
    }



    QDomElement cTitle2 = doc.createElement("cTitle2");
    items.appendChild(cTitle2);

    if (useCDATA) {
        QDomCDATASection cTitle2t = doc.createCDATASection(ui->cTitle2->text());
        cTitle2.appendChild(cTitle2t);
    } else {
        QDomText cTitle2t = doc.createTextNode(ui->cTitle2->text());
        cTitle2.appendChild(cTitle2t);
    }



    QDomElement mText1 = doc.createElement("mText1");
    items.appendChild(mText1);

    if (useCDATA) {
        QDomCDATASection mText1t = doc.createCDATASection(ui->mText1->text());
        mText1.appendChild(mText1t);
    } else {
        QDomText mText1t = doc.createTextNode(ui->mText1->text());
        mText1.appendChild(mText1t);
    }


    
    QDomElement mText2 = doc.createElement("mText2");
    items.appendChild(mText2);

    if (useCDATA) {
        QDomCDATASection mText2t = doc.createCDATASection(ui->mText2->text());
        mText2.appendChild(mText2t);
    } else {
        QDomText mText2t = doc.createTextNode(ui->mText2->text());
        mText2.appendChild(mText2t);
    }



    QDomElement mText3 = doc.createElement("mText3");
    items.appendChild(mText3);

    if (useCDATA) {
        QDomCDATASection mText3t = doc.createCDATASection(ui->mText3->text());
        mText3.appendChild(mText3t);
    } else {
        QDomText mText3t = doc.createTextNode(ui->mText3->text());
        mText3.appendChild(mText3t);
    }



    QDomElement mText4 = doc.createElement("mText4");
    items.appendChild(mText4);

    if (useCDATA) {
        QDomCDATASection mText4t = doc.createCDATASection(ui->mText4->text());
        mText4.appendChild(mText4t);
    } else {
        QDomText mText4t = doc.createTextNode(ui->mText4->text());
        mText4.appendChild(mText4t);
    }


    QDomElement gameE = doc.createElement("game");
    items.appendChild(gameE);

    if (useCDATA) {
        QDomCDATASection gameT = doc.createCDATASection(gameComboBox->currentText());
        gameE.appendChild(gameT);
    } else {
        QDomText gameT = doc.createTextNode(gameComboBox->currentText());
        gameE.appendChild(gameT);
    }


    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << doc.toString();
    file.close();

}

void MainWindow::resetScores()
{
    ui->pScore1->setValue(0);
    ui->pScore2->setValue(0);
}

void MainWindow::swapNames()
{
    QString tempName = ui->pName1->text();
    ui->pName1->setText(ui->pName2->text());
    ui->pName2->setText(tempName);
    int tempscore = ui->pScore1->text().toInt();
    ui->pScore1->setValue(ui->pScore2->text().toInt());
    ui->pScore2->setValue(tempscore);
}


void MainWindow::openConfig() {
    cWindow->setConfig(settings);
    cWindow->show();

    if (cWindow->exec() == 1) {
        QMap<QString, QString> configSettings = cWindow->getConfig();

        settings["xsplitPath"] = configSettings["xsplitPath"];
        settings["useCDATA"] = configSettings["useCDATA"];

        if (settings["useCDATA"] == "1") {
            useCDATA = true;
        } else {
            useCDATA = false;
        }

        saveSettings();

        loadData();
    }
}

void MainWindow::addGame() {
    bool ok;
    QString game = QInputDialog::getText(this, tr("Input"),
                                              tr("Game:"), QLineEdit::Normal,
                                              "", &ok);
    if (ok && !game.isEmpty()) {
             gameComboBox->addItem(game);
             gameComboBox->setCurrentIndex(gameComboBox->findText(game));
             saveSettings();
    }
}

void MainWindow::delGame() {
    gameComboBox->removeItem(gameComboBox->currentIndex());
    saveSettings();
}
