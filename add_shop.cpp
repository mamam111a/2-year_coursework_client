#include "add_shop.h"
#include "ui_add_shop.h"
#include <QMessageBox>
#include "globals.h"
#include "sendInfo.h"
#include <QRegularExpression>
add_shop::add_shop(adminMenu* adminmenu)
    : QDialog(adminmenu)
    , ui(new Ui::add_shop)
    , adminmenu(adminmenu)

{
    this->setFixedSize(800, 600);
    ui->setupUi(this);
}

add_shop::~add_shop()
{
    delete ui;
}

void add_shop::on_pushButton_2_clicked()
{
    QString name = ui->name->text();
    QString city = ui->city->text();
    QString street = ui->street->text();
    QString numberHouse = ui->numberHouse->text();
    QTime timeOT = ui->timeEdit->time();
    QTime timeDO = ui->timeEdit_2->time();
    QString timeStrA = timeOT.toString("HH:mm");
    QString timeStrB = timeDO.toString("HH:mm");
    QRegularExpression re("^[0-9]+[A-Za-zА-Яа-я]?(?:/[0-9]+[A-Za-zА-Яа-я]?)?$");

    if (!re.match(numberHouse).hasMatch() && numberHouse.isEmpty() == false) {
        QMessageBox::warning(this, "Ошибка", "Введите корректный номер дома");
        return;
    }
    if (name.isEmpty() || city.isEmpty() || street.isEmpty() || numberHouse.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены");
        return;
    }
    if (name.contains('|') || city.contains('|') || street.contains('|') || numberHouse.contains('|') ) {
        QMessageBox::warning(this, "Ошибка", "Недопустимый символ '|'");
        return;
    }


    QString line = "addshops|" + name + "|" + city + "|" + street + "|" + numberHouse + "|" + timeStrB + " - " + timeStrA;
    sendToServer(socketMain, line);
    ui->name->clear();
    ui->city->clear();
    ui->street->clear();
    ui->numberHouse->clear();
    ui->timeEdit->setTime(QTime(0, 0));
    ui->timeEdit_2->setTime(QTime(0, 0));
}


void add_shop::on_pushButton_clicked()
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

