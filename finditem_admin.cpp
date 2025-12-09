#include "finditem_admin.h"
#include "ui_finditem_admin.h"
#include <QMessageBox>
#include "globals.h"
#include "sendInfo.h"
#include <QDate>
#include <QRegularExpression>
finditem_admin::finditem_admin(adminMenu* adminmenu)
    : QDialog(adminmenu)
    , ui(new Ui::finditem_admin)
    , adminmenu(adminmenu)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
}

finditem_admin::~finditem_admin()
{
    delete ui;
}

void finditem_admin::on_pushButton_clicked()
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


void finditem_admin::on_pushButton_2_clicked()
{
    QString section = ui->section->text();
    QString author = ui->author->text();
    QString name = ui->name->text();
    QString publisher = ui->publisher->text();
    QString publisher_year = ui->publisher_year->text();
    QString quantity = ui->quantity->text();
    QString price = ui->price->text();
    QString numShop = ui->numberShop->text();

    if (section.contains("|") || author.contains("|") || name.contains("|") ||
        publisher.contains("|") || publisher_year.contains("|") ||
        quantity.contains("|") || price.contains("|")  || numShop.contains("|")) {
        QMessageBox::warning(this, "Ошибка", "Недопустимый символ '|'");
        return;
    }
    if (section.isEmpty() && author.isEmpty() && name.isEmpty() &&
        publisher.isEmpty() && publisher_year.isEmpty() &&
        quantity.isEmpty() && price.isEmpty()  && numShop.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите хотя бы одно значение для поиска");
        return;
    }
    if (!publisher_year.isEmpty()) {
        bool ok;
        int year = publisher_year.toInt(&ok);
        int currentYear = QDate::currentDate().year(); // текущий год
        if (!ok || year <= 0 || year > currentYear) {
            QMessageBox::warning(this, "Ошибка", "Год издания должен быть положительным числом до текущего года");
            return;
        }
    }

    if (!quantity.isEmpty()) {
        bool ok;
        int qty = quantity.toInt(&ok);
        if (!ok || qty < 0) {
            QMessageBox::warning(this, "Ошибка", "Количество должно быть положительным числом");
            return;
        }
    }

    if (!price.isEmpty()) {
        bool ok;
        double p = price.toInt(&ok);
        if (!ok || p <= 0) {
            QMessageBox::warning(this, "Ошибка", "Цена должна быть положительным числом");
            return;
        }
    }

    if (!numShop.isEmpty()) {
        bool ok;
        int shopNum = numShop.toInt(&ok);
        if (!ok || shopNum <= 0) {
            QMessageBox::warning(this, "Ошибка", "Номер магазина должен быть положительным числом");
            return;
        }
    }
    QStringList authorParts = author.trimmed().split(QRegularExpression("\\s+"));

    if (author.isEmpty() == false && authorParts.size() != 3) {
        QMessageBox::warning(this, "Ошибка",
                             "Поле 'Автор' должно содержать ровно 3 слова\n(Имя Фамилия Отчество)");
        return;
    }
    QRegularExpression fioRegex("^[А-Яа-яA-Za-z\\s-]+$");

    if (!fioRegex.match(author).hasMatch() && author.isEmpty() == false) {
        QMessageBox::warning(this, "Ошибка",
                             "Поле 'Автор' должно содержать только буквы");
        return;
    }

    QString message = "findbooks|" + numShop + "|" + section + "|" + author + "|" + name + "|" + publisher + "|" +
                      publisher_year + "|" + quantity + "|" + price  + "|";

    sendToServer(socketMain, message);
}

