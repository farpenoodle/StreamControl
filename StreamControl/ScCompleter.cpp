#include "ScCompleter.h"



ScCompleter::ScCompleter(QObject* parent) :
    QCompleter(parent)
{
}

void ScCompleter::setName(QString name,QString setName) {
    lineEditName = name;
    dataSetName = setName;
}

QString ScCompleter::getName() {
    return lineEditName;
}

QString ScCompleter::getSetName() {
    return dataSetName;
}
