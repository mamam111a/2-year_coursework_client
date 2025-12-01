#include "update_item.h"
#include "ui_update_item.h"
#include <QButtonGroup>
#include <QMessageBox>
#include "globals.h"
#include "sendInfo.h"
#include <QRegularExpression>
#include <QDate>
using namespace std;
update_item::update_item(adminMenu* adminmenu)
    : QDialog(adminmenu)
    , ui(new Ui::update_item)
    , adminmenu(adminmenu)
{
    this->setFixedSize(800, 600);
    ui->setupUi(this);

    QButtonGroup *group = new QButtonGroup(this);
    group->addButton(ui->radioButton);
    group->addButton(ui->radioButton_2);
    group->addButton(ui->radioButton_3);
    group->addButton(ui->radioButton_4);
    group->addButton(ui->radioButton_5);
    group->addButton(ui->radioButton_6);
    group->addButton(ui->radioButton_7);
    group->addButton(ui->radioButton_9);

    ui->radioButton->setChecked(true);


}

update_item::~update_item()
{
    delete ui;
}

void update_item::on_pushButton_clicked()
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


void update_item::on_pushButton_2_clicked()
{
    QString result;
    if (ui->radioButton->isChecked()) {
        result = "section";
    } else if (ui->radioButton_2->isChecked()) {
        result = "author";
    } else if (ui->radioButton_3->isChecked()) {
        result = "title";
    }  else if (ui->radioButton_4->isChecked()) {
        result = "publisher";
    } else if (ui->radioButton_5->isChecked()) {
        result = "publishing_year";
    } else if (ui->radioButton_6->isChecked()) {
        result = "quantity";
    } else if (ui->radioButton_7->isChecked()) {
        result = "price";
    } else if (ui->radioButton_9->isChecked()) {
        result = "shop_id";
    }


    QString section = ui->section_3->text();
    QString author = ui->author_3->text();
    QString title = ui->title_2->text();
    QString publisher = ui->publisher_2->text();
    QString publisher_year = ui->publisher_year_2->text();
    QString price = ui->price_2->text();
    QString quantity = ui->quantity_2->text();
    QString shopnumber = ui->shopNumber_3->text();

    QString newValue = ui->newVal_2->text();

    if (section.isEmpty() && author.isEmpty() && title.isEmpty() &&
        publisher.isEmpty() && publisher_year.isEmpty() &&
        price.isEmpty() && quantity.isEmpty() && shopnumber.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Введите хотя бы одно значение");
        return;
    }
    if (section.contains('|') || author.contains('|') || title.contains('|') ||
        publisher.contains('|') || publisher_year.contains('|') ||
        price.contains('|') || quantity.contains('|') || shopnumber.contains('|'))
    {
        QMessageBox::warning(this, "Ошибка", "Недопустимый символ '|'");
        return;
    }
    int year = 0, priceValue = 0, quantityValue = 0, shopNmbValue = 0;

    try {
        if (!publisher_year.isEmpty())
            year = stoi(publisher_year.toStdString());

        if (!price.isEmpty())
            priceValue = stoi(price.toStdString());

        if (!quantity.isEmpty())
            quantityValue = stoi(quantity.toStdString());

        if (!shopnumber.isEmpty())
            shopNmbValue = stoi(shopnumber.toStdString());
        if ((year != 0 && year <= 0) ||
            (priceValue != 0 && priceValue <= 0) ||
            (quantityValue != 0 && quantityValue <= 0) ||
            (shopNmbValue != 0 && shopNmbValue <= 0))
        {
            QMessageBox::warning(this, "Ошибка", "Числовые значения должны быть положительными");
            return;
        }

    } catch (const invalid_argument&) {
        QMessageBox::warning(this, "Ошибка", "Поля числовых значений должны содержать только числа");
        return;
    } catch (const out_of_range&) {
        QMessageBox::warning(this, "Ошибка", "Введено слишком большое число");
        return;
    }


    if (!publisher_year.isEmpty()) {
        bool ok;
        int year = publisher_year.toInt(&ok);
        int currentYear = QDate::currentDate().year();

        if (!ok) {
            QMessageBox::warning(this, "Ошибка", "Год издания должен быть числом");
            return;
        }

        if (year <= 0 || year > currentYear) {
            QMessageBox::warning(this, "Ошибка", QString("Год издания должен быть положительным числом до текущего года включительно").arg(currentYear));
            return;
        }
    }

    if (newValue.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите новое значение для обновления");
        return;
    }

    if (result == "publishing_year") {
        bool ok;
        int year = newValue.toInt(&ok);
        int currentYear = QDate::currentDate().year();
        if (!ok) {
            QMessageBox::warning(this, "Ошибка", "Год издания должен быть числом");
            return;
        }
        if (year <= 0 || year > currentYear) {
            QMessageBox::warning(this, "Ошибка", QString("Год издания должен быть положительным числом до текущего года включительно").arg(currentYear));
            return;
        }
    }
    else if (result == "quantity" || result == "price" || result == "shop_id") {
        bool ok;
        int value = newValue.toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Ошибка", "Новое значение должно быть числом");
            return;
        }
        if (value <= 0) {
            QMessageBox::warning(this, "Ошибка", "Числовое значение должно быть положительным");
            return;
        }
    }

    if (newValue.contains('|')) {
        QMessageBox::warning(this, "Ошибка", "Недопустимый символ '|'");
        return;
    }


    QString line =  "updatebooks|" + shopnumber + "|" + section + "|" + author + "|" + title + "|" + publisher  + "|" + publisher_year + "|" + quantity + "|" + price + "|"  + result + "|" + newValue;
    sendToServer(socketMain, line);

    ui->section_3->clear();
    ui->author_3->clear();
    ui->title_2->clear();
    ui->publisher_2->clear();
    ui->publisher_year_2->clear();
    ui->price_2->clear();
    ui->quantity_2->clear();
    ui->newVal_2->clear();
}

