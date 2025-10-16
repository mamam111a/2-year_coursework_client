#include "finditem.h"
#include "ui_finditem.h"
#include "globals.h"
#include <QMessageBox>
#include "sendInfo.h"


FindItem::FindItem(MainWindow *mainWin)
    : QDialog(nullptr)
    , ui(new Ui::FindItem)
    , mainWindow(mainWin)
{
    ui->setupUi(this);

    if(mainWindow)
        this->setGeometry(mainWindow->frameGeometry());
    mainWindow->hide();
}

FindItem::~FindItem()
{
    delete ui;
}

void FindItem::on_pushButton_clicked()
{
    this->close();
    if (mainWindow) {
        QSize findSize = this->size();
        QPoint findPos = this->pos();
        QSize mainSize = mainWindow->size();
        int x = findPos.x() + (findSize.width() - mainSize.width()) / 2;
        int y = findPos.y() + (findSize.height() - mainSize.height()) / 2;
        mainWindow->move(x, y);
        mainWindow->show();
    }

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
    QString message = section + "|" + author + "|" + name + "|" + publisher + "|" + publisher_year;
    sendToServer(socketMain, message);
}

