#include "delete_item.h"
#include "ui_delete_item.h"
#include <QMessageBox>
#include "globals.h"
#include "sendInfo.h"
#include <QDate>
using namespace std;
delete_item::delete_item(adminMenu* adminmenu)
    : QDialog(adminmenu)
    , ui(new Ui::delete_item)
    , adminmenu(adminmenu)

{
    this->setFixedSize(800, 600);
    ui->setupUi(this);
}

delete_item::~delete_item()
{
    delete ui;
}
void delete_item::on_pushButton_clicked()
{
    this->close();
    QSize findSize = this->size();
    QPoint findPos = this->pos();
    QSize mainSize = adminmenu->size();
    int x = findPos.x() + (findSize.width() - mainSize.width()) / 2;
    int y = findPos.y() + (findSize.height() - mainSize.height()) / 2;
    adminmenu->move(x, y);
    adminmenu->show();

}

void delete_item::on_pushButton_2_clicked()
{
    QString section = ui->section->text();
    QString author = ui->author->text();
    QString title = ui->title->text();
    QString publisher = ui->publisher->text();
    QString publisher_year = ui->publisher_year->text();
    QString price = ui->price->text();
    QString quantity = ui->quantity->text();
    QString numberShop = ui->numbershop->text();

    // Проверка недопустимого символа '|'
    if (section.contains('|') || author.contains('|') || title.contains('|') ||
        publisher.contains('|') || publisher_year.contains('|') ||
        price.contains('|')  || quantity.contains('|') || numberShop.contains('|'))
    {
        QMessageBox::warning(this, "Ошибка", "Недопустимый символ '|'");
        return;
    }

    int year = 0, priceValue = 0, quantityValue = 0, shopNmbValue = 0;
    try {
        if (!publisher_year.isEmpty())
            year = publisher_year.toInt();

        if (!price.isEmpty())
            priceValue = price.toInt();

        if (!quantity.isEmpty())
            quantityValue = quantity.toInt();

        if (!numberShop.isEmpty())
            shopNmbValue = numberShop.toInt();

    } catch (...) {
        QMessageBox::warning(this, "Ошибка", "Поля числовых значений должны содержать только числа");
        return;
    }

    if ((!publisher_year.isEmpty() && year <= 0) ||
      (!price.isEmpty() && priceValue <= 0) ||
      (!quantity.isEmpty() && quantityValue <= 0) ||
      (!numberShop.isEmpty() && shopNmbValue <= 0))
    {
        QMessageBox::warning(this, "Ошибка", "Числовые значения должны быть положительными");
        return;
    }

    if (!publisher_year.isEmpty() && (year > QDate::currentDate().year() || year <= 0)) {
        QMessageBox::warning(this, "Ошибка", "Год издания должен быть положительным числом до текущего года включительно");
        return;
    }

    if (section.isEmpty() || author.isEmpty() || title.isEmpty() ||
        publisher.isEmpty() || publisher_year.isEmpty() ||
        price.isEmpty()  || quantity.isEmpty() || numberShop.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля для удаления");
        return;
    }

    QString line = "deletebooks|" + numberShop + "|" + section + "|" + author + "|" + title + "|" +
                   publisher + "|" + publisher_year + "|" + quantity + "|" + price;
    sendToServer(socketMain, line);

    ui->section->clear();
    ui->author->clear();
    ui->title->clear();
    ui->publisher->clear();
    ui->publisher_year->clear();
    ui->price->clear();
    ui->quantity->clear();
    ui->numbershop->clear();
}
