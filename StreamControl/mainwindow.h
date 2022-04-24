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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtXml/QDomDocument>

#include "configwindow.h"
#include "dialogs/widgetsettingsdialog.h"
#include "config.h"
#include "ScCompleter.h"
#include "widgets/providerwidgetbuilder.h"

class TwitterHandler;

class QWidget;
class QSignalMapper;
class QToolBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    void loadData();
    void loadSettings();

    QWidget *centralWidget;
    QToolBar *toolBar;

public slots:

    void saveData();
    void saveSettings();
    void loadLayout();
    void reloadLayout();
    void clearMaps();
    void parseLayout(QDomElement, QWidget*);
    void parseTabLayout(QDomElement, QWidget*);
    void parseToolBar(QDomNode);
    void parseCLI(QDomNode);
    void addLabel(QDomElement, QWidget*);
    void addLine(QDomElement, QWidget*);
    void addButton(QDomElement, QWidget*);
    void addLineEdit(QDomElement, QWidget*);
    void addSpinBox(QDomElement, QWidget*);
    void addCheckBox(QDomElement, QWidget*);
    void addComboBox(QDomElement, QWidget*);
    void addRadioGroup(QDomElement, QWidget*);
    void addTweetWidget(QDomElement, QWidget*);
    void addProviderWidget(QDomElement, QWidget*, QMap<QString, QObject*> widgetList, ProviderWidgetBuilder::Provider);
    QString addTabWidget(QDomElement, QWidget*);
    QString saveXML();
    QString saveJSON();
    void loadXML();
    void loadJSON();
    QDomDocument getDefaultLayout();
    QString getValueByID(QString);
    QString parseCmd(QString);

    void saveDataSets();

    void resetFields(QString);
    void swapFields(QString);
    void tsClick(QString);
    void setButtonClick(QString);
    void openConfig();
    void openWidgetSettings();
    void toggleAlwaysOnTop(bool);
    void toggleHideReloadLayout(bool);
    void completerActivate(QString);
    void removeLineFromDataSet();
    void removeComboFromDataSet();
    void checkLineDataSet(QString);
    void checkComboDataSet(QString);

    void execCmdQueue(QList<int>);
    void doCLI();

    void updateCompleters();

    QStringList checkLayout(QDomDocument);
    QStringList checkElements(QDomElement);
    QStringList checkLabel(QDomElement);
    QStringList checkLine(QDomElement);
    QStringList checkButton(QDomElement);
    QStringList checkLineEdit(QDomElement);
    QStringList checkSpinBox(QDomElement);
    QStringList checkCheckBox(QDomElement);
    QStringList checkTabLayout(QDomElement);
    QStringList checkRadioGroup(QDomElement);
    QStringList checkTweetWidget(QDomElement);
    QStringList checkChallongeWidget(QDomElement);

    QList<QStringList> processDataSet(QList<QStringList>);
    QList<QStringList> condenseDataSet(QList<QStringList>);

    bool checkDataSet1Blank(QString);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

    void addHotkey(QString,QString,QString);
    void performHotkey(int);
    void deleteHotkeys();
    void keyPoll();

private:
    void loadSettingsFromXml(const QDomNode& element,
                             QMap<QString, QString>& settings,
                             bool appendNodeName = false,
                             QStringList prefix = QStringList());
    void setWidgetFontSize(QWidget *widget, int fontSize);

    QSignalMapper *resetMapper;
    QSignalMapper *swapMapper;
    QSignalMapper *tsMapper;
    QSignalMapper *setButtonMapper;
    int layoutIterator;
    ConfigWindow *cWindow;
    WidgetSettingsDialog *widgetSettingsDialog;
    QMap<QString, QString> settings;
    QMap<QString, QObject*> widgetList;
    QMap<QString, QWidget*> visualList;
    QMap<QString, ScCompleter*> completerList;
    QMap<QString, QString> widgetType;
    QMap<QString, QList<QString> > resetList;
    QMap<QString, QList<QString> > swapSets;
    QMap<QString, QList<QString> > swapList;
    QMap<QString, QList<QStringList> > dataSets;
    QMap<QString, QList<QStringList> > condensedDataSets;
    QMap<QString, int> dataAssoc;
    QMap<QString, QList<QString> > dataMaster;
    QList<QStringList> hotkeys;
    QList<int> hotkeysIndex;
    QStringList cmdList;
    QList<QStringList> cmdIgnores;
    QMap<QString, QList<int> > cmdVars;
    QMap<QString, QString > cmdOldValues;

    QStringList removedSetQueue;

    bool useCDATA;
    bool altHotkeyHandling;
    int saveFormat;
    TwitterHandler *th;
    bool needLink;

    QTimer *keyPoller;
    bool hotkeyDown;

    QAction *actionReloadLayout;
};

#endif // MAINWINDOW_H
