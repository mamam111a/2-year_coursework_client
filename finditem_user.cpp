#include "finditem_user.h"
#include "ui_finditem_user.h"
#include "globals.h"
#include <QMessageBox>
#include "sendInfo.h"
#include <QRegularExpression>
#include <QDate>
using namespace std;
FindItem::FindItem(MainWindow *mainWin)
    : QDialog(nullptr)
    , ui(new Ui::FindItem)
    , mainWindow(mainWin)
{
    this->setFixedSize(800, 600);
    ui->setupUi(this);

    if(mainWindow) {
        connect(mainWindow, &MainWindow::DataServerShop, this, &FindItem::AddShopsToListWidget);
        this->setGeometry(mainWindow->frameGeometry());
        mainWindow->hide();
    }
}
void FindItem::CheckState(QListWidgetItem *changedItem)
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

void FindItem::AddShopsToListWidget(const QStringList &shops)
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
    connect(ui->listWidget, &QListWidget::itemChanged, this, &FindItem::CheckState);
}
FindItem::~FindItem()
{
    delete ui;
}

void FindItem::on_pushButton_clicked()
{
    QString message = "0|logout";
    sendToServer(socketMain, message);
    this->close();
    QSize findSize = this->size();
    QPoint findPos = this->pos();
    QSize mainSize = mainWindow->size();
    int x = findPos.x() + (findSize.width() - mainSize.width()) / 2;
    int y = findPos.y() + (findSize.height() - mainSize.height()) / 2;
    if (mainWindow) {
        mainWindow->show();
    }
    mainWindow->move(x, y);

}
void FindItem::on_pushButton_2_clicked()
{
    QString section = ui->section->text();
    QString author = ui->author->text();
    QString name = ui->name->text();
    QString publisher = ui->publisher->text();
    QString publisher_year = ui->publisher_year->text();

    if (section.contains("|") || author.contains("|") || name.contains("|") ||
        publisher.contains("|") || publisher_year.contains("|")) {
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

    if (!ui->listWidget->item(0)->checkState() && section.isEmpty() && author.isEmpty() && name.isEmpty() &&
        publisher.isEmpty() && publisher_year.isEmpty()) {
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

    QString message = section + "|" + author + "|" + name + "|" + publisher + "|" + publisher_year + "|" + indString +
                      "|" + quantityOTStr + "|" + quantityDOStr + "|" + priceOTStr + "|" + priceDOStr;
    sendToServer(socketMain, message);
}
