#ifndef SCCOMBOBOX_H
#define SCCOMBOBOX_H

#include <QComboBox>
class QStringListModel;

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
    void setNoSaveOnChange(bool);
    bool noSaveOnChange();

protected:
    void resizeEvent(QResizeEvent *);

private:
    QToolButton *clearButton;
    QString comboBoxName;
    QString dataSetName;
    bool noSave;

signals:
    void clearButtonClicked();

};

#endif // SCCOMBOBOX_H
