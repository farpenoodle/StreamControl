#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QSet>
#include <QTimer>
#include <algorithm>
#include <functional>

#include "csveditordialog.h"

CsvEditorDialog::CsvEditorDialog(const QString &dataSetName,
                                 const QList<QStringList> &rows,
                                 const QStringList &headers,
                                 int focusCol,
                                 QWidget *parent)
    : QDialog(parent)
{
    int columns = headers.size();
    focusColumn = qBound(0, focusCol, qMax(0, columns - 1));

    table = new QTableWidget(rows.size(), columns);
    table->setHorizontalHeaderLabels(headers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    table->setEditTriggers(QAbstractItemView::DoubleClicked
                           | QAbstractItemView::EditKeyPressed
                           | QAbstractItemView::AnyKeyPressed);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    table->horizontalHeader()->setStretchLastSection(true);

    for (int row = 0; row < rows.size(); row++) {
        for (int col = 0; col < columns; col++) {
            QString value = col < rows[row].size() ? rows[row][col] : QString();
            table->setItem(row, col, new QTableWidgetItem(value));
        }
    }
    table->resizeColumnsToContents();

    QPushButton *addButton = new QPushButton(tr("Add Row"));
    removeButton = new QPushButton(tr("Remove Row(s)"));
    removeButton->setEnabled(false);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(buttonBox);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(table);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeRows()));
    connect(table, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    resize(600, 400);
    setWindowTitle(tr("Edit Data Set - %1").arg(dataSetName));
}

QList<QStringList> CsvEditorDialog::rows() const
{
    QList<QStringList> result;
    for (int row = 0; row < table->rowCount(); row++) {
        QStringList line;
        bool blank = true;
        for (int col = 0; col < table->columnCount(); col++) {
            QTableWidgetItem *item = table->item(row, col);
            QString value = item ? item->text() : QString();
            if (!value.isEmpty())
                blank = false;
            line.append(value);
        }
        if (!blank)
            result.append(line);
    }
    return result;
}

void CsvEditorDialog::focusRow(int row)
{
    if (row < 0 || row >= table->rowCount() || table->columnCount() == 0)
        return;

    QTableWidgetItem *item = table->item(row, focusColumn);
    table->setCurrentItem(item);
    table->selectRow(row);

    // the table has no size until the dialog is shown, so scroll once it is
    QTimer::singleShot(0, this, [this, item]() {
        table->scrollToItem(item, QAbstractItemView::PositionAtCenter);
    });
}

void CsvEditorDialog::addRow()
{
    int row = table->rowCount();
    table->insertRow(row);
    for (int col = 0; col < table->columnCount(); col++)
        table->setItem(row, col, new QTableWidgetItem());

    if (table->columnCount() == 0)
        return;

    QTableWidgetItem *item = table->item(row, focusColumn);
    table->scrollToItem(item);
    table->setCurrentItem(item);
    table->editItem(item);
}

void CsvEditorDialog::removeRows()
{
    QSet<int> rowSet;
    foreach (QTableWidgetItem *item, table->selectedItems())
        rowSet.insert(item->row());
    if (rowSet.isEmpty() && table->currentRow() >= 0)
        rowSet.insert(table->currentRow());

    QList<int> rowList(rowSet.begin(), rowSet.end());
    std::sort(rowList.begin(), rowList.end(), std::greater<int>());
    foreach (int row, rowList)
        table->removeRow(row);

    selectionChanged();
}

void CsvEditorDialog::selectionChanged()
{
    removeButton->setEnabled(!table->selectedItems().isEmpty());
}
