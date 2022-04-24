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

#include <QApplication>
#include "mainwindow.h"
#include <QPalette>
#include <QFile>
#include <QDomDocument>

int main(int argc, char *argv[])
{
    //If on Windows set Hi DPI support
    #ifdef Q_OS_WIN
        qputenv("QT_AUTO_SCREEN_SCALE_FACTOR","1");
    #endif
    QApplication a(argc, argv);    
    a.setStyle("fusion");



    QFile file("settings.xml");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QDomDocument doc;
        doc.setContent(&file);
        file.close();

        QDomNode settings = doc.namedItem("settings");
        QDomNode darkMode = settings.namedItem("darkMode");
        if (!darkMode.isNull()) {
            if (darkMode.firstChild().nodeValue() == "1") {

                QPalette darkPalette;
                darkPalette.setColor(QPalette::Window, QColor(53,53,53));
                darkPalette.setColor(QPalette::WindowText, Qt::white);
                darkPalette.setColor(QPalette::Base, QColor(25,25,25));
                darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
                darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
                darkPalette.setColor(QPalette::ToolTipText, Qt::white);
                darkPalette.setColor(QPalette::Text, Qt::white);
                darkPalette.setColor(QPalette::Button, QColor(53,53,53));
                darkPalette.setColor(QPalette::ButtonText, Qt::white);
                darkPalette.setColor(QPalette::BrightText, Qt::red);
                darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

                darkPalette.setColor(QPalette::Disabled, QPalette::Text, Qt::darkGray);
                darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, Qt::darkGray);

                darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
                darkPalette.setColor(QPalette::HighlightedText, Qt::black);

                a.setPalette(darkPalette);

                a.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
            }

        }

    }








    MainWindow mainWindow;
    mainWindow.show();
    return a.exec();
}
