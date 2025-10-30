#include "finditem_admin.h"
#include "ui_finditem_admin.h"
#include <QMessageBox>
#include "globals.h"
#include "sendInfo.h"

finditem_admin::finditem_admin(adminMenu* adminmenu)
    : QDialog(adminmenu)
    , ui(new Ui::finditem_admin)
    , adminmenu(adminmenu)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
}

finditem_admin::~finditem_admin()
{
    delete ui;
}

void finditem_admin::on_pushButton_clicked()
{
    this->close();
    QSize findSize = this->size();
    QPoint findPos = this->pos();
    QSize mainSize = adminmenu->size();
    int x = findPos.x() + (findSize.width() - mainSize.width()) / 2;
    int y = findPos.y() + (findSize.height() - mainSize.height()) / 2;
    if (adminmenu) {
        adminmenu->show();
    }
    adminmenu->move(x, y);
}


void finditem_admin::on_pushButton_2_clicked()
{
    QString section = ui->section->text();
    QString author = ui->author->text();
    QString name = ui->name->text();
    QString publisher = ui->publisher->text();
    QString publisher_year = ui->publisher_year->text();
    QString quantity = ui->quantity->text();
    QString price = ui->price->text();
    QString additional_info = ui->additional_info->text();
    QString numShop = ui->numberShop->text();

    if (section.contains("|") || author.contains("|") || name.contains("|") ||
        publisher.contains("|") || publisher_year.contains("|") ||
        quantity.contains("|") || price.contains("|") || additional_info.contains("|") || numShop.contains("|")) {
        QMessageBox::warning(this, "Ошибка", "Недопустимый символ '|'");
        return;
    }
    if (section.isEmpty() && author.isEmpty() && name.isEmpty() &&
        publisher.isEmpty() && publisher_year.isEmpty() &&
        quantity.isEmpty() && price.isEmpty() && additional_info.isEmpty() && numShop.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите хотя бы одно значение для поиска");
        return;
    }

    QString message = "findbooks|" + numShop + "|" + section + "|" + author + "|" + name + "|" + publisher + "|" +
                      publisher_year + "|" + quantity + "|" + price + "|" + additional_info + "|";

    sendToServer(socketMain, message);
}

