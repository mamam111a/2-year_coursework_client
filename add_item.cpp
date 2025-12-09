#include "add_item.h"
#include "ui_add_item.h"
#include <QMessageBox>
#include <string>
#include "globals.h"
#include "sendInfo.h"
#include <QDate>
#include <QRegularExpression>
using namespace std;
add_item::add_item(adminMenu* adminmenu)
    : QDialog(adminmenu)
    , ui(new Ui::add_item)
    , adminmenu(adminmenu)

{
    this->setFixedSize(800, 600);
    ui->setupUi(this);
}

add_item::~add_item()
{
    delete ui;
}

void add_item::on_pushButton_clicked()
{
    this->close();
    QSize findSize = this->size();
    QPoint findPos = this->pos();
    QSize mainSize = adminmenu->size();
    int x = findPos.x() + (findSize.width() - mainSize.width()) / 2;
    int y = findPos.y() + (findSize.height() - mainSize.height()) / 2;
    adminmenu->move(x, y);
    if (adminmenu) {
        adminmenu->show();
    }

}

void add_item::on_pushButton_2_clicked()
{
    QString section = ui->section->text();
    QString author = ui->author->text();
    QString title = ui->title->text();
    QString publisher = ui->publisher->text();
    QString publisher_year = ui->publisher_year->text();
    QString price = ui->price->text();
    QString quantity = ui->quantity->text();
    QString shopnumber = ui->shopNumber->text();

    if (section.isEmpty() || author.isEmpty() || title.isEmpty() ||
        publisher.isEmpty() || publisher_year.isEmpty() ||
        price.isEmpty() || quantity.isEmpty() || shopnumber.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены \n(за исключением поля 'доп. информация')");
        return;
    }
    if (section.contains('|') || author.contains('|') || title.contains('|') ||
        publisher.contains('|') || publisher_year.contains('|') ||
        price.contains('|') ||  quantity.contains('|') || shopnumber.contains('|'))
    {
        QMessageBox::warning(this, "Ошибка", "Недопустимый символ '|'");
        return;
    }
    try {
        int year = stoi(publisher_year.toStdString());
        int priceValue = stoi(price.toStdString());
        int quantityValue = stoi(quantity.toStdString());
        int shopNmbValue = stoi(shopnumber.toStdString());

        if (year <= 0 || priceValue <= 0 || quantityValue <= 0 || shopNmbValue <= 0) {
            QMessageBox::warning(this, "Ошибка", "Числовые значения должны быть положительными");
            return;
        }

        if (!publisher_year.isEmpty()) {
            bool ok;
            int year = publisher_year.toInt(&ok);
            int currentYear = QDate::currentDate().year();
            if (!ok || year <= 0 || year > currentYear) {
                QMessageBox::warning(this, "Ошибка", "Год издания должен быть положительным числом до текущего года включительно");
                return;
            }
        }


    } catch (const invalid_argument&) {
        QMessageBox::warning(this, "Ошибка", "Поля 'Год издания', 'Цена', 'Количество' и 'Номер магазина' должны содержать только числа");
        return;
    } catch (const out_of_range&) {
        QMessageBox::warning(this, "Ошибка", "Введено слишком большое число");
        return;
    }
    QStringList authorParts = author.trimmed().split(QRegularExpression("\\s+"));

    if (authorParts.size() != 3) {
        QMessageBox::warning(this, "Ошибка",
                             "Поле 'Автор' должно содержать ровно 3 слова\n(Имя Фамилия Отчество)");
        return;
    }
    QRegularExpression fioRegex("^[А-Яа-яA-Za-z\\s-]+$");

    if (!fioRegex.match(author).hasMatch()) {
        QMessageBox::warning(this, "Ошибка",
                             "Поле 'Автор' должно содержать только буквы");
        return;
    }
    QString line =  "addbooks|" + shopnumber + "|" + section + "|" + author + "|" + title + "|" + publisher  + "|" + publisher_year + "|" + quantity + "|" + price ;
    sendToServer(socketMain, line);

    ui->section->clear();
    ui->author->clear();
    ui->title->clear();
    ui->publisher->clear();
    ui->publisher_year->clear();
    ui->price->clear();
    ui->quantity->clear();
    ui->shopNumber->clear();

}

