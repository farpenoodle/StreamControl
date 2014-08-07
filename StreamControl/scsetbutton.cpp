#include "scsetbutton.h"

ScSetButton::ScSetButton(bool nSaveOnClick, QString nWidget, QString nValue, QWidget *parent) :
    QPushButton(parent)
{
    saveOnClick = nSaveOnClick;
    widget = nWidget;
    value = nValue;
}

bool ScSetButton::isSaveOnClick() {
    return saveOnClick;
}

QString ScSetButton::getWidget() {
    return widget;
}

QString ScSetButton::getValue() {
    return value;
}
