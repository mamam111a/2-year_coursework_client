#include "delete_item.h"
#include "ui_delete_item.h"
#include <QMessageBox>
#include "globals.h"
#include "sendInfo.h"
#include <QDate>
#include <QRegularExpression>
using namespace std;
delete_item::delete_item(adminMenu* adminmenu)
    : QDialog(adminmenu)
    , ui(new Ui::delete_item)
    , adminmenu(adminmenu)

{
    this->setFixedSize(800, 600);
    ui->setupUi(this);
}

delete_item::~delete_item()
{
    delete ui;
}
void delete_item::on_pushButton_clicked()
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

void delete_item::CheckState(QListWidgetItem *changedItem)
{
    if (!changedItem) return;

    ui->listWidget->blockSignals(true);

    for (int i = 0; i < ui->listWidget->count(); i++) {
        QListWidgetItem *item = ui->listWidget->item(i);
        if (item != changedItem) {
            item->setCheckState(Qt::Unchecked);
        }
    }


    if (changedItem->checkState() == Qt::Unchecked) {
        changedItem->setCheckState(Qt::Checked);
    }

    ui->listWidget->blockSignals(false);
}


void delete_item::AddShopsToListWidget(const QStringList &shops)
{
    ui->listWidget->clear();

    for (const QString &shop : shops) {
        QStringList parts = shop.split(';');
        if (parts.size() >= 4) {
            QString displayText = QString("%1) \"%2\" по адресу: %3 (%4)")
                                      .arg(parts[0], parts[1], parts[2], parts[3]);
            QListWidgetItem *item = new QListWidgetItem(displayText, ui->listWidget);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
            ui->listWidget->addItem(item);
        }
    }

    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);
    connect(ui->listWidget, &QListWidget::itemChanged, this, &delete_item::CheckState);
}


void delete_item::AddSectionsToComboBox(const QStringList &section)
{
    ui->comboBox_section->clear();
    ui->comboBox_section->addItem("Не выбрано");
    for (const QString &x : section) {
        QString text = x.section(';', 1);
        ui->comboBox_section->addItem(text);
    }
}


void delete_item::AddPublisherToComboBox(const QStringList &pub)
{
    ui->comboBox_pub->clear();
    ui->comboBox_pub->addItem("Не выбрано");
    for (const QString &x : pub) {
        ui->comboBox_pub->addItem(x);
    }
}


QString delete_item::GetSelectedShopNumber()
{
    for (int i = 0; i < ui->listWidget->count(); i++) {
        QListWidgetItem *item = ui->listWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            QString text = item->text();
            int pos = text.indexOf(")");
            if (pos != -1)
                return text.left(pos); // возвращаем номер магазина
        }
    }
    return "";
}


void delete_item::on_pushButton_2_clicked()
{
    QString section = ui->comboBox_section->currentText();
    QString authorName = ui->author_name->text();
    QString authorFamilia = ui->author_familia->text();
    QString authorOtchestvo = ui->author_otchestvo->text();
    QString title = ui->title->text();
    QString publisher = ui->comboBox_pub->currentText();
    QString publisher_year = ui->publisher_year->text();
    QString price = ui->price->text();
    QString quantity = ui->quantity->text();
    if(publisher == "Не выбрано" || section == "Не выбрано") {
        QMessageBox::warning(this, "Ошибка", "Необходимо указать издателя, секцию");
        return;
    }


    QString shopnumber = GetSelectedShopNumber();


    if (section.isEmpty() || authorName.isEmpty() || authorFamilia.isEmpty() || authorOtchestvo.isEmpty() || title.isEmpty() ||
        publisher.isEmpty() || publisher_year.isEmpty() ||
        price.isEmpty() || quantity.isEmpty() || shopnumber.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены");
        return;
    }


    if (section.contains('|') || authorName.contains('|') || authorFamilia.contains('|') || authorOtchestvo.contains('|') || title.contains('|') ||
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

        int currentYear = QDate::currentDate().year();
        if (year <= 0 || year > currentYear) {
            QMessageBox::warning(this, "Ошибка", "Год издания должен быть положительным числом до текущего года включительно");
            return;
        }
    } catch (...) {
        QMessageBox::warning(this, "Ошибка", "Поля 'Год издания', 'Цена', 'Количество' и 'Номер магазина' должны содержать только числа");
        return;
    }


    QRegularExpression fioRegex("^[А-Яа-яA-Za-z\\s-]+$");
    if (!fioRegex.match(authorName).hasMatch() || !fioRegex.match(authorFamilia).hasMatch() || !fioRegex.match(authorOtchestvo).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Поля 'Автор' должны содержать только буквы");
        return;
    }


    QString line =  "deletebooks|" + shopnumber + "|" + section + "|" + authorName + "|" + authorFamilia + "|" + authorOtchestvo
                   + "|" + title + "|" + publisher  + "|" + publisher_year + "|" + quantity + "|" + price ;
    sendToServer(socketMain, line);



    ui->comboBox_section->setCurrentIndex(-1);
    ui->author_name->clear();
    ui->author_familia->clear();
    ui->author_otchestvo->clear();
    ui->title->clear();
    ui->comboBox_pub->setCurrentIndex(-1);
    ui->publisher_year->clear();
    ui->price->clear();
    ui->quantity->clear();


    for (int i = 0; i < ui->listWidget->count(); ++i) {
        if (i == 0)
            ui->listWidget->item(i)->setCheckState(Qt::Checked);
        else
            ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
    }
}
