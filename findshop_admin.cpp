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
    QString name = ui->name_3->text();
    QString adress = ui->adress_3->text();
    QString workingtime = ui->workingtime_3->text();

    if (name.contains('|') || adress.contains('|') || workingtime.contains('|')) {
        QMessageBox::warning(this, "Ошибка", "Недопустимый символ '|'");
        return;
    }
    if (name.isEmpty() && adress.isEmpty() && workingtime.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните хотя бы одно поле");
        return;
    }
    QString line = "findshops|" + name + "|" + adress + "|" + workingtime;
    sendToServer(socketMain, line);

    ui->name_3->clear();
    ui->adress_3->clear();
    ui->workingtime_3->clear();
}

