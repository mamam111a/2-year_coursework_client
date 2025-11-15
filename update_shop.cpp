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
    group->addButton(ui->radioButton_name);
    group->addButton(ui->radioButton_city);
    group->addButton(ui->radioButton_working);
    group->addButton(ui->radioButton_street);
    group->addButton(ui->radioButton_numberHouse);
    ui->radioButton_name->setChecked(true);
}

update_shop::~update_shop()
{
    delete ui;
}

void update_shop::on_pushButton_2_clicked()
{
    QString result;
    if (ui->radioButton_name->isChecked()) {
        result = "name";
    } else if (ui->radioButton_city->isChecked()) {
        result = "city";
    } else if (ui->radioButton_working->isChecked()) {
        result = "working_hours";
    }
    else if (ui->radioButton_street->isChecked()) {
        result = "street";
    }
    else if (ui->radioButton_numberHouse->isChecked()) {
        result = "house_number";
    }

    QString name = ui->name_2->text();
    QString city = ui->city->text();
    QString street = ui->street->text();
    QString numberHouse = ui->numberHouse->text();
    QString newValue = ui->newVal->text();
    QTime timeOT = ui->timeEdit->time();
    QTime timeDO = ui->timeEdit_2->time();
    QString timeStrA = timeOT.toString("HH:mm");
    QString timeStrB = timeDO.toString("HH:mm");
    QRegularExpression re("^[0-9]+[A-Za-zА-Яа-я]?(?:/[0-9]+[A-Za-zА-Яа-я]?)?$");

    if ((!re.match(numberHouse).hasMatch() && numberHouse.isEmpty() == false ) ||
        (result == "house_number" && !re.match(newValue).hasMatch())) {
        QMessageBox::warning(this, "Ошибка", "Введите корректный номер дома");
        return;
    }
    if(newValue.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите новое значение");
        return;
    }
    if (name.contains('|') || city.contains('|') || street.contains('|') || numberHouse.contains('|') ) {
        QMessageBox::warning(this, "Ошибка", "Недопустимый символ '|'");
        return;
    }
    if (result == "working_hours") {
        QRegularExpression re("^([01]\\d|2[0-3]):([0-5]\\d)\\s-\\s([01]\\d|2[0-3]):([0-5]\\d)$");
        QRegularExpressionMatch match = re.match(newValue);
        if (!match.hasMatch()) {
            QMessageBox::warning(this, "Ошибка", "Неверный формат времени. Используйте HH:mm - HH:mm (обязательные пробелы)");
            return;
        }
    }
    bool includeWorkingHours = ui->checkBox->isChecked();
    QString line;
    if(includeWorkingHours) {
        line =  "updateshops|" + name + "|" + city + "|" + street + "|" + numberHouse +
               "|" + timeStrA + " - " + timeStrB + + "|" + result + "|" + newValue;
    }
    else{
        if (name.isEmpty() && city.isEmpty() && street.isEmpty() && numberHouse.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Заполните хотя бы одно поле");
            return;
        }
        line =  "updateshops|" + name + "|" + city + "|" + street + "|" + numberHouse + "|"+ "|" + result + "|" + newValue;

    }

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

