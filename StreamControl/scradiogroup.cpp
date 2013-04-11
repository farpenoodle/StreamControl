#include "scradiogroup.h"
#include <QDebug>
#include <QRadioButton>

ScRadioGroup::ScRadioGroup(QWidget *parent)
    : QButtonGroup(parent)
{
}

QString ScRadioGroup::getCurrentRadio(){
    return buttonValues[checkedId()];
}

void ScRadioGroup::setValue(int index,QString value) {
    buttonValues.insert(index,value);
}

int ScRadioGroup::getIndexFromValue(QString value) {
    return buttonValues.indexOf(value);
}
