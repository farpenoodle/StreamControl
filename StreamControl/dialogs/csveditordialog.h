#ifndef DIALOG_CSVEDITORDIALOG_H
#define DIALOG_CSVEDITORDIALOG_H

#include <QDialog>
#include <QStringList>

class QTableWidget;
class QPushButton;
class QLineEdit;

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
    void useRow();
    void selectionChanged();
    void applyFilter(const QString &text);
    void selectFirstVisibleRow();

signals:
    // the current row, as shown in the table (including unsaved edits)
    void rowActivated(const QStringList &row);

private:
    QTableWidget *table;
    QLineEdit *filterEdit;
    QPushButton *removeButton;
    QPushButton *useButton;
    int focusColumn;
};

#endif // DIALOG_CSVEDITORDIALOG_H
