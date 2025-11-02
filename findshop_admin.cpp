#include "findshop_admin.h"
#include "ui_findshop_admin.h"
#include <QMessageBox>
#include "sendInfo.h"
#include "globals.h"
findshop_admin::findshop_admin(adminMenu* adminmenu)
    : QDialog(adminmenu)
    , ui(new Ui::findshop_admin)
    , adminmenu(adminmenu)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
}


findshop_admin::~findshop_admin()
{
    delete ui;
}

void findshop_admin::on_pushButton_clicked()
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


void findshop_admin::on_pushButton_2_clicked()
{
    QString name = ui->name->text();
    QString adress = ui->adress->text();
    QTime timeOT = ui->timeEdit->time();
    QTime timeDO = ui->timeEdit_2->time();
    QString timeStrA = timeOT.toString("HH:mm");
    QString timeStrB = timeDO.toString("HH:mm");
    if(timeStrA == timeStrB) {
        QMessageBox::warning(this, "Ошибка", "Некорректный график работы магазина");
        return;
    }
    if (name.contains('|') || adress.contains('|')) {
        QMessageBox::warning(this, "Ошибка", "Недопустимый символ '|'");
        return;
    }
    if (name.isEmpty() && adress.isEmpty() && timeStrA == "00:00" && timeStrB == "00:00") {
        QMessageBox::warning(this, "Ошибка", "Заполните хотя бы одно поле");
        return;
    }
    QString line = "findshops|" + name + "|" + adress + "|" + timeStrB + " - " + timeStrA;
    sendToServer(socketMain, line);

    ui->name->clear();
    ui->adress->clear();
}

