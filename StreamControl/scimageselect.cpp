#include <QGridLayout>
#include <QDir>

#include "scimageselect.h"

ScImageSelect::ScImageSelect(QWidget *parent, QString path, QString defaultImageSubPath, int optionWidth, int optionHeight, int optionsColumns) : QPushButton(parent)
{
    this->path = path.endsWith('/') ? path : path + "/";
    if (!defaultImageSubPath.isEmpty()) {
        this->selectedImagePath = this->path + defaultImageSubPath;
    }
    this->optionWidth = optionWidth;
    this->optionHeight = optionHeight;
    this->optionsColumns = optionsColumns;
    this->setIcon(QIcon(this->selectedImagePath));
    optionsWidget = new QWidget(this->parentWidget());
    connect(this, SIGNAL(clicked()), this, SLOT(displayOptions()));
}

void ScImageSelect::displayOptions() {
    // if options are already displayed, hide them and return
    if (!optionsWidget->findChildren<QPushButton*>().isEmpty()) {
        qDeleteAll(optionsWidget->findChildren<QPushButton*>());
        return;
    }

    qDeleteAll(optionsWidget->findChildren<QPushButton*>());
    QDir dir = QDir(path);
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.bmp";
    QStringList options = dir.entryList(filters, QDir::Files|QDir::NoDotAndDotDot);
    for (int i = 0; i < options.size(); i++) {
        QPushButton *optionButton = new QPushButton(optionsWidget);
        optionButton->setGeometry(QRect(optionWidth * (i % 8),
                                        optionHeight * (i/8),
                                        optionWidth,
                                        optionHeight));
        optionButton->setIcon(QIcon(path + options[i]));
        optionButton->setIconSize(optionButton->size());
        optionButton->setObjectName(path + options[i]);
        connect(optionButton, SIGNAL(clicked()), this, SLOT(selectOption()));
        optionButton->show();
    }
    optionsWidget->adjustSize();
    optionsWidget->move(this->geometry().center().x() - (optionsWidget->width() / 2),
                        this->geometry().bottom());
    optionsWidget->show();
}

void ScImageSelect::selectOption() {
    selectedImagePath = sender()->objectName();
    this->setIcon(QIcon(selectedImagePath));
    qDeleteAll(optionsWidget->findChildren<QPushButton*>());
}

void ScImageSelect::setName(QString name, QString dataSetName) {
    this->name = name;
    this->dataSetName = dataSetName;
}

QString ScImageSelect::getName() {
    return name;
}

QString ScImageSelect::getDataSetName() {
    return dataSetName;
}

QString ScImageSelect::getSelectedImagePath() {
    return selectedImagePath;
}
