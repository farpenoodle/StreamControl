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
#include "configwindow.h"
#include <QMap>
#include <QList>
#include <QComboBox>
#include <QSignalMapper>
#include "config.h"
#include <QtXml/QDomDocument>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow();
    ~MainWindow();

    void loadData();
    void loadSettings();

    QComboBox *gameComboBox;
    QWidget *centralWidget;

public slots:

    void saveData();
    void saveSettings();
    void loadLayout();
    void clearMaps();
    void parseLayout(QDomElement, QWidget*);
    void parseTabLayout(QDomElement, QWidget*);
    void addLabel(QDomElement, QWidget*);
    void addLine(QDomElement, QWidget*);
    void addButton(QDomElement, QWidget*);
    void addLineEdit(QDomElement, QWidget*);
    void addSpinBox(QDomElement, QWidget*);
    QString addTabWidget(QDomElement, QWidget*);
    QDomDocument getDefaultLayout();

    void resetFields(QString);
    void swapFields(QString);
    void openConfig();
    void addGame();
    void delGame();
    void toggleAlwaysOnTop(bool);

private:
    QSignalMapper *resetMapper;
    QSignalMapper *swapMapper;
    int layoutIterator;
    ConfigWindow *cWindow;
    QMap<QString, QString> settings;
    QMap<QString, QWidget*> widgetList;
    QMap<QString, QWidget*> visualList;
    QMap<QString, QString> widgetType;
    QMap<QString, QList<QString> > resetList;
    QMap<QString, QList<QString> > swapSets;
    QMap<QString, QList<QString> > swapList;
    QMap<QString, QList<QString> > dataSets;
    QMap<QString, QList<QString> > dataAssoc;
    QMap<QString, QList<QString> > dataFollows;

    bool useCDATA;
};

#endif // MAINWINDOW_H
