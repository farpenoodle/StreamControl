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
#include <QTextStream>
#include <QDateTime>
#include "mainwindow.h"
#include "configwindow.h"
#include <QtDebug>
#include <QShortcut>
#include <QMessageBox>
#include <QComboBox>
#include <QAction>
#include <QLabel>
#include <QInputDialog>
#include <QToolButton>
#include <QMenu>
#include <QSpinBox>
#include <QLineEdit>
#include <QPainter>
#include <QToolbar>
#include <QPushButton>
#include <QCheckBox>
#include <QScrollArea>
#include "csv.h"
#include <QCompleter>
#include <QFileInfo>
#include <QDir>
#include "ScCompleter.h"
#include <QStringListModel>
#include "ScLineEdit.h"
#include "scradiogroup.h"
#include "sctsbutton.h"
#include <QRadioButton>
#include "windows.h"
#include "twitterwidget.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

MainWindow::MainWindow()
{

    if (objectName().isEmpty())
                setObjectName(QStringLiteral("MainWindow"));

    //Set up signalmappers
    resetMapper = new QSignalMapper (this) ;
    swapMapper = new QSignalMapper (this) ;

    //some defaults
    resize(50, 50);
    setFixedSize(50, 50);

    QIcon icon;
    icon.addFile(QStringLiteral(":/StreamControl/icons/r1logo2trans-crop.png"), QSize(), QIcon::Normal, QIcon::Off);
    setWindowIcon(icon);
    setAnimated(true);
    setWindowFlags(windowFlags()^Qt::WindowMaximizeButtonHint);

    cWindow = new ConfigWindow(this);

    toolBar = new QToolBar(this);
    toolBar->setObjectName(QStringLiteral("toolBar"));
    toolBar->setLayoutDirection(Qt::LeftToRight);
    toolBar->setMovable(false);
    toolBar->setFloatable(false);
    addToolBar(Qt::TopToolBarArea, toolBar);

    QAction* actionSave = new QAction(this);
    actionSave->setObjectName(QStringLiteral("actionSave"));
    QIcon icon1;
    icon1.addFile(QStringLiteral(":/StreamControl/icons/fugue/bonus/icons-24/disk.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionSave->setIcon(icon1);
    actionSave->setShortcuts(QKeySequence::Save);
    connect(actionSave,SIGNAL( triggered() ),this,SLOT( saveData() ));

    QMenu *configMenu = new QMenu();
    QAction *actionConfig = new QAction("Configuration", this);
    configMenu->addAction(actionConfig);
    QAction *actionAlwaysOnTop = new QAction("Always on top", this);
    actionAlwaysOnTop->setCheckable(true);
    configMenu->addAction(actionAlwaysOnTop);


    QToolButton* configButton = new QToolButton();
    configButton->setMenu(configMenu);
    configButton->setPopupMode(QToolButton::InstantPopup);
    QIcon configIcon;
    configIcon.addFile(QString::fromUtf8(":/StreamControl/icons/fugue/bonus/icons-24/gear.png"), QSize(), QIcon::Normal, QIcon::Off);
    configButton->setIcon(configIcon);
    connect(actionConfig,SIGNAL( triggered() ),this,SLOT( openConfig() ));
    connect(actionAlwaysOnTop,SIGNAL(toggled(bool)),this,SLOT( toggleAlwaysOnTop(bool) ));



    //code to add non buttons to toolbar
    QLabel* spaceLabel = new QLabel("   ");

    toolBar->addAction(actionSave);
    toolBar->addWidget(configButton);
    toolBar->addWidget(spaceLabel);
    toolBar->setContextMenuPolicy(Qt::PreventContextMenu);

    loadSettings();
    loadLayout();
    loadData();

}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::loadSettings() {

    QFile file("settings.xml");
    QString xsplitPath;
    QString layoutPath;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        QDomDocument doc;
        doc.setContent(&file);

        file.close();

        QDomElement settingsXML = doc.namedItem("settings").toElement();

        QDomElement xsplitPathE = settingsXML.namedItem("xsplitPath").toElement();
        QDomElement layoutPathE = settingsXML.namedItem("layoutPath").toElement();

        xsplitPath = xsplitPathE.text();
        layoutPath = layoutPathE.text();

        QDomElement useCDATAE = settingsXML.namedItem("useCDATA").toElement();

        if (useCDATAE.text() == "1") {
            useCDATA = true;
            settings["useCDATA"] = "1";
        } else {
            useCDATA = false;
            settings["useCDATA"] = "0";
        }

        QDomElement formatE = settingsXML.namedItem("format").toElement();

        saveFormat = formatE.text().toInt();

        if(saveFormat < 1 || saveFormat > 3) {
            saveFormat = SC_XML;
        }

        settings["format"] = QString::number(saveFormat);

        settings["xsplitPath"] = xsplitPath;
        settings["layoutPath"] = layoutPath;


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

    QDomElement layoutPathE = doc.createElement("layoutPath");
    settingsXML.appendChild(layoutPathE);

    QDomCDATASection layoutPathT = doc.createCDATASection(settings["layoutPath"]);
    layoutPathE.appendChild(layoutPathT);

    QDomElement useCDATAE = doc.createElement("useCDATA");
    settingsXML.appendChild(useCDATAE);

    QDomText useCDATAT = doc.createTextNode(settings["useCDATA"]);
    useCDATAE.appendChild(useCDATAT);

    QDomElement formatE = doc.createElement("format");
    settingsXML.appendChild(formatE);

    QDomText formatT = doc.createTextNode(settings["format"]);
    formatE.appendChild(formatT);

    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << doc.toString();
    file.close();
}

void MainWindow::loadData()
{
    if (saveFormat == SC_XML || saveFormat == SC_Both) {
        loadXML();
    }
    if (saveFormat == SC_JSON) {
        loadJSON();
    }

}

void MainWindow::loadXML() {
    QFile file(settings["xsplitPath"] + "streamcontrol.xml");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QDomDocument doc;
    doc.setContent(&file);

    file.close();

    QDomElement items = doc.namedItem("items").toElement();

    QMapIterator<QString, QObject *> i(widgetList);
    while (i.hasNext()) {
        i.next();
        QString wType = widgetType[i.key()];
        QDomElement currElement = items.namedItem(i.key()).toElement();

        if (wType == "lineEdit") {
            ((ScLineEdit*)widgetList[i.key()])->setText(currElement.text());
        } else if (wType == "spinBox") {
            ((QSpinBox*)widgetList[i.key()])->setValue(currElement.text().toInt());
        } else if (wType == "tsButton") {
            ((ScTSButton*)widgetList[i.key()])->setTimeStamp(currElement.text().toInt());
        } else if (wType == "checkBox") {
            if (currElement.text() == "1") {
                ((QCheckBox*)widgetList[i.key()])->setChecked(true);
            } else {
                ((QCheckBox*)widgetList[i.key()])->setChecked(false);
            }
        } else if (wType == "radioGroup") {
            ((ScRadioGroup*)widgetList[i.key()])->checkFromValue(currElement.text());
        }
    }
}

void MainWindow::loadJSON() {
    QFile file(settings["xsplitPath"] + "streamcontrol.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);


    //doc.setContent(&file);
    QString input = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(input.toUtf8());
    QJsonObject Obj = doc.object();
    qDebug() << doc.isNull();

    file.close();

    //QDomElement items = doc.namedItem("items").toElement();

    QMapIterator<QString, QObject *> i(widgetList);
    while (i.hasNext()) {
        i.next();
        QString wType = widgetType[i.key()];

        if (wType == "lineEdit") {
            ((ScLineEdit*)widgetList[i.key()])->setText(Obj[i.key()].toString());
        } else if (wType == "spinBox") {
            ((QSpinBox*)widgetList[i.key()])->setValue(Obj[i.key()].toInt());
        } else if (wType == "tsButton") {
            ((ScTSButton*)widgetList[i.key()])->setTimeStamp(Obj[i.key()].toInt());
        } else if (wType == "checkBox") {
            if (Obj[i.key()].toString() == "1") {
                ((QCheckBox*)widgetList[i.key()])->setChecked(true);
            } else {
                ((QCheckBox*)widgetList[i.key()])->setChecked(false);
            }
        } else if (wType == "radioGroup") {
            ((ScRadioGroup*)widgetList[i.key()])->checkFromValue(Obj[i.key()].toString());
        }
    }
}


void MainWindow::saveData()
{
    QString dataOutput;

    if (saveFormat == SC_XML || saveFormat == SC_Both) {
        QFile file(settings["xsplitPath"] + "streamcontrol.xml");
        file.open(QIODevice::WriteOnly | QIODevice::Text);

        dataOutput = saveXML();

        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << dataOutput;
        file.close();
    }

    if (saveFormat == SC_JSON || saveFormat == SC_Both) {
        QFile file(settings["xsplitPath"] + "streamcontrol.json");
        file.open(QIODevice::WriteOnly | QIODevice::Text);

        dataOutput = saveJSON();

        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << dataOutput;
        file.close();
    }

    //datasets

    saveDataSets();
}

QString MainWindow::saveXML() {
    QDomDocument doc ("StreamControl");

    QDomElement items = doc.createElement("items");
    doc.appendChild(items);


    QDateTime current = QDateTime::currentDateTime();
    uint timestamp_t = current.toTime_t();

    QDomElement timestamp = doc.createElement("timestamp");
    items.appendChild(timestamp);

    QDomText timestampt = doc.createTextNode(QString::number(timestamp_t));;
    timestamp.appendChild(timestampt);

    QMapIterator<QString, QObject *> i(widgetList);
    while (i.hasNext()) {
        i.next();
        QString wType = widgetType[i.key()];
        QDomElement newItem = doc.createElement(i.key());
        items.appendChild(newItem);

        if (wType == "lineEdit") {
            if (useCDATA) {
                QDomCDATASection newItemt = doc.createCDATASection(((ScLineEdit*)widgetList[i.key()])->text());
                newItem.appendChild(newItemt);
            } else {
                QDomText newItemt = doc.createTextNode(((ScLineEdit*)widgetList[i.key()])->text());
                newItem.appendChild(newItemt);
            }
        } else if (wType == "spinBox") {
            QDomText newItemt = doc.createTextNode(((QSpinBox*)widgetList[i.key()])->text());
            newItem.appendChild(newItemt);
        } else if (wType == "checkBox") {
            QString checked = "0";
            if (((QCheckBox*)widgetList[i.key()])->isChecked()) {
                checked = "1";
            }
            QDomText newItemt = doc.createTextNode(checked);
            newItem.appendChild(newItemt);
        } else if (wType == "comboBox") {
            int currentIndex = ((QComboBox*)widgetList[i.key()])->currentIndex();
            QString value;
            QVariant data = ((QComboBox*)widgetList[i.key()])->itemData(currentIndex);
            if (data.isNull())
                value = ((QComboBox*)widgetList[i.key()])->itemText(currentIndex);
            else
                value = data.toString();

            QDomText newItemt = doc.createTextNode(value);
            newItem.appendChild(newItemt);
        } else if (wType == "radioGroup") {
            QString value = ((ScRadioGroup*)widgetList[i.key()])->getCurrentRadio();

            QDomText newItemt = doc.createTextNode(value);
            newItem.appendChild(newItemt);
        } else if (wType == "tweet") {
            if (useCDATA) {
                QDomElement username = doc.createElement("username");
                QDomCDATASection username_t = doc.createCDATASection(((twitterWidget*)widgetList[i.key()])->getUsername());

                username.appendChild(username_t);
                newItem.appendChild(username);

                QDomElement twittername = doc.createElement("twittername");
                QDomCDATASection twittername_t = doc.createCDATASection(((twitterWidget*)widgetList[i.key()])->getTwitterName());

                twittername.appendChild(twittername_t);
                newItem.appendChild(twittername);

                QDomElement tweetText = doc.createElement("text");
                QDomCDATASection tweetText_t = doc.createCDATASection(((twitterWidget*)widgetList[i.key()])->getTweetText());

                tweetText.appendChild(tweetText_t);
                newItem.appendChild(tweetText);

                QDomElement created = doc.createElement("created");
                QDomCDATASection created_t = doc.createCDATASection(((twitterWidget*)widgetList[i.key()])->getDate());

                created.appendChild(created_t);
                newItem.appendChild(created);

                QDomElement picFileName = doc.createElement("picFileName");
                QDomCDATASection picFileName_t = doc.createCDATASection(((twitterWidget*)widgetList[i.key()])->getProfilePicFilename());

                picFileName.appendChild(picFileName_t);
                newItem.appendChild(picFileName);
            } else {
                QDomElement username = doc.createElement("username");
                QDomText username_t = doc.createTextNode(((twitterWidget*)widgetList[i.key()])->getUsername());

                username.appendChild(username_t);
                newItem.appendChild(username);

                QDomElement twittername = doc.createElement("twittername");
                QDomText twittername_t = doc.createTextNode(((twitterWidget*)widgetList[i.key()])->getTwitterName());

                twittername.appendChild(twittername_t);
                newItem.appendChild(twittername);

                QDomElement tweetText = doc.createElement("text");
                QDomText tweetText_t = doc.createTextNode(((twitterWidget*)widgetList[i.key()])->getTweetText());

                tweetText.appendChild(tweetText_t);
                newItem.appendChild(tweetText);

                QDomElement created = doc.createElement("created");
                QDomText created_t = doc.createTextNode(((twitterWidget*)widgetList[i.key()])->getDate());

                created.appendChild(created_t);
                newItem.appendChild(created);

                QDomElement picFileName = doc.createElement("picFileName");
                QDomText picFileName_t = doc.createTextNode(((twitterWidget*)widgetList[i.key()])->getProfilePicFilename());

                picFileName.appendChild(picFileName_t);
                newItem.appendChild(picFileName);
            }
        } else if (wType == "tsButton") {
            if (((ScTSButton*)widgetList[i.key()])->isActive()) {
                ((ScTSButton*)widgetList[i.key()])->setTimeStamp(timestamp_t);
                ((ScTSButton*)widgetList[i.key()])->setActive(false);
            }

            QDomText newItemt = doc.createTextNode(QString::number(((ScTSButton*)widgetList[i.key()])->getTimeStamp()));
            newItem.appendChild(newItemt);
        }

    }

    return doc.toString();
}

QString MainWindow::saveJSON() {

    QJsonObject Obj;

    QDateTime current = QDateTime::currentDateTime();
    uint timestamp_t = current.toTime_t();

    Obj["timestamp"] = QString::number(timestamp_t);

    QMapIterator<QString, QObject *> i(widgetList);
    while (i.hasNext()) {
        i.next();
        QString wType = widgetType[i.key()];

        if (wType == "lineEdit") {
            Obj[i.key()] = ((ScLineEdit*)widgetList[i.key()])->text();
        } else if (wType == "spinBox") {
            Obj[i.key()] = ((QSpinBox*)widgetList[i.key()])->text();
        } else if (wType == "checkBox") {
            QString checked = "0";
            if (((QCheckBox*)widgetList[i.key()])->isChecked()) {
                checked = "1";
            }
            Obj[i.key()] = checked;
        } else if (wType == "comboBox") {
            int currentIndex = ((QComboBox*)widgetList[i.key()])->currentIndex();
            QString value;
            QVariant data = ((QComboBox*)widgetList[i.key()])->itemData(currentIndex);
            if (data.isNull())
                value = ((QComboBox*)widgetList[i.key()])->itemText(currentIndex);
            else
                value = data.toString();

            Obj[i.key()] = value;
        } else if (wType == "radioGroup") {
            QString value = ((ScRadioGroup*)widgetList[i.key()])->getCurrentRadio();
            Obj[i.key()] = value;
        } else if (wType == "tweet") {
            QJsonObject tweet;

            tweet["username"] = ((twitterWidget*)widgetList[i.key()])->getUsername();
            tweet["twittername"] = ((twitterWidget*)widgetList[i.key()])->getTwitterName();
            tweet["text"] = ((twitterWidget*)widgetList[i.key()])->getTweetText();
            tweet["created"] = ((twitterWidget*)widgetList[i.key()])->getDate();
            tweet["picFileName"] = ((twitterWidget*)widgetList[i.key()])->getProfilePicFilename();

            Obj[i.key()] = tweet;

        } else if (wType == "tsButton") {
            if (((ScTSButton*)widgetList[i.key()])->isActive()) {
                ((ScTSButton*)widgetList[i.key()])->setTimeStamp(timestamp_t);
                ((ScTSButton*)widgetList[i.key()])->setActive(false);
            }
            Obj[i.key()] = QString::number(((ScTSButton*)widgetList[i.key()])->getTimeStamp());
        }

    }

    return QJsonDocument(Obj).toJson(QJsonDocument::Indented);

}

void MainWindow::resetFields(QString widget)
{

    QListIterator<QString> i(resetList[widget]);
    while (i.hasNext()) {
        QString key = i.next();
        if (widgetType[key] == "spinBox") {
            ((QSpinBox*)widgetList[key])->setValue(0);
        } else if (widgetType[key] == "lineEdit") {
            ((ScLineEdit*)widgetList[key])->setText("");
        } else if (widgetType[key] == "checkBox") {
            ((QCheckBox*)widgetList[key])->setChecked(false);
        }
    }
}

void MainWindow::swapFields(QString widget)
{

    QString swSet1 = swapSets[widget][0];
    QString swSet2 = swapSets[widget][1];


    QList<QString> swList1 = swapList[swSet1];
    QList<QString> swList2 = swapList[swSet2];

    for (int i = 0; i < swList1.size(); ++i) {
        QString currField = swList1[i];
        QString newField = swList2[i];
        QString tempData;

        if (widgetType[currField] == "lineEdit"){
            tempData = ((ScLineEdit*)widgetList[currField])->text();
            ((ScLineEdit*)widgetList[currField])->setText(((ScLineEdit*)widgetList[newField])->text());
            ((ScLineEdit*)widgetList[newField])->setText(tempData);
        } else if (widgetType[currField] == "spinBox") {
            tempData = ((QSpinBox*)widgetList[currField])->text();
            ((QSpinBox*)widgetList[currField])->setValue(((QSpinBox*)widgetList[newField])->text().toInt());
            ((QSpinBox*)widgetList[newField])->setValue(tempData.toInt());
        } else if (widgetType[currField] == "checkBox") {
            bool tempCheck = ((QCheckBox*)widgetList[currField])->isChecked();
            ((QCheckBox*)widgetList[currField])->setChecked(((QCheckBox*)widgetList[newField])->isChecked());
            ((QCheckBox*)widgetList[newField])->setChecked(tempCheck);
        }
     }

}

void MainWindow::openConfig() {
    cWindow->setConfig(settings);
    cWindow->show();

    if (cWindow->exec() == 1) {
        QMap<QString, QString> configSettings = cWindow->getConfig();

        settings["xsplitPath"] = configSettings["xsplitPath"];
        settings["layoutPath"] = configSettings["layoutPath"];
        settings["useCDATA"] = configSettings["useCDATA"];
        settings["format"] = configSettings["format"];

        if (settings["useCDATA"] == "1") {
            useCDATA = true;
        } else {
            useCDATA = false;
        }

        saveFormat = settings["format"].toInt();

        if(saveFormat < 1 || saveFormat > 3) {
            saveFormat = SC_XML;
        }

        saveSettings();

        loadLayout();

        loadData();
    }
}

void MainWindow::toggleAlwaysOnTop(bool on_top) {

    #ifdef Q_OS_WIN
    HWND hWnd = (HWND)this->winId();

    if (on_top)
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    else
        SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    #else
    Qt::WindowFlags oldflags = windowFlags(), newflags;

    if( on_top )
        newflags = oldflags | Qt::WindowStaysOnTopHint;
    else
        newflags = oldflags & ~Qt::WindowStaysOnTopHint;

    setWindowFlags( newflags );
    show();
    #endif
}

void MainWindow::loadLayout() {

    layoutIterator = 0;

    clearMaps();
    QStringList errors;
    QString parseError;
    int parseErrorLine;
    int parseErrorColumn;

    QDomDocument doc;

    QFile file(settings["layoutPath"]);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        doc.setContent(&file,&parseError,&parseErrorLine,&parseErrorColumn);

        file.close();
    } else {

        doc = getDefaultLayout();

    }

    if (parseError.length() > 0) {
        errors << "XML Error:\n" + parseError + "\n\nLine:" + QString::number(parseErrorLine) + "\nColumn:" + QString::number(parseErrorColumn);
    } else {
        errors << checkLayout(doc);
    }

    if (errors.length() > 0) {

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        QString errorMessage = errors.join("\n");
        errorMessage += "\n\nLoading default layout";
        msgBox.setText(errorMessage);
        msgBox.exec();

        doc = getDefaultLayout();
    }

    QDomElement layout = doc.namedItem("layout").toElement();

    //Set up the main window
    int layoutWidth = layout.attribute("width").toInt();
    int layoutHeight = layout.attribute("height").toInt();

    if (layoutWidth < 50) {
        layoutWidth = 50;
    }
    if (layoutHeight < 50) {
        layoutHeight = 50;
    }


    resize(layoutWidth, layoutHeight);
    setFixedSize(layoutWidth, layoutHeight);

    if(layout.attribute("tabbed") == "1") {
        centralWidget = new QTabWidget(this);
    } else {
        centralWidget = new QWidget(this);
    }

    setCentralWidget(centralWidget);

    if(layout.attribute("tabbed") == "1"){
        parseTabLayout(layout,centralWidget);
    } else {
        parseLayout(layout, centralWidget);
    }

    //Do ToolBar
    QDomNode toolBarNode = layout.namedItem("toolBar");

    if (!toolBarNode.isNull()) {
        parseToolBar(toolBarNode);
    }

    //connect signal mappers

    connect (resetMapper, SIGNAL(mapped(QString)), this, SLOT(resetFields(QString))) ;
    connect (swapMapper, SIGNAL(mapped(QString)), this, SLOT(swapFields(QString))) ;
    connect (tsMapper, SIGNAL(mapped(QString)), this, SLOT(tsClick(QString))) ;

}

void MainWindow::parseLayout(QDomElement element, QWidget *parent) {
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        QString tagName = child.toElement().tagName();
        if (tagName == "label") {
            addLabel(child.toElement(), parent);
        } else if (tagName == "line") {
            addLine(child.toElement(), parent);
        } else if (tagName == "button") {
            addButton(child.toElement(), parent);
        } else if (tagName == "lineEdit") {
            addLineEdit(child.toElement(), parent);
        } else if (tagName == "spinBox") {
            addSpinBox(child.toElement(), parent);
        } else if (tagName == "checkBox") {
            addCheckBox(child.toElement(), parent);
        } else if (tagName == "radioGroup") {
            addRadioGroup(child.toElement(), parent);
        } else if (tagName == "comboBox") {
            addComboBox(child.toElement(), parent);
        } else if (tagName == "tweet") {
            addTweetWidget(child.toElement(), parent);
        } else if (tagName == "tabSet") {
            QString newTabSet = addTabWidget(child.toElement(), parent);
            parseTabLayout(child.toElement(), visualList[newTabSet]);
        }

        child = child.nextSibling();
    }
}

void MainWindow::parseTabLayout(QDomElement element, QWidget *parent) {
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        QString tagName = child.toElement().tagName();
        if(tagName == "tab") {
            QString newTabName = child.toElement().attribute("name");
            QString newTab = "tab"+QString::number(layoutIterator);

            visualList[newTab] = new QWidget(parent);

            parseLayout(child.toElement(),visualList[newTab]);

            if (child.toElement().attribute("scrollable") == "1") {
                visualList[newTab+"Scroll"] = new QScrollArea(parent);
                visualList[newTab]->adjustSize();
                ((QScrollArea*)visualList[newTab+"Scroll"])->setWidget(((QWidget*)visualList[newTab]));
                ((QScrollArea*)visualList[newTab+"Scroll"])->setFrameShape(QFrame::NoFrame);
                ((QTabWidget*)parent)->addTab(visualList[newTab+"Scroll"],newTabName);
            } else {
                ((QTabWidget*)parent)->addTab(visualList[newTab],newTabName);
            }

            layoutIterator++;
        }

        child = child.nextSibling();
    }
}

void MainWindow::parseToolBar(QDomNode toolBarNode) {

    QDomNode child = toolBarNode.firstChild();
    while (!child.isNull()) {
        QString tagName = child.toElement().tagName();

        if (tagName == "label") {
            //add labels
            QString newLabel = "label"+QString::number(layoutIterator);
            visualList[newLabel] = new QLabel();
            visualList[newLabel]->setObjectName(newLabel);
            ((QLabel*)visualList[newLabel])->setText(child.toElement().text());

            toolBar->addWidget(((QLabel*)visualList[newLabel]));

            layoutIterator++;
            //end labels
        } else if (tagName == "comboBox") {
            //add comboboxes
            QDomElement comboBoxElement = child.toElement();
            QString newComboBox = comboBoxElement.attribute("id");
            widgetType[newComboBox] = "comboBox";
            widgetList[newComboBox] = new QComboBox();
            widgetList[newComboBox]->setObjectName(newComboBox);

            int comboBoxWidth = 100;
            if (comboBoxElement.hasAttribute("width")) {
                comboBoxWidth = comboBoxElement.attribute("width").toInt();
            }
            ((QComboBox*)widgetList[newComboBox])->setMinimumWidth(comboBoxWidth);

            if (comboBoxElement.attribute("editable") == "1" || comboBoxElement.attribute("editable") == "true") {
                ((QComboBox*)widgetList[newComboBox])->setEditable(true);

            }

            toolBar->addWidget(((QComboBox*)widgetList[newComboBox]));

            QDomNode combochild = comboBoxElement.firstChild();
            int selectedIndex = 0;
            for (int itemIndex = 0; !combochild.isNull(); itemIndex++) {
                QDomElement itemElement = combochild.toElement();
                if (itemElement.tagName() == "comboItem") {

                    QString text = itemElement.text();
                    QString value = itemElement.attribute("value");
                    if (value.isNull())
                        value = text;

                    ((QComboBox*)widgetList[newComboBox])->addItem(text, value);

                    if (itemElement.attribute("selected") == "true")
                        selectedIndex = itemIndex;
                }

                combochild = combochild.nextSibling();
            }

            ((QComboBox*)widgetList[newComboBox])->setCurrentIndex(selectedIndex);
            //end comboboxes
        }

        child = child.nextSibling();
    }

}

void MainWindow::addLabel(QDomElement element, QWidget *parent) {

    QString newLabel = "label"+QString::number(layoutIterator);
    visualList[newLabel] = new QLabel(parent);
    visualList[newLabel]->setObjectName(newLabel);
    visualList[newLabel]->setGeometry(QRect(element.attribute("x").toInt(),
                                                          element.attribute("y").toInt(),
                                                          element.attribute("width").toInt(),
                                                          element.attribute("height").toInt()));
    ((QLabel*)visualList[newLabel])->setText(element.text());

    layoutIterator++;
}

void MainWindow::addTweetWidget(QDomElement element, QWidget *parent) {

    QString newTweet = element.attribute("id");
    widgetList[newTweet] = new twitterWidget(parent);
    widgetType[newTweet] = "tweet";
    widgetList[newTweet]->setObjectName(newTweet);
    ((twitterWidget*)widgetList[newTweet])->setGeometry(QRect(element.attribute("x").toInt(),
                                                          element.attribute("y").toInt(),
                                                          element.attribute("width").toInt(),
                                                          element.attribute("height").toInt()));

    QString picPath = "twitter"; // default path to twitter so the xsplit directory isn't filled with pictures

    if(element.attribute("picPath") != "") {
        picPath = element.attribute("picPath");
    }

    QDir newPath(element.attribute(picPath));

    if (!newPath.isAbsolute()) {
        QString path = settings["xsplitPath"] + element.attribute("picPath");
        newPath.setPath(path);
    }

    if(!newPath.exists()) {
        newPath.mkpath(newPath.path());
    }

    ((twitterWidget*)widgetList[newTweet])->setPath(newPath.path() + "/");

    layoutIterator++;
}

void MainWindow::addLine(QDomElement element, QWidget *parent) {

    QString newLine = "line"+QString::number(layoutIterator);
    visualList[newLine] = new QLabel(parent);
    visualList[newLine]->setObjectName(newLine);
    visualList[newLine]->setGeometry(QRect(element.attribute("x").toInt(),
                                                          element.attribute("y").toInt(),
                                                          element.attribute("width").toInt(),
                                                          element.attribute("height").toInt()));
    ((QFrame*)visualList[newLine])->setFrameShape(QFrame::HLine);
    ((QFrame*)visualList[newLine])->setFrameShadow(QFrame::Sunken);

    layoutIterator++;
}

void MainWindow::addCheckBox(QDomElement element, QWidget *parent) {

    QString newCheckBox = element.attribute("id");
    widgetType[newCheckBox] = "checkBox";
    widgetList[newCheckBox] = new QCheckBox(parent);
    widgetList[newCheckBox]->setObjectName(newCheckBox);
    ((QCheckBox*)widgetList[newCheckBox])->setGeometry(QRect(element.attribute("x").toInt(),
                                                          element.attribute("y").toInt(),
                                                          element.attribute("width").toInt(),
                                                          element.attribute("height").toInt()));
    ((QCheckBox*)widgetList[newCheckBox])->setText(element.text());

}

void MainWindow::addComboBox(QDomElement element, QWidget *parent) {

    QString newComboBox = element.attribute("id");
    widgetType[newComboBox] = "comboBox";
    widgetList[newComboBox] = new QComboBox(parent);
    widgetList[newComboBox]->setObjectName(newComboBox);

    ((QComboBox*)widgetList[newComboBox])->setGeometry(QRect(element.attribute("x").toInt(),
                                                          element.attribute("y").toInt(),
                                                          element.attribute("width").toInt(),
                                                          element.attribute("height").toInt()));

    if (element.attribute("editable") == "true") {
        ((QComboBox*)widgetList[newComboBox])->setEditable(true);

    }

    QDomNode child = element.firstChild();
    int selectedIndex = 0;
    for (int itemIndex = 0; !child.isNull(); itemIndex++) {
        QDomElement itemElement = child.toElement();
        if (itemElement.tagName() == "comboItem") {

            QString text = itemElement.text();
            QString value = itemElement.attribute("value");
            if (value.isNull())
                value = text;

            ((QComboBox*)widgetList[newComboBox])->addItem(text, value);

            if (itemElement.attribute("selected") == "true")
                selectedIndex = itemIndex;
        }

        child = child.nextSibling();
    }

    ((QComboBox*)widgetList[newComboBox])->setCurrentIndex(selectedIndex);

}

void MainWindow::addRadioGroup(QDomElement element, QWidget *parent) {

    QString newRadioGroup = element.attribute("id");
    widgetType[newRadioGroup] = "radioGroup";
    widgetList[newRadioGroup] = new ScRadioGroup(parent);
    widgetList[newRadioGroup]->setObjectName(newRadioGroup);

    QDomNode child = element.firstChild();
    int radioIterator = 0;
    while (!child.isNull()) {
        if (child.toElement().tagName() == "radioButton"){

            QDomElement radioButton = child.toElement();
            int x = radioButton.attribute("x").toInt();
            int y = radioButton.attribute("y").toInt();
            int width = radioButton.attribute("width").toInt();
            int height = radioButton.attribute("height").toInt();
            QString text = radioButton.text();
            QString value = radioButton.attribute("value");
            QString radioName = "radio" + value;

            QRadioButton *newRadioButton = new QRadioButton(text,parent);
            newRadioButton->setGeometry(QRect(x,y,width,height));
            newRadioButton->setObjectName(radioName);
            if(radioIterator == 0)
                newRadioButton->setChecked(true);
            \
            ((ScRadioGroup*)widgetList[newRadioGroup])->addButton(newRadioButton,radioIterator);
            ((ScRadioGroup*)widgetList[newRadioGroup])->setValue(radioIterator,value);
            radioIterator++;

        }

        child = child.nextSibling();
    }

}

void MainWindow::addButton(QDomElement element, QWidget *parent) {
    if (element.attribute("type") == "reset") {
        QString newButton = element.attribute("id");

        QList<QString> resetL = CSV::parseFromString(element.attribute("reset"))[0];
        resetList.insert(newButton,resetL);

        visualList[newButton] = new QPushButton(parent);
        visualList[newButton]->setObjectName(newButton);
        visualList[newButton]->setGeometry(QRect(element.attribute("x").toInt(),
                                           element.attribute("y").toInt(),
                                           element.attribute("width").toInt(),
                                           element.attribute("height").toInt()));
        ((QPushButton*)visualList[newButton])->setText(element.text());
        if (!element.attribute("tooltip").isEmpty()) {
            ((QPushButton*)visualList[newButton])->setToolTip(element.attribute("tooltip"));
        }

        connect(((QPushButton*)visualList[newButton]), SIGNAL(clicked()), resetMapper, SLOT(map()));
        resetMapper -> setMapping (((QPushButton*)visualList[newButton]), newButton) ;


    } else if (element.attribute("type") == "swap") {

        QString newButton = element.attribute("id");

        QList<QString> swapl1 = CSV::parseFromString(element.attribute("swapSet1"))[0];
        QList<QString> swapl2 = CSV::parseFromString(element.attribute("swapSet2"))[0];

        QList<QString> swapset;
        swapset.insert(0,newButton + "1");
        swapset.insert(1,newButton + "2");

        swapSets.insert(newButton,swapset);

        swapList.insert(newButton + "1",swapl1);

        swapList.insert(newButton + "2",swapl2);

        visualList[newButton] = new QPushButton(parent);
        visualList[newButton]->setObjectName(newButton);
        visualList[newButton]->setGeometry(QRect(element.attribute("x").toInt(),
                                                 element.attribute("y").toInt(),
                                                 element.attribute("width").toInt(),
                                                 element.attribute("height").toInt()));
        ((QPushButton*)visualList[newButton])->setText(element.text());
        if (!element.attribute("tooltip").isEmpty()) {
            ((QPushButton*)visualList[newButton])->setToolTip(element.attribute("tooltip"));
        }

        connect(((QPushButton*)visualList[newButton]), SIGNAL(clicked()), swapMapper, SLOT(map()));
        swapMapper -> setMapping (((QPushButton*)visualList[newButton]), newButton) ;



    } else if (element.attribute("type") == "timestamp") {
        bool nSaveOnClick = false;

        if (element.attribute("saveonclick") == "true" || element.attribute("saveonclick") == "1") {
            nSaveOnClick = true;
        }
        QString newButton = element.attribute("id");
        widgetType[newButton] = "tsButton";

        widgetList[newButton] = new ScTSButton(nSaveOnClick,parent);
        widgetList[newButton]->setObjectName(newButton);
        ((ScTSButton*)widgetList[newButton])->setGeometry(QRect(element.attribute("x").toInt(),
                                           element.attribute("y").toInt(),
                                           element.attribute("width").toInt(),
                                           element.attribute("height").toInt()));

        ((ScTSButton*)widgetList[newButton])->setText(element.text());

        if (!element.attribute("tooltip").isEmpty()) {
            ((ScTSButton*)widgetList[newButton])->setToolTip(element.attribute("tooltip"));
        }

        connect(((ScTSButton*)widgetList[newButton]), SIGNAL(clicked()), tsMapper, SLOT(map()));
        tsMapper -> setMapping (((ScTSButton*)widgetList[newButton]), newButton) ;
    }
}

void MainWindow::tsClick(QString tsButton) {
    if (((ScTSButton*)widgetList[tsButton])->isActive()) {
        ((ScTSButton*)widgetList[tsButton])->setActive(false);
    } else {
        ((ScTSButton*)widgetList[tsButton])->setActive(true);
    }

    if (((ScTSButton*)widgetList[tsButton])->isSaveOnClick()) {
        saveData();
    }
}

void MainWindow::addLineEdit(QDomElement element, QWidget *parent) {

    QString newLineEdit = element.attribute("id");

    widgetList[newLineEdit] = new ScLineEdit(parent);
    widgetList[newLineEdit]->setObjectName(newLineEdit);
    ((ScLineEdit*)widgetList[newLineEdit])->setGeometry(QRect(element.attribute("x").toInt(),
                                             element.attribute("y").toInt(),
                                             element.attribute("width").toInt(),
                                             element.attribute("height").toInt()));
    widgetType[newLineEdit] = "lineEdit";

    if (element.text() != "") {
        ((ScLineEdit*)widgetList[newLineEdit])->setPlaceholderText(element.text());
    }

    if(element.hasAttribute("dataSet")) {
        QString dataSetName = element.attribute("dataSet");
        if (dataSets[dataSetName].isEmpty()) {
            QString setPath = QFileInfo(settings["layoutPath"]).path() +"/"+ dataSetName;
            QList<QStringList> newDataSet = CSV::parseFromFile(setPath,"UTF-8");

            dataSets[dataSetName] = processDataSet(newDataSet);
            condensedDataSets[dataSetName] = condenseDataSet(dataSets[dataSetName]);
        }
        int dataField = 0;
        if (element.hasAttribute("dataField")) {
            dataField = element.attribute("dataField").toInt() - 1;

            for (int i = dataSets[dataSetName].length(); i <= dataField; i++) {
                QStringList newList;

                for (int i2 = 0; i2 < dataSets[dataSetName][0].length();i2++){
                    newList.insert(i2,"");
                }
                dataSets[dataSetName].insert(i,newList);
                condensedDataSets[dataSetName] = condenseDataSet(dataSets[dataSetName]);
            }

        }

        dataAssoc[newLineEdit] = dataField;
        completerList[newLineEdit] = new ScCompleter(parent);
        bool hasMaster;
        ((ScLineEdit*)widgetList[newLineEdit])->setName(newLineEdit,dataSetName);
        if (element.hasAttribute("master")) {
            QStringListModel *model = new QStringListModel(condensedDataSets[dataSetName][dataField]);
            completerList[newLineEdit]->setModel(model);
            dataMaster[element.attribute("master")].append(newLineEdit);
            ((ScLineEdit*)widgetList[newLineEdit])->setButtonVisible(false);
            hasMaster = true;
        } else {
            QStringListModel *model = new QStringListModel(dataSets[dataSetName][dataField]);
            completerList[newLineEdit]->setModel(model);
            connect(((ScLineEdit*)widgetList[newLineEdit]),SIGNAL(textChanged(QString)), this, SLOT(checkLineDataSet(QString)));
            connect(((ScLineEdit*)widgetList[newLineEdit]),SIGNAL(clearButtonClicked()), this, SLOT(removeFromDataSet()));
            hasMaster = false;

        }
        completerList[newLineEdit]->setName(newLineEdit,dataSetName,dataField,hasMaster);
        completerList[newLineEdit]->setCaseSensitivity(Qt::CaseInsensitive);
        completerList[newLineEdit]->setCompletionMode(QCompleter::PopupCompletion);

        ((ScLineEdit*)widgetList[newLineEdit])->setCompleter(completerList[newLineEdit]);

        connect(completerList[newLineEdit], SIGNAL(activated(QString)), this, SLOT(completerActivate(QString)));

    }
}

void MainWindow::completerActivate(QString item) {
    QString scSender = ((ScCompleter*)sender())->getName();
    QString scSetName = ((ScCompleter*)sender())->getSetName();
    int field = dataAssoc[scSender];
    int index = dataSets[scSetName][field].indexOf(item);

    for (int i = 0; i < dataMaster[scSender].length();i++) {
        QString id = dataMaster[scSender][i];
        int newField = dataAssoc[id];
        ((ScLineEdit*)widgetList[id])->setText(dataSets[scSetName][newField][index]);
    }
}

void MainWindow::removeFromDataSet() {
    QString scSender = ((ScLineEdit*)sender())->getName();
    QString scSetName = ((ScLineEdit*)sender())->getSetName();

    QString item = ((ScLineEdit*)sender())->text();

    int field = dataAssoc[scSender];
    int index = dataSets[scSetName][field].indexOf(item);

    int numSets = dataSets[scSetName].length();

    for (int i = 0; i < numSets; i++) {
        dataSets[scSetName][i].removeAt(index);
    }

    condensedDataSets[scSetName] = condenseDataSet(dataSets[scSetName]);

    int numSlave = dataMaster[scSender].length();
    for (int i = 0; i < numSlave; i++) {
        QString widget = dataMaster[scSender][i];
        ((ScLineEdit*)widgetList[widget])->clear();
    }

    removedSetQueue.append(scSetName);

    updateCompleters();

    ((ScLineEdit*)sender())->clear();


}

void MainWindow::updateCompleters() {
    QMapIterator<QString, ScCompleter *> i(completerList);
    while (i.hasNext()) {
        i.next();
        QString name = i.key();
        QString setName = completerList[name]->getSetName();
        int dataField = completerList[name]->getDataField();

        if (completerList[name]->hasMaster() == true) {
            QStringListModel *model = new QStringListModel(condensedDataSets[setName][dataField]);
            completerList[name]->setModel(model);
        } else {
            QStringListModel *model = new QStringListModel(dataSets[setName][dataField]);
            completerList[name]->setModel(model);
        }
    }
}

void MainWindow::checkLineDataSet(QString line) {
    QString scSender = ((ScLineEdit*)sender())->getName();
    QString scSetName = ((ScLineEdit*)sender())->getSetName();
    int field = dataAssoc[scSender];
    int index = dataSets[scSetName][field].indexOf(line);

    if(index != -1) {
        ((ScLineEdit*)widgetList[scSender])->setButtonVisible(true);
    } else {
        ((ScLineEdit*)widgetList[scSender])->setButtonVisible(false);
    }
}

QList<QStringList> MainWindow::processDataSet(QList<QStringList> oldSet) {
    int items = oldSet.length() - 1;
    int sets = oldSet[0].length() - 1;

    //this bit is confusing should probably fix it
    bool empty = true;
    for (int i = 0; i <= items; i++) {
        if (items > 0 || items == -1)
            empty = false;
        if (items == 0 && oldSet[0][i] != "")
            empty = false;
    }

    QList<QStringList> newSet;
    for (int i = 0; i <= sets; i++){
        QStringList newList;
        for (int i2 = 0; i2 <= items; i2++){
            if (!empty)
                newList.append(oldSet[i2][i]);
        }
        newSet.append(newList);
    }
    return newSet;
}

QList<QStringList> MainWindow::condenseDataSet(QList<QStringList> oldSet) {
    QList<QStringList> newSet;

    int sets = oldSet.length() - 1;
    for (int i = 0; i <= sets; i++){
        QStringList newList = oldSet[i].toSet().toList();
        newSet.append(newList);
    }

    return newSet;
}

void MainWindow::saveDataSets() {
    QMapIterator<QString, ScCompleter *> i(completerList);
    QStringList updatedSets;
    while (i.hasNext()) {
        i.next();
        QString name = i.key();
        QString setName = completerList[name]->getSetName();
        int dataField = completerList[name]->getDataField();

        if (completerList[name]->hasMaster() == false) { //if it's a master
            //check if current value in in dataSet
            QString currentVal = ((ScLineEdit*)widgetList[name])->text();
            int currIndex =  dataSets[setName][dataField].indexOf(currentVal);

            if (currIndex == -1 && currentVal != "") {
                //set all to blank first
                int numFields = dataSets[setName].length();
                for (int i = 0; i < numFields; i++) {
                    if (!checkDataSet1Blank(setName))
                        dataSets[setName][i].append("");
                }

                int newIndex = dataSets[setName][dataField].length() - 1;

                QString newValue = ((ScLineEdit*)widgetList[name])->text();
                dataSets[setName][dataField][newIndex] = newValue;

                //find each field that has name as master
                int slaveNum = dataMaster[name].length();
                for (int i = 0; i < slaveNum; i++) {
                    QString slaveName = dataMaster[name][i];
                    int field = dataAssoc[slaveName];
                    if (field != dataField) {
                        QString newValue = ((ScLineEdit*)widgetList[slaveName])->text();
                        dataSets[setName][field][newIndex] = newValue;
                    }
                }
                if (updatedSets.indexOf(setName) == -1)
                    updatedSets.append(setName);

                ((ScLineEdit*)widgetList[name])->setButtonVisible(true);

            } else if (currentVal != "") { //if has in set
                //find each field that has name as master
                int slaveNum = dataMaster[name].length();
                for (int i = 0; i < slaveNum; i++) {
                    QString slaveName = dataMaster[name][i];
                    int field = dataAssoc[slaveName];
                    if (field != dataField) {
                        QString newValue = ((ScLineEdit*)widgetList[slaveName])->text();
                        if (dataSets[setName][field][currIndex] != newValue){ // if not new value update
                            dataSets[setName][field][currIndex] = newValue;
                            if (updatedSets.indexOf(setName) == -1)
                                updatedSets.append(setName);
                        }//end update
                    }
                }


            }// end if has in set


        }// end if has master


    }

    if (!removedSetQueue.isEmpty()) {
        updatedSets.append(removedSetQueue);
        removedSetQueue.clear();
    }

    int numUpdate = updatedSets.length();

    for (int i = 0; i < numUpdate; i++) {
        condensedDataSets[updatedSets[i]] = condenseDataSet(dataSets[updatedSets[i]]);

        QList<QStringList> newList = processDataSet(dataSets[updatedSets[i]]);

        QString outputFile = QFileInfo(settings["layoutPath"]).path() +"/"+ updatedSets[i];
        CSV::write(newList,outputFile,"UTF-8");

    }

    updateCompleters();
}

void MainWindow::addSpinBox(QDomElement element, QWidget *parent) {

    QString newSpinBox = element.attribute("id");

    widgetList[newSpinBox] = new QSpinBox(parent);
    widgetList[newSpinBox]->setObjectName(newSpinBox);
    ((QSpinBox*)widgetList[newSpinBox])->setGeometry(QRect(element.attribute("x").toInt(),
                                              element.attribute("y").toInt(),
                                              element.attribute("width").toInt(),
                                              element.attribute("height").toInt()));
    if(!element.attribute("maximum").isEmpty()) {
        ((QSpinBox*)widgetList[newSpinBox])->setMaximum(element.attribute("maximum").toInt());
    }
    widgetType[newSpinBox] = "spinBox";

}

QString MainWindow::addTabWidget(QDomElement element, QWidget *parent) {

    QString tabSet = "tabSet"+QString::number(layoutIterator);
    visualList[tabSet] = new QTabWidget(parent);
    visualList[tabSet]->setObjectName(tabSet);
    visualList[tabSet]->setGeometry(QRect(element.attribute("x").toInt(),
                                                          element.attribute("y").toInt(),
                                                          element.attribute("width").toInt(),
                                                          element.attribute("height").toInt()));

    layoutIterator++;
    return tabSet;
}

QDomDocument MainWindow::getDefaultLayout() {
    QString xmlcontent = "<!DOCTYPE StreamControlLayout>\r\n<layout width=\"400\" height=\"140\" tabbed=\"1\">\r\n <toolBar>\r\n  <label>Game</label>\r\n  <comboBox id=\"game\" editable=\"true\">\r\n   <comboItem>Super Street Fighter IV</comboItem>\r\n   <comboItem>Ultimate Marvel vs Capcom 3</comboItem>\r\n   <comboItem>Persona 4: Arena</comboItem>\r\n   <comboItem>Tekken Tag Tournament 2</comboItem>\r\n   <comboItem>King of Fighters XIII</comboItem>\r\n  </comboBox>\r\n </toolBar>\r\n <tab name=\"Match Info\">\r\n  <label x=\"10\" y=\"14\" width=\"46\" height=\"13\">Player 1</label>\r\n  <label x=\"10\" y=\"44\" width=\"46\" height=\"13\">Player 2</label>\r\n  <label x=\"300\" y=\"14\" width=\"46\" height=\"13\">Rounds</label>\r\n  <lineEdit id=\"pName1\" x=\"60\" y=\"10\" width=\"171\" height=\"20\" />\r\n  <lineEdit id=\"pName2\" x=\"60\" y=\"40\" width=\"171\" height=\"20\" />\r\n  <spinBox id=\"pScore1\" x=\"250\" y=\"10\" width=\"42\" height=\"22\" maximum=\"999\" />\r\n  <spinBox id=\"pScore2\" x=\"250\" y=\"40\" width=\"42\" height=\"22\" maximum=\"999\" />\r\n  <spinBox id=\"rounds\" x=\"340\" y=\"10\" width=\"42\" height=\"22\" maximum=\"999\" />\r\n  <button type=\"reset\" x=\"300\" y=\"40\" width=\"41\" height=\"23\" tooltip=\"Reset the Scores\" id=\"reset\" reset=\"pScore1,pScore2\">Reset</button>\r\n  <button type=\"swap\" x=\"340\" y=\"40\" width=\"41\" height=\"23\" tooltip=\"Swap the Scores\" id=\"swap1\" swapSet1=\"pName1,pScore1\" swapSet2=\"pName2,pScore2\">Swap</button>\r\n </tab>\r\n <tab name=\"Commentary\">\r\n  <label x=\"10\" y=\"14\" width=\"46\" height=\"13\">Title 1</label>\r\n  <label x=\"10\" y=\"44\" width=\"46\" height=\"13\">Title 2</label>\r\n  <lineEdit id=\"cTitle1\" x=\"60\" y=\"10\" width=\"321\" height=\"20\" />\r\n  <lineEdit id=\"cTitle2\" x=\"60\" y=\"40\" width=\"321\" height=\"20\" />\r\n </tab>\r\n <tab name=\"Misc 1\">\r\n  <label x=\"10\" y=\"14\" width=\"46\" height=\"13\">mText 1</label>\r\n  <label x=\"10\" y=\"44\" width=\"46\" height=\"13\">mText 2</label>\r\n  <lineEdit id=\"mText1\" x=\"60\" y=\"10\" width=\"321\" height=\"20\" />\r\n  <lineEdit id=\"mText2\" x=\"60\" y=\"40\" width=\"321\" height=\"20\" />\r\n </tab>\r\n <tab name=\"Misc 2\">\r\n  <label x=\"10\" y=\"14\" width=\"46\" height=\"13\">mText 3</label>\r\n  <label x=\"10\" y=\"44\" width=\"46\" height=\"13\">mText 4</label>\r\n  <lineEdit id=\"mText3\" x=\"60\" y=\"10\" width=\"321\" height=\"20\" />\r\n  <lineEdit id=\"mText4\" x=\"60\" y=\"40\" width=\"321\" height=\"20\" />\r\n </tab>\r\n</layout>\r\n";
    QDomDocument doc;
    doc.setContent(xmlcontent);
    return doc;
}

void MainWindow::clearMaps() {
    QList<QAction *> tbList = toolBar->actions();

    for (int tbi = 3; tbi < tbList.length();tbi++) {
        toolBar->removeAction(tbList.at(tbi));
    }

    widgetList.clear();
    visualList.clear();
    widgetType.clear();
    resetList.clear();
    swapSets.clear();
    swapList.clear();
    dataSets.clear();
    dataAssoc.clear();
    dataMaster.clear();
    resetMapper = new QSignalMapper (this) ;
    swapMapper = new QSignalMapper (this) ;
    tsMapper = new QSignalMapper (this) ;
}

bool MainWindow::checkDataSet1Blank(QString setName) {
    bool empty = true;
    int numFields = dataSets[setName].length();
    for (int i = 0; i < numFields; i++) {
        if (dataSets[setName][i].length() > 1 || dataSets[setName][i].length() == 0)
            empty = false;
        if (dataSets[setName][i].length() == 1 && dataSets[setName][i][0] != "")
            empty = false;

    }
    return empty;
}
