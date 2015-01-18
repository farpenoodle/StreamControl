#ifndef SCCOMBOBOX_H
#define SCCOMBOBOX_H

#include <QComboBox>
#include <QStringListModel>

class QToolButton;

class ScComboBox : public QComboBox
{
    Q_OBJECT
public:
    ScComboBox(QWidget *parent = 0);

public slots:
    void setName(QString,QString);
    QString getName();
    QString getDataSetName();
    void setButtonVisible(bool);
    void addModel(QStringListModel *);
    void clearButtonSlot();

protected:
    void resizeEvent(QResizeEvent *);

private:
    QToolButton *clearButton;
    QString comboBoxName;
    QString dataSetName;

signals:
    void clearButtonClicked();

};

#endif // SCCOMBOBOX_H
