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
    QString adress = ui->adress->text();
    QString workingtime = ui->workingtime->text();

    if (name.isEmpty() || adress.isEmpty() || workingtime.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены");
        return;
    }
    if (name.contains('|') || adress.contains('|') || workingtime.contains('|')) {
        QMessageBox::warning(this, "Ошибка", "Недопустимый символ '|'");
        return;
    }
    QRegularExpression timeRegex("^([01]\\d|2[0-3]):[0-5]\\d\\s-\\s([01]\\d|2[0-3]):[0-5]\\d$");

    if (!timeRegex.match(workingtime).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Поле 'Время работы' должно быть в формате 00:00 - 00:00");
        return;
    }
    QString line = "addshops|" + name + "|" + adress + "|" + workingtime;
    sendToServer(socketMain, line);
    ui->name->clear();
    ui->adress->clear();
    ui->workingtime->clear();
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

