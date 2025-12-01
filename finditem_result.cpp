#include "finditem_result.h"
#include "ui_finditem_result.h"
#include "mainwindow.h"
#include <QClipboard>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
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
            copiedText += ";";
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
    for (QString &row : rows) {
        row = row.trimmed();
        if (!row.isEmpty() && row[0] == '#')
            row.remove(0, 1);
    }

    QTableWidget *table = ui->tableWidget;
    if (!table) {
        QMessageBox::warning(this, "Ошибка", "Таблица не найдена в интерфейсе!");
        return;
    }

    table->clear();
    table->setColumnCount(11);
    table->setHorizontalHeaderLabels({
        "Название магазина", "Адрес", "Время открытия", "Время закрытия" ,"Жанр", "Автор", "Название",
        "Издательство", "Год", "Количество","Цена"
    });
    table->setRowCount(rows.size());

    for (int rowNum = 0; rowNum < rows.size(); rowNum++) {
        QStringList cols = rows[rowNum].split(";", Qt::KeepEmptyParts);
        for (int col = 0; col < cols.size() && col < table->columnCount(); col++) {
            QTableWidgetItem *item = new QTableWidgetItem(cols[col].trimmed());

            item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            if (col < 4) {
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
    for (QString &row : rows) {
        row = row.trimmed();
        if (!row.isEmpty() && row[0] == '#')
            row.remove(0, 1);
    }

    QTableWidget *table = ui->tableWidget;
    if (!table) {
        QMessageBox::warning(this, "Ошибка", "Таблица не найдена в интерфейсе!");
        return;
    }

    table->clear();
    table->setColumnCount(6);
    table->setHorizontalHeaderLabels({
        "Название", "Город", "Улица","Номер здания", "Время открытия", "Время закрытия"
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
void finditem_result::on_pushButton_2_clicked()
{

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setWindowTitle("Сохранить результаты");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilters({"CSV файл (*.csv)", "Текстовый файл (*.txt)"});
    dialog.setDefaultSuffix("csv");

    if (!dialog.exec())
        return;

    QString fileName = dialog.selectedFiles().first();
    QString selectedFilter = dialog.selectedNameFilter();
    QString extension;
    if (selectedFilter.contains("*.csv"))
        extension = ".csv";
    else if (selectedFilter.contains("*.txt"))
        extension = ".txt";
    QFileInfo fi(fileName);
    if (fi.suffix().isEmpty()) {
        fileName += extension;
    } else if (fi.suffix().compare(extension.mid(1), Qt::CaseInsensitive) != 0) {
        fileName = fi.path() + "/" + fi.completeBaseName() + extension;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи!");
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    QTableWidget *table = ui->tableWidget;
    QStringList headers;
    for (int col = 0; col < table->columnCount(); col++)
        headers << table->horizontalHeaderItem(col)->text();
    out << headers.join(";") << "\n";
    for (int row = 0; row < table->rowCount(); row++) {
        QStringList rowValues;
        for (int col = 0; col < table->columnCount(); col++) {
            QTableWidgetItem *item = table->item(row, col);
            rowValues << (item ? item->text() : "");
        }
        out << rowValues.join(";") << "\n";
    }

    file.close();
    QMessageBox::information(this, "Результат", "Данные успешно сохранены!");
}

