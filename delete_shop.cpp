#include "delete_shop.h"
#include "ui_delete_shop.h"
#include <QMessageBox>
#include "globals.h"
#include "sendInfo.h"

delete_shop::delete_shop(adminMenu* adminmenu)
    : QDialog(adminmenu)
    , ui(new Ui::delete_shop)
    , adminmenu(adminmenu)
{
    this->setFixedSize(800, 600);
    ui->setupUi(this);
}

delete_shop::~delete_shop()
{
    delete ui;
}

void delete_shop::on_pushButton_2_clicked()
{
    QString name = ui->name->text();
    QString adress = ui->adress->text();
    QTime timeOT = ui->timeEdit->time();
    QTime timeDO = ui->timeEdit_2->time();
    QString timeStrA = timeOT.toString("HH:mm");
    QString timeStrB = timeDO.toString("HH:mm");

    if (name.contains('|') || adress.contains('|')) {
        QMessageBox::warning(this, "Ошибка", "Недопустимый символ '|'");
        return;
    }
    if (name.isEmpty() || adress.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля для удаления");
        return;
    }
    QString line = "deleteshops|" + name + "|" + adress + "|" + timeStrB + " - " + timeStrA;
    sendToServer(socketMain, line);

    ui->name->clear();
    ui->adress->clear();

}


void delete_shop::on_pushButton_clicked()
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

