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
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    //If on Windows set Hi DPI support
    #ifdef Q_OS_WIN
        qputenv("QT_AUTO_SCREEN_SCALE_FACTOR","1");
    #endif
    QApplication a(argc, argv);
    a.setStyle("fusion");

    bool darkModeEnabled = false;

    #ifdef Q_OS_MACOS
        QFile file(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/settings.xml");
    #else
        QFile file("settings.xml");
    #endif
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QDomDocument doc;
        doc.setContent(&file);
        file.close();

        QDomNode settings = doc.namedItem("settings");
        QDomNode darkMode = settings.namedItem("darkMode");
        if (!darkMode.isNull()) {
            if (darkMode.firstChild().nodeValue() == "1") {
                darkModeEnabled = true;

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

    if (!darkModeEnabled) {
        //Default Fusion light palette, so the OS colour scheme doesn't leak in
        const QColor windowText = Qt::black;
        const QColor backGround = QColor(239, 239, 239);
        const QColor light = backGround.lighter(150);
        const QColor mid = backGround.darker(130);
        const QColor midLight = mid.lighter(110);
        const QColor base = Qt::white;
        const QColor disabledBase(backGround);
        const QColor dark = backGround.darker(150);
        const QColor darkDisabled = QColor(209, 209, 209).darker(110);
        const QColor text = Qt::black;
        const QColor highlight = QColor(48, 140, 198);
        const QColor highlightedText = Qt::white;
        const QColor disabledText = QColor(190, 190, 190);
        const QColor button = backGround;
        const QColor shadow = dark.darker(135);
        const QColor disabledShadow = shadow.lighter(150);
        const QColor disabledHighlight(145, 145, 145);
        QColor placeholder = text;
        placeholder.setAlpha(128);

        QPalette lightPalette(windowText, backGround, light, dark, mid, text, base);
        lightPalette.setBrush(QPalette::Midlight, midLight);
        lightPalette.setBrush(QPalette::Button, button);
        lightPalette.setBrush(QPalette::Shadow, shadow);
        lightPalette.setBrush(QPalette::HighlightedText, highlightedText);

        lightPalette.setBrush(QPalette::Disabled, QPalette::Text, disabledText);
        lightPalette.setBrush(QPalette::Disabled, QPalette::WindowText, disabledText);
        lightPalette.setBrush(QPalette::Disabled, QPalette::ButtonText, disabledText);
        lightPalette.setBrush(QPalette::Disabled, QPalette::Base, disabledBase);
        lightPalette.setBrush(QPalette::Disabled, QPalette::Dark, darkDisabled);
        lightPalette.setBrush(QPalette::Disabled, QPalette::Shadow, disabledShadow);

        lightPalette.setBrush(QPalette::Active, QPalette::Highlight, highlight);
        lightPalette.setBrush(QPalette::Inactive, QPalette::Highlight, highlight);
        lightPalette.setBrush(QPalette::Disabled, QPalette::Highlight, disabledHighlight);
        lightPalette.setBrush(QPalette::PlaceholderText, placeholder);

        a.setPalette(lightPalette);
    }

    MainWindow mainWindow;
    mainWindow.show();
    return a.exec();
}
