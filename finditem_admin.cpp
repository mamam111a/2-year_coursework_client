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

void finditem_admin::CheckState(QListWidgetItem *changedItem)
{
    if (!changedItem) return;

    ui->listWidget->blockSignals(true);

    QListWidgetItem *anyShopItem = ui->listWidget->item(0);

    if (changedItem == anyShopItem) {
        anyShopItem->setCheckState(Qt::Checked);
        for (int i = 1; i < ui->listWidget->count(); i++) {
            ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
        }
    } else {
        bool anySpecificChecked = false;
        for (int i = 1; i < ui->listWidget->count(); i++) {
            if (ui->listWidget->item(i)->checkState() == Qt::Checked) {
                anySpecificChecked = true;
                break;
            }
        }
        anyShopItem->setCheckState(anySpecificChecked ? Qt::Unchecked : Qt::Checked);
    }

    ui->listWidget->blockSignals(false);
}

void finditem_admin::AddShopsToListWidget(const QStringList &shops)
{
    ui->listWidget->clear();

    QListWidgetItem *anyShopItem = new QListWidgetItem("В ЛЮБОМ МАГАЗИНЕ", ui->listWidget);
    anyShopItem->setFlags(anyShopItem->flags() | Qt::ItemIsUserCheckable);
    anyShopItem->setCheckState(Qt::Checked);
    ui->listWidget->addItem(anyShopItem);

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
    connect(ui->listWidget, &QListWidget::itemChanged, this, &finditem_admin::CheckState);
}


void finditem_admin::on_pushButton_clicked()
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
void finditem_admin::AddSectionsToComboBox(const QStringList &section)
{
    ui->comboBox->clear();
    ui->comboBox->addItem("Не выбрано");
    for (const QString &x : section) {
        QString text = x.section(';', 1);
        ui->comboBox->addItem(text);
    }
}
void finditem_admin::AddPublisherToComboBox(const QStringList &pub)
{
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("Не выбрано");
    for (const QString &x : pub) {
        ui->comboBox_2->addItem(x);
    }
}
void finditem_admin::on_pushButton_2_clicked()
{
    QString section = ui->comboBox->currentText();
    QString authorName = ui->author_name->text();
    QString authorFamilia = ui->author_familia->text();
    QString authorOtchestvo = ui->author_otchestvo->text();
    QString name = ui->name->text();
    QString publisher = ui->comboBox_2->currentText();
    QString publisher_year = ui->pub_year->text();
    if(section == "Не выбрано") section = "";
    if(publisher == "Не выбрано") publisher = "";

    if (section.contains("|") || authorName.contains("|") || name.contains("|") ||
        publisher.contains("|") || publisher_year.contains("|") || authorFamilia.contains("|") || authorOtchestvo.contains("|")) {
        QMessageBox::warning(this, "Ошибка", "Недопустимый символ '|'");
        return;
    }

    bool anySpecificShopChecked = false;
    for (int i = 1; i < ui->listWidget->count(); i++) {
        QListWidgetItem *item = ui->listWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            anySpecificShopChecked = true;
            break;
        }
    }

    if (!anySpecificShopChecked) {
        ui->listWidget->item(0)->setCheckState(Qt::Checked);
    }

    if (section.isEmpty() && authorName.isEmpty() && name.isEmpty() &&
        publisher.isEmpty() && publisher_year.isEmpty() && authorFamilia.isEmpty() && authorOtchestvo.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите хотя бы одно значение для поиска");
        return;
    }

    if (!publisher_year.isEmpty()) {
        bool ok;
        int year = publisher_year.toInt(&ok);
        int currentYear = QDate::currentDate().year();
        if (!ok || year <= 0 || year > currentYear) {
            QMessageBox::warning(this, "Ошибка", "Год издания должен быть положительным числом до текущего года");
            return;
        }
    }

    QList<int> selectedInd;
    for (int i = 0; i < ui->listWidget->count(); i++) {
        QListWidgetItem *item = ui->listWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            selectedInd.append(i);
        }
    }

    QString indString;
    for (int x : selectedInd) {
        indString += QString::number(x) + ",";
    }
    if (!indString.isEmpty())
        indString.chop(1);

    int quantityOT = ui->spinBox->value();
    int quantityDO = ui->spinBox_2->value();
    int priceOT = ui->spinBox_3->value();
    int priceDO = ui->spinBox_4->value();

    QString quantityOTStr = QString::number(quantityOT);
    QString quantityDOStr = QString::number(quantityDO);
    QString priceOTStr = QString::number(priceOT);
    QString priceDOStr = QString::number(priceDO);

    QRegularExpression fioRegex("^[А-Яа-яA-Za-z\\s-]+$");

    if (!fioRegex.match(authorName).hasMatch() && authorName.isEmpty() == false) {
        QMessageBox::warning(this, "Ошибка",
                             "Поле 'Имя автора' должно содержать только буквы");
        return;
    }
    if (!fioRegex.match(authorFamilia).hasMatch() && authorFamilia.isEmpty() == false) {
        QMessageBox::warning(this, "Ошибка",
                             "Поле 'Фамилия автора' должно содержать только буквы");
        return;
    }
    if (!fioRegex.match(authorOtchestvo).hasMatch() && authorOtchestvo.isEmpty() == false) {
        QMessageBox::warning(this, "Ошибка",
                             "Поле 'Отчество автора' должно содержать только буквы");
        return;
    }

    QString message = "findbooks|" + section + "|" + authorName + "|" + authorFamilia + "|" + authorOtchestvo + "|" + name + "|" + publisher + "|" + publisher_year + "|" + indString +
                      "|" + quantityOTStr + "|" + quantityDOStr + "|" + priceOTStr + "|" + priceDOStr;
    sendToServer(socketMain, message);


    ui->author_name->clear();
    ui->author_familia->clear();
    ui->author_otchestvo->clear();
    ui->name->clear();
    ui->pub_year->clear();

    ui->comboBox->setCurrentIndex(-1);
    ui->comboBox_2->setCurrentIndex(-1);

    for (int i = 0; i < ui->listWidget->count(); ++i) {
        if (i == 0)
            ui->listWidget->item(i)->setCheckState(Qt::Checked);
        else
            ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
    }
}

