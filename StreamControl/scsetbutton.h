#ifndef SCSETBUTTON_H
#define SCSETBUTTON_H

#include <QPushButton>

class ScSetButton : public QPushButton
{
    Q_OBJECT
public:
    ScSetButton(bool nSaveOnClick,QString nWidget,QString nValue,QWidget *parent = 0);

signals:

private:
    bool saveOnClick;
    QString widget;
    QString value;

public slots:
    QString getWidget();
    QString getValue();
    bool isSaveOnClick();
};

#endif // SCSETBUTTON_H
