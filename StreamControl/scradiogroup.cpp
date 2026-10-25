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

bool ScRadioGroup::checkFromValue(QString value) {
    int index = buttonValues.indexOf(value);
    if (index == -1)
        return false;
    button(index)->setChecked(true);
    return true;
}
