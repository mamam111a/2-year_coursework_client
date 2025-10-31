#include "finditem_user.h"
#include "ui_finditem_user.h"
#include "globals.h"
#include <QMessageBox>
#include "sendInfo.h"


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

    if (changedItem->text() == "В ЛЮБОМ МАГАЗИНЕ") {
        if (changedItem->checkState() == Qt::Checked) {
            for (int i = 0; i < ui->listWidget->count(); i++) {
                QListWidgetItem *item = ui->listWidget->item(i);
                if (item != changedItem) {
                    item->setCheckState(Qt::Unchecked);
                }
            }
        }
    } else {
        QListWidgetItem *anyShopItem = ui->listWidget->item(0);
        if (anyShopItem->checkState() == Qt::Checked) {
            anyShopItem->setCheckState(Qt::Unchecked);
        }
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
    if (section.isEmpty() && author.isEmpty() && name.isEmpty() &&
        publisher.isEmpty() && publisher_year.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите хотя бы одно значение для поиска");
        return;
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
    indString.chop(1);
    QString message = section + "|" + author + "|" + name + "|" + publisher + "|" + publisher_year + "|" + indString;
    sendToServer(socketMain, message);
}

