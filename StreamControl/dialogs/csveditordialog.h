#ifndef DIALOG_CSVEDITORDIALOG_H
#define DIALOG_CSVEDITORDIALOG_H

#include <QDialog>
#include <QStringList>

class QTableWidget;
class QPushButton;

class CsvEditorDialog : public QDialog
{
    Q_OBJECT

public:
    // rows are row-major: one QStringList per CSV line
    CsvEditorDialog(const QString &dataSetName,
                    const QList<QStringList> &rows,
                    const QStringList &headers,
                    int focusColumn,
                    QWidget *parent = 0);

    // table contents, row-major, with fully blank rows dropped
    QList<QStringList> rows() const;

    // select a row and scroll it into view
    void focusRow(int row);

public slots:
    void addRow();
    void removeRows();
    void selectionChanged();

private:
    QTableWidget *table;
    QPushButton *removeButton;
    int focusColumn;
};

#endif // DIALOG_CSVEDITORDIALOG_H
