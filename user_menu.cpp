#include "user_menu.h"
#include "ui_user_menu.h"
#include "sendInfo.h"
#include "globals.h"
#include "mainwindow.h"
#include "finditem_user.h"
#include "findshop_admin.h"
user_menu::user_menu(MainWindow *mainWin)
    : QDialog(nullptr)
    , ui(new Ui::user_menu)
    , mainWindow(mainWin)
{
    this->setFixedSize(800, 600);
    ui->setupUi(this);
}

user_menu::~user_menu()
{
    delete ui;
}

void user_menu::on_closeButton_clicked()
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


void user_menu::on_pushButton_clicked()
{
    FindItem *findItemWindow = new FindItem(this);
    findItemWindow->AddSectionsToComboBox(mainWindow->sectionList);
    findItemWindow->AddPublisherToComboBox(mainWindow->publisherList);
    findItemWindow->setAttribute(Qt::WA_DeleteOnClose);
    findItemWindow->AddShopsToListWidget(mainWindow->shopsList);
    findItemWindow->setGeometry(this->geometry());
    connect(findItemWindow, &QObject::destroyed, this, [this]() {
        this->show();
    });
    findItemWindow->show();
    this->hide();
}


void user_menu::on_pushButton_2_clicked()
{
    this->hide();
    findshop_admin findshopadmin(nullptr, this);
    findshopadmin.setModal(true);
    findshopadmin.setGeometry(this->geometry());
    findshopadmin.exec();
    this->show();
}

