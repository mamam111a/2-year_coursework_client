#include "findshop_admin.h"
#include "ui_findshop_admin.h"
#include <QMessageBox>
#include "sendInfo.h"
#include "globals.h"
findshop_admin::findshop_admin(adminMenu* adminmenu, user_menu *usermenu)
    : QDialog(adminmenu)
    , ui(new Ui::findshop_admin)
    , adminmenu(adminmenu)
    , usermenu(usermenu)
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
    if(usermenu == nullptr) {
        QSize mainSize = adminmenu->size();
        int x = findPos.x() + (findSize.width() - mainSize.width()) / 2;
        int y = findPos.y() + (findSize.height() - mainSize.height()) / 2;
        if (adminmenu) {
            adminmenu->show();
        }
        adminmenu->move(x, y);
    }
    else{
        QSize mainSize = usermenu->size();
        int x = findPos.x() + (findSize.width() - mainSize.width()) / 2;
        int y = findPos.y() + (findSize.height() - mainSize.height()) / 2;
        if (usermenu) {
            usermenu->show();
        }
        usermenu->move(x, y);
    }


}


void findshop_admin::on_pushButton_2_clicked()
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

    bool includeWorkingHours = ui->checkBox->isChecked();
    QString line;
    if(includeWorkingHours) {
        line = "findshops|" + name + "|" + adress + "|" + timeStrB + " - " + timeStrA;
    }
    else{
        if (name.isEmpty() && adress.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Заполните хотя бы одно поле");
            return;
        }
        line = "findshops|" + name + "|" + adress + "|";
    }

    sendToServer(socketMain, line);

    ui->name->clear();
    ui->adress->clear();
}

