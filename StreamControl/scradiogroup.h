#ifndef SCRADIOGROUP_H
#define SCRADIOGROUP_H
#include <QButtonGroup>
#include <QStringList>

class QRadioButton;

class ScRadioGroup : public QButtonGroup
{
    Q_OBJECT
public:
    ScRadioGroup(QWidget *parent = 0);

public slots:
    QString getCurrentRadio();
    void setValue(int, QString);
    void checkFromValue(QString);
private:
    QStringList buttonValues;
};

#endif // SCRADIOGROUP_H
