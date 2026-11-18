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
    void setDataSetEditable(bool);

private slots:
    void lineEditContextMenu(const QPoint &pos);

protected:
    void resizeEvent(QResizeEvent *);
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    QToolButton *clearButton;
    QString comboBoxName;
    QString dataSetName;
    bool noSave;
    bool dataSetEditable;

signals:
    void clearButtonClicked();
    void editDataSetRequested();

};

#endif // SCCOMBOBOX_H
