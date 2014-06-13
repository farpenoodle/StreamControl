#ifndef SCTSBUTTON_H
#define SCTSBUTTON_H

#include <QPushButton>

class ScTSButton : public QPushButton
{
    Q_OBJECT
public:
    ScTSButton(bool nSaveOnClick,QWidget *parent = 0);

signals:

private:
    bool active;
    bool saveOnClick;
    uint timestamp;

public slots:
    uint getTimeStamp();
    void setTimeStamp(uint nTimeStamp);
    bool isActive();
    bool isSaveOnClick();
    void setActive(bool nActive);

};

#endif // SCTSBUTTON_H
