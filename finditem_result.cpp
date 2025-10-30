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
    this->setFixedSize(1221, 625);


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
            if (!copiedText.isEmpty()) copiedText += "\n"; // новая строка
            lastRow = item->row();
        } else {
            copiedText += "\t"; // табуляция между колонками
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
    table->setColumnCount(9);
    table->setHorizontalHeaderLabels({
        "Магазин", "Жанр", "Автор", "Название",
        "Издательство", "Год", "Количество","Цена", "Доп. информация"
    });
    table->setRowCount(rows.size());

    for (int rowNum = 0; rowNum < rows.size(); rowNum++) {
        QStringList cols = rows[rowNum].split(";", Qt::SkipEmptyParts);
        for (int col = 1; col < cols.size() && col <= table->columnCount(); col++) {
            QTableWidgetItem *item = new QTableWidgetItem(cols[col].trimmed());
            item->setTextAlignment(Qt::AlignCenter);
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
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({
        "Название", "Адрес", "Время работы"
    });
    table->setRowCount(rows.size());

    for (int rowNum = 0; rowNum < rows.size(); rowNum++) {
        QStringList cols = rows[rowNum].split(";", Qt::SkipEmptyParts);
        for (int col = 1; col < cols.size() && col <= table->columnCount(); col++) {
            QTableWidgetItem *item = new QTableWidgetItem(cols[col].trimmed());
            item->setTextAlignment(Qt::AlignCenter);
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

