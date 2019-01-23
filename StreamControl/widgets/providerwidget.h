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

#ifndef WIDGETS_PROVIDERWIDGET_H
#define WIDGETS_PROVIDERWIDGET_H

#include <QWidget>

class ProviderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProviderWidget(QWidget *parent);

signals:

public slots:
    virtual void fetchTournaments() = 0;
    virtual void fetchMatches() = 0;
    virtual void processTournamentListJson() = 0;
    virtual void processTournamentJson() = 0;
    virtual void setMatchData() = 0;
    virtual void setBracketData() = 0;
    virtual void updateCustomIdBoxState() = 0;
};

#endif // WIDGETS_PROVIDERWIDGET_H
