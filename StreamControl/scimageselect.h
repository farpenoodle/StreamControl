#ifndef SCIMAGESELECT_H
#define SCIMAGESELECT_H

#include <QPushButton>

class QGridLayout;

class ScImageSelect : public QPushButton
{
    Q_OBJECT

public:
    ScImageSelect(QWidget *parent = 0, QString path = "", QString defaultImage = "", int optionWidth = 32, int optionHeight = 32, int optionsColumns = 8);

private slots:
    void displayOptions();
    void selectOption();
    void setName(QString, QString);

public slots:
    QString getName();
    QString getDataSetName();
    QString getSelectedImagePath();

private:
    QString name;
    QString dataSetName;
    QString path;
    QWidget *optionsWidget;
    int optionWidth;
    int optionHeight;
    int optionsColumns;
    QString selectedImagePath;
};


#endif // SCIMAGESELECT_H
