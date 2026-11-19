#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QSet>
#include <QLineEdit>
#include <QShortcut>
#include <QTimer>
#include <algorithm>
#include <functional>

#include "csveditordialog.h"

CsvEditorDialog::CsvEditorDialog(const QString &dataSetName,
                                 const QString &fieldName,
                                 const QList<QStringList> &rows,
                                 const QStringList &headers,
                                 int focusCol,
                                 QWidget *parent)
    : QDialog(parent)
{
    int columns = headers.size();
    focusColumn = qBound(0, focusCol, qMax(0, columns - 1));

    filterEdit = new QLineEdit;
    filterEdit->setPlaceholderText(tr("Filter rows..."));
    filterEdit->setClearButtonEnabled(true);

    QShortcut *findShortcut = new QShortcut(QKeySequence::Find, this);
    connect(findShortcut, &QShortcut::activated, this, [this]() {
        filterEdit->setFocus();
        filterEdit->selectAll();
    });

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
    useButton = new QPushButton(tr("Use Row"));
    useButton->setToolTip(tr("Fill the layout's fields with the selected row"));
    useButton->setEnabled(false);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(useButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(buttonBox);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(filterEdit);
    mainLayout->addWidget(table);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeRows()));
    connect(useButton, SIGNAL(clicked()), this, SLOT(useRow()));
    connect(filterEdit, SIGNAL(textChanged(QString)), this, SLOT(applyFilter(QString)));
    connect(filterEdit, SIGNAL(returnPressed()), this, SLOT(selectFirstVisibleRow()));
    connect(table, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    resize(600, 400);
    setWindowTitle(tr("Edit Data Set - %1 (%2)").arg(dataSetName, fieldName));

    // Enter in the filter jumps to the first match; don't let it press Save as well
    foreach (QPushButton *button, findChildren<QPushButton*>()) {
        button->setAutoDefault(false);
        button->setDefault(false);
    }

    filterEdit->setFocus();
}

void CsvEditorDialog::applyFilter(const QString &text)
{
    QString needle = text.trimmed();

    for (int row = 0; row < table->rowCount(); row++) {
        bool match = needle.isEmpty();
        for (int col = 0; !match && col < table->columnCount(); col++) {
            QTableWidgetItem *item = table->item(row, col);
            if (item && item->text().contains(needle, Qt::CaseInsensitive))
                match = true;
        }
        table->setRowHidden(row, !match);
    }

    // don't leave hidden rows selected, or Remove/Use Row would act on rows you can't see
    QList<QTableWidgetSelectionRange> ranges = table->selectedRanges();
    foreach (const QTableWidgetSelectionRange &range, ranges) {
        for (int row = range.topRow(); row <= range.bottomRow(); row++) {
            if (table->isRowHidden(row))
                table->setRangeSelected(QTableWidgetSelectionRange(row, 0, row, table->columnCount() - 1), false);
        }
    }
    if (table->currentRow() >= 0 && table->isRowHidden(table->currentRow()))
        table->setCurrentItem(nullptr);

    if (QTableWidgetItem *current = table->currentItem())
        table->scrollToItem(current);

    selectionChanged();
}

void CsvEditorDialog::selectFirstVisibleRow()
{
    for (int row = 0; row < table->rowCount(); row++) {
        if (!table->isRowHidden(row)) {
            QTableWidgetItem *item = table->item(row, focusColumn);
            table->setCurrentItem(item);
            table->selectRow(row);
            table->scrollToItem(item);
            table->setFocus();
            return;
        }
    }
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

void CsvEditorDialog::useRow()
{
    int row = table->currentRow();
    if (row < 0)
        return;

    // a cell still being typed in is committed when the button takes focus
    QStringList line;
    for (int col = 0; col < table->columnCount(); col++) {
        QTableWidgetItem *item = table->item(row, col);
        line.append(item ? item->text() : QString());
    }
    emit rowActivated(line);
}

void CsvEditorDialog::selectionChanged()
{
    bool hasSelection = !table->selectedItems().isEmpty();
    removeButton->setEnabled(hasSelection);
    useButton->setEnabled(hasSelection && table->currentRow() >= 0);
}
