#include <QToolButton>
#include <QStyle>
#include <QDebug>
#include "ScLineEdit.h"

ScLineEdit::ScLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    clearButton = new QToolButton(this);
    clearButton->setIcon(QIcon(QStringLiteral(":/StreamControl/icons/fugue/icons/cross-small-white.png")));
    clearButton->setCursor(Qt::ArrowCursor);
    clearButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    clearButton->hide();
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearButtonSlot()));
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    QSize msz = minimumSizeHint();
    setMinimumSize(qMax(msz.width(), clearButton->sizeHint().height() + frameWidth * 2 + 2),
                   qMax(msz.height(), clearButton->sizeHint().height() + frameWidth * 2 + 2));
    noSave = false;
}

void ScLineEdit::resizeEvent(QResizeEvent *)
{
    QSize sz = clearButton->sizeHint();
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    clearButton->move(rect().right() - frameWidth - sz.width(),
                      (rect().bottom() + 1 - sz.height())/2);
}

void ScLineEdit::setName(QString name,QString setName) {
    lineEditName = name;
    dataSetName = setName;
}

QString ScLineEdit::getName() {
    return lineEditName;
}

QString ScLineEdit::getDataSetName() {
    return dataSetName;
}
void ScLineEdit::setButtonVisible(bool visible) {
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    if(visible) {
        setStyleSheet(QString("QLineEdit { padding-right: %1px; } ").arg(clearButton->sizeHint().width() + frameWidth + 1));
        clearButton->setVisible(true);
    } else {
        setStyleSheet("");
        clearButton->setVisible(false);
    }
}

void ScLineEdit::clearButtonSlot(){
    emit clearButtonClicked();
}

void ScLineEdit::setNoSaveOnChange(bool noSaveVal) {
    noSave = noSaveVal;
}

bool ScLineEdit::noSaveOnChange() {
    return noSave;
}
