#include "ScComboBox.h"
#include <QToolButton>
#include <QStyle>
#include <QDebug>
#include <QStringListModel>


ScComboBox::ScComboBox(QWidget *parent)
    : QComboBox(parent)
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
}

void ScComboBox::resizeEvent(QResizeEvent *)
{
    QSize sz = clearButton->sizeHint();
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    clearButton->move(rect().right() - frameWidth - sz.width() - 20,
                      (rect().bottom() + 1 - sz.height())/2);
}

void ScComboBox::setName(QString name,QString setName) {
    comboBoxName = name;
    dataSetName = setName;
}

QString ScComboBox::getName() {
    return comboBoxName;
}

QString ScComboBox::getDataSetName() {
    return dataSetName;
}
void ScComboBox::setButtonVisible(bool visible) {
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    if(visible) {
        setStyleSheet(QString("QComboBox { padding-right: %1px; } ").arg(clearButton->sizeHint().width() + frameWidth + 1));
        clearButton->setVisible(true);
    } else {
        setStyleSheet("");
        clearButton->setVisible(false);
    }
}

void ScComboBox::clearButtonSlot(){
    emit clearButtonClicked();
}

void ScComboBox::addModel(QStringListModel *model){
    QStringList list = model->stringList();
    for (int i = 0; i < list.size(); ++i) {
        QString currStr = list.at(i);
        int index = findText(currStr);
        if (index == -1) {
            addItem(currStr);
        }
    }
}
