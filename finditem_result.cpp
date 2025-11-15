#include "finditem_result.h"
#include "ui_finditem_result.h"
#include "mainwindow.h"
#include <QClipboard>
#include <QMessageBox>

finditem_result::finditem_result(MainWindow *mainWin, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::finditem_result)
    , mainWindow(mainWin)
{

    ui->setupUi(this);
    connect(ui->copyButton, &QPushButton::clicked, this, &finditem_result::CopySelectedCells);
}

finditem_result::~finditem_result()
{
    delete ui;
}
void finditem_result::CopySelectedCells()
{
    QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();
    if (selectedItems.isEmpty()) return;

    QString copiedText;
    int lastRow = -1;
    for (QTableWidgetItem* item : selectedItems) {
        if (item->row() != lastRow) {
            if (!copiedText.isEmpty()) copiedText += "\n";
            lastRow = item->row();
        } else {
            copiedText += "\t";
        }
        copiedText += item->text();
    }

    QApplication::clipboard()->setText(copiedText);
}
void finditem_result::ShowSearchResultsBooks(const QString &message)
{
    QStringList rows = message.split("\n", Qt::SkipEmptyParts);
    if (rows.isEmpty()) {
        QMessageBox::information(this, "Результат", "Ничего не найдено.");
        return;
    }

    QTableWidget *table = ui->tableWidget;
    if (!table) {
        QMessageBox::warning(this, "Ошибка", "Таблица не найдена в интерфейсе!");
        return;
    }

    table->clear();
    table->setColumnCount(11);
    table->setHorizontalHeaderLabels({
        "Название магазина", "Адрес", "Время работы", "Жанр", "Автор", "Название",
        "Издательство", "Год", "Количество","Цена", "Доп. информация"
    });
    table->setRowCount(rows.size());

    for (int rowNum = 0; rowNum < rows.size(); rowNum++) {
        QStringList cols = rows[rowNum].split(";", Qt::KeepEmptyParts);
        for (int col = 0; col < cols.size() && col < table->columnCount(); col++) {
            QTableWidgetItem *item = new QTableWidgetItem(cols[col].trimmed());

            item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            if (col < 3) {
                item->setBackground(QBrush(QColor(220, 230, 250)));
            } else {
                item->setBackground(QBrush(QColor(220, 250, 220)));
            }

            table->setItem(rowNum, col, item);
        }
    }

    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    table->setWordWrap(true);
    table->updateGeometry();
    table->viewport()->update();
}


void finditem_result::ShowSearchResultsShops(const QString &message) {
    QStringList rows = message.split("\n", Qt::SkipEmptyParts);
    if (rows.isEmpty()) {
        QMessageBox::information(this, "Результат", "Ничего не найдено.");
        return;
    }

    QTableWidget *table = ui->tableWidget;
    if (!table) {
        QMessageBox::warning(this, "Ошибка", "Таблица не найдена в интерфейсе!");
        return;
    }

    table->clear();
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({
        "Название", "Город", "Улица","Номер здания", "Время работы"
    });
    table->setRowCount(rows.size());

    for (int rowNum = 0; rowNum < rows.size(); rowNum++) {
        QStringList cols = rows[rowNum].split(";", Qt::SkipEmptyParts);
        for (int col = 1; col < cols.size() && col <= table->columnCount(); col++) {
            QTableWidgetItem *item = new QTableWidgetItem(cols[col].trimmed());
             item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            item->setData(Qt::TextAlignmentRole, Qt::AlignCenter);
            table->setItem(rowNum, col - 1, item);
        }
    }
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setWordWrap(true);
    table->resizeRowsToContents();
    table->updateGeometry();
    table->viewport()->update();
}

void finditem_result::on_pushButton_clicked()
{
    this->close();
}


void finditem_result::on_copyButton_clicked()
{
    ui->copyButton->setText("Скопировано");
}

