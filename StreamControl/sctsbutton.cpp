#include "sctsbutton.h"
#include <QStyle>
#include <QDebug>

ScTSButton::ScTSButton(bool nSaveOnClick,QWidget *parent) :
    QPushButton(parent)
{
    timestamp = 0;
    saveOnClick = nSaveOnClick;
    active = false;
}

bool ScTSButton::isActive() {
    return active;
}

bool ScTSButton::isSaveOnClick() {
    return saveOnClick;
}

void ScTSButton::setActive(bool nActive) {
    if (nActive == true) {
        this->setStyleSheet("background-color: red");
        qDebug() << "Yup";
        active = true;
    } else {
        this->setStyleSheet("background-color: none");
        active = false;
        qDebug() << "Nop";
    }
}

uint ScTSButton::getTimeStamp() {
    return timestamp;
}

void ScTSButton::setTimeStamp(uint nTimeStamp) {
    timestamp = nTimeStamp;
}
