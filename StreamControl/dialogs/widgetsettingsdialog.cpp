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

#include <QVBoxLayout>
#include <QLineEdit>

#include "brackettab.h"
#include "widgetsettingsdialog.h"


WidgetSettingsDialog::WidgetSettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    tabWidget = new QTabWidget;
    bracketTab = new BracketTab(settings);
    tabWidget->addTab(bracketTab, tr("Challonge"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    connect(bracketTab->challongeUsernameEdit,SIGNAL( textEdited(QString) ),this, SLOT ( saveDetails() ));
    connect(bracketTab->challongeApiKeyEdit,SIGNAL( textEdited(QString) ),this, SLOT ( saveDetails() ));
    connect(bracketTab->challongeOrganizationEdit,SIGNAL( textEdited(QString) ),this, SLOT ( saveDetails() ));

    setLayout(mainLayout);

    setWindowTitle(tr("Widget Settings"));
}

void WidgetSettingsDialog::saveDetails()
{
    settings["challonge>username"] = bracketTab->challongeUsernameEdit->text();
    settings["challonge>apiKey"] = bracketTab->challongeApiKeyEdit->text();
    settings["challonge>organization"] = bracketTab->challongeOrganizationEdit->text();
}

void WidgetSettingsDialog::setConfig(QMap<QString, QString> newSettings) {
    settings = newSettings;
    bracketTab->challongeUsernameEdit->setText(settings.value("challonge>username"));
    bracketTab->challongeApiKeyEdit->setText(settings.value("challonge>apiKey"));
    bracketTab->challongeOrganizationEdit->setText(settings.value("challonge>organization"));
}

QMap<QString, QString> WidgetSettingsDialog::getConfig() const
{
    return settings;
}
