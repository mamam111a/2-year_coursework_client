#include "update_shop.h"
#include "ui_update_shop.h"
#include <QButtonGroup>
#include <QMessageBox>
#include "globals.h"
#include "sendInfo.h"
#include <QRegularExpression>
update_shop::update_shop(adminMenu* adminmenu)
    : QDialog(adminmenu)
    , ui(new Ui::update_shop)
    , adminmenu(adminmenu)
{
    this->setFixedSize(800, 600);
    ui->setupUi(this);

    QButtonGroup *group = new QButtonGroup(this);
    group->addButton(ui->radioButton_10);
    group->addButton(ui->radioButton_16);
    group->addButton(ui->radioButton_18);
    ui->radioButton_10->setChecked(true);
}

update_shop::~update_shop()
{
    delete ui;
}

void update_shop::on_pushButton_2_clicked()
{
    QString result;
    if (ui->radioButton_10->isChecked()) {
        result = "name";
    } else if (ui->radioButton_16->isChecked()) {
        result = "address";
    } else if (ui->radioButton_18->isChecked()) {
        result = "working_hours";
    }

    QString name = ui->name_2->text();
    QString address = ui->address_2->text();
    QString newValue = ui->newVal->text();
    QTime timeOT = ui->timeEdit->time();
    QTime timeDO = ui->timeEdit_2->time();
    QString timeStrA = timeOT.toString("HH:mm");
    QString timeStrB = timeDO.toString("HH:mm");


    if(timeStrA == timeStrB) {
        QMessageBox::warning(this, "Ошибка", "Некорректный график работы магазина");
        return;
    }
    if (name.contains('|') || address.contains('|') ) {
        QMessageBox::warning(this, "Ошибка", "Недопустимый символ '|'");
        return;
    }

    QString line =  "updateshops|" + name + "|" + address + "|" + timeStrB + " - " + timeStrA + + "|" + result + "|" + newValue;
    sendToServer(socketMain, line);
}


void update_shop::on_pushButton_clicked()
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

