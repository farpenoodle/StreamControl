#ifndef SCLINEEDIT_H
#define SCLINEEDIT_H

#include <QLineEdit>

class QToolButton;

class ScLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    ScLineEdit(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *);
    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:

public slots:
    void setName(QString,QString);
    QString getName();
    QString getDataSetName();
    void setButtonVisible(bool);
    void clearButtonSlot();
    void setNoSaveOnChange(bool);
    bool noSaveOnChange();
    void setDataSetEditable(bool);


private:
    QToolButton *clearButton;
    QString lineEditName;
    QString dataSetName;
    bool noSave;
    bool dataSetEditable;

signals:
    void clearButtonClicked();
    void editDataSetRequested();

};


#endif // SCLINEEDIT_H
