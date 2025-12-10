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
    this->setFixedSize(1054, 672);
    ui->setupUi(this);

    QButtonGroup *group = new QButtonGroup(this);
    group->addButton(ui->radioButton_section);
    group->addButton(ui->radioButton_title);
    group->addButton(ui->radioButton_pub_year);
    group->addButton(ui->radioButton_author);
    group->addButton(ui->radioButton_price);
    group->addButton(ui->radioButton_quantity);
    group->addButton(ui->radioButton_pub);

    ui->radioButton_section->setChecked(true);


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

void update_item::CheckState(QListWidgetItem *changedItem)
{
    if (!changedItem) return;

    ui->listWidget->blockSignals(true);

    if (changedItem->checkState() == Qt::Checked) {

        for (int i = 0; i < ui->listWidget->count(); i++) {
            QListWidgetItem *item = ui->listWidget->item(i);
            if (item != changedItem) {
                item->setCheckState(Qt::Unchecked);
            }
        }
    }

    ui->listWidget->blockSignals(false);
}


void update_item::AddShopsToListWidget(const QStringList &shops)
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
    connect(ui->listWidget, &QListWidget::itemChanged, this, &update_item::CheckState);
}

void update_item::AddSectionsToComboBox(const QStringList &section)
{

    ui->comboBox_section->clear();
    ui->comboBox_section->addItem("Не выбрано");
    for (const QString &x : section) {
        QString text = x.section(';', 1);
        ui->comboBox_section->addItem(text);
    }
}

void update_item::AddPublisherToComboBox(const QStringList &pub)
{
    ui->comboBox_pub->clear();
    ui->comboBox_pub->addItem("Не выбрано");
    for (const QString &x : pub) {
        ui->comboBox_pub->addItem(x);
    }
}

QString update_item::GetSelectedShopNumber()
{
    for (int i = 0; i < ui->listWidget->count(); i++) {
        QListWidgetItem *item = ui->listWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            QString text = item->text();
            int pos = text.indexOf(")");
            if (pos != -1)
                return text.left(pos);
        }
    }
    return "";
}
void update_item::on_pushButton_2_clicked()
{
    QString toChange = "";

    if (ui->radioButton_section->isChecked()) {
        toChange = "section";
    }
    else if (ui->radioButton_author->isChecked()) {
        toChange = "author";
    }
    else if (ui->radioButton_title->isChecked()) {
        toChange = "title";
    }
    else if (ui->radioButton_pub->isChecked()) {
        toChange = "publisher";
    }
    else if (ui->radioButton_pub_year->isChecked()) {
        toChange = "publishing_year";
    }
    else if (ui->radioButton_quantity->isChecked()) {
        toChange = "quantity";
    }
    else if (ui->radioButton_price->isChecked()) {
        toChange = "price";
    }


    QString section = ui->comboBox_section->currentText();
    QString authorName = ui->author_name->text();
    QString authorFamilia = ui->author_familia->text();
    QString authorOtchestvo = ui->author_otchestvo->text();
    QString title = ui->title->text();
    QString publisher = ui->comboBox_pub->currentText();
    QString publisher_year = ui->publisher_year->text();
    QString price = ui->price->text();
    QString quantity = ui->quantity->text();
    QString shopnumber = GetSelectedShopNumber();

    QString newValue = ui->newVal_2->text();

    if(publisher == "Не выбрано") publisher = "";
    if(section == "Не выбрано") section = "";
    if (section.isEmpty() && authorName.isEmpty() && authorFamilia.isEmpty() && authorOtchestvo.isEmpty() && title.isEmpty() &&
        publisher.isEmpty() && publisher_year.isEmpty() &&
        price.isEmpty() && quantity.isEmpty() && shopnumber.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Введите хотя бы одно значение");
        return;
    }
    if (section.contains('|') || authorName.contains('|') || authorFamilia.contains('|') || authorOtchestvo.contains('|')
        || title.contains('|') ||
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

    if (toChange == "publishing_year") {
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
    else if (toChange == "quantity" || toChange == "price" || toChange == "shop_id") {
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

    if(authorName.isEmpty() == false) {

        QRegularExpression fioRegex("^[А-Яа-яA-Za-z\\s-]+$");

        if (!fioRegex.match(authorName).hasMatch()) {
            QMessageBox::warning(this, "Ошибка",
                                 "Поле 'Имя автора' должно содержать только буквы");
            return;
        }  
    }
    if(authorFamilia.isEmpty() == false) {

        QRegularExpression fioRegex("^[А-Яа-яA-Za-z\\s-]+$");

        if (!fioRegex.match(authorFamilia).hasMatch()) {
            QMessageBox::warning(this, "Ошибка",
                                 "Поле 'Фамилия автора' должно содержать только буквы");
            return;
        }
    }
    if(authorOtchestvo.isEmpty() == false) {

        QRegularExpression fioRegex("^[А-Яа-яA-Za-z\\s-]+$");

        if (!fioRegex.match(authorOtchestvo).hasMatch()) {
            QMessageBox::warning(this, "Ошибка",
                                 "Поле 'Отчество автора' должно содержать только буквы");
            return;
        }
    }

    if(toChange == "author") {
        QStringList authorParts = newValue.trimmed().split(QRegularExpression("\\s+"));
        if (authorParts.size() != 3) {
            QMessageBox::warning(this, "Ошибка",
                                 "Поле 'Автор' должно содержать ровно 3 слова\n(Имя Фамилия Отчество)");
            return;
        }
        QRegularExpression fioRegex("^[А-Яа-яA-Za-z\\s-]+$");

        if (!fioRegex.match(newValue).hasMatch()) {
            QMessageBox::warning(this, "Ошибка",
                                 "Поле 'Автор' должно содержать только буквы");
            return;
        }
    }

    QString line =  "updatebooks|" + shopnumber + "|" + section + "|" + authorName + "|" + authorFamilia
                   + "|" + authorOtchestvo + "|" + title + "|" + publisher  + "|" + publisher_year + "|" + quantity + "|" + price + "|"  + toChange + "|" + newValue;
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
    ui->newVal_2->clear();


    for (int i = 0; i < ui->listWidget->count(); ++i) {
        ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
    }

}

