#include "ScCompleter.h"



ScCompleter::ScCompleter(QObject* parent) :
    QCompleter(parent)
{
}

void ScCompleter::setName(QString name,QString setName,int field, bool mast) {
    widgetName = name;
    dataSetName = setName;
    dataSetField = field;
    hMaster = mast;
}

QString ScCompleter::getName() {
    return widgetName;
}

QString ScCompleter::getDataSetName() {
    return dataSetName;
}


int ScCompleter::getDataField() {
    return dataSetField;
}

bool ScCompleter::hasMaster() {
    return hMaster;
}
