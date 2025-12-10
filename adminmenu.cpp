#include "adminmenu.h"
#include "globals.h"
#include "ui_adminmenu.h"
#include <QMessageBox>
#include "sendInfo.h"
#include "globals.h"
#include "add_item.h"
#include "add_shop.h"
#include "delete_item.h"
#include "delete_shop.h"
#include "update_item.h"
#include "update_shop.h"
#include "finditem_user.h"
#include "finditem_admin.h"
#include "findshop_admin.h"
adminMenu::adminMenu(MainWindow *mainWin)
    : QDialog(mainWin)
    , ui(new Ui::adminMenu)
    , mainWindow(mainWin)
{
    this->setFixedSize(800, 600);
    ui->setupUi(this);
}

adminMenu::~adminMenu()
{
    delete ui;
}

void adminMenu::on_closeButton_clicked()
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

void adminMenu::on_addbooks_clicked()
{
    this->hide();


    add_item *additem = new add_item(this);


    additem->AddSectionsToComboBox(mainWindow->sectionList);
    additem->AddPublisherToComboBox(mainWindow->publisherList);
    additem->AddShopsToListWidget(mainWindow->shopsList);


    additem->setAttribute(Qt::WA_DeleteOnClose);


    additem->setModal(true);
    additem->setGeometry(this->geometry());

    additem->exec();

    this->show();
}
void adminMenu::on_addshops_clicked()
{
    this->hide();
    add_shop addshop(this);
    addshop.setModal(true);
    addshop.setGeometry(this->geometry());
    addshop.exec();
    this->show();
}


void adminMenu::on_deletebooks_clicked()
{
    this->hide();


    delete_item *deleteitem = new delete_item(this);


    deleteitem->AddSectionsToComboBox(mainWindow->sectionList);
    deleteitem->AddPublisherToComboBox(mainWindow->publisherList);
    deleteitem->AddShopsToListWidget(mainWindow->shopsList);


   deleteitem->setAttribute(Qt::WA_DeleteOnClose);


    deleteitem->setModal(true);
    deleteitem->setGeometry(this->geometry());


    deleteitem->exec();

    this->show();
}

void adminMenu::on_deleteshops_clicked()
{
    this->hide();
    delete_shop deleteshop(this);
    deleteshop.setModal(true);
    deleteshop.setGeometry(this->geometry());
    deleteshop.exec();
    this->show();
}


void adminMenu::on_updatebooks_clicked()
{
    this->hide();


    update_item *updateItem = new update_item(this);


    updateItem->AddSectionsToComboBox(mainWindow->sectionList);
    updateItem->AddPublisherToComboBox(mainWindow->publisherList);
    updateItem->AddShopsToListWidget(mainWindow->shopsList);


    updateItem->setAttribute(Qt::WA_DeleteOnClose);


   updateItem->setModal(true);
    updateItem->setGeometry(this->geometry());


    updateItem->exec();

    this->show();
}


void adminMenu::on_updateshops_clicked()
{
    this->hide();
    update_shop updateshop(this);
    updateshop.setModal(true);
    updateshop.setGeometry(this->geometry());
    updateshop.exec();
    this->show();
}


void adminMenu::on_readbooks_clicked()
{

    this->hide();


    finditem_admin *finditemadmin = new finditem_admin(this);


    finditemadmin->AddSectionsToComboBox(mainWindow->sectionList);
    finditemadmin->AddPublisherToComboBox(mainWindow->publisherList);
    finditemadmin->AddShopsToListWidget(mainWindow->shopsList);


    finditemadmin->setAttribute(Qt::WA_DeleteOnClose);


    finditemadmin->setModal(true);
    finditemadmin->setGeometry(this->geometry());


    finditemadmin->exec();

    this->show();
}


void adminMenu::on_readshops_clicked()
{
    this->hide();
    findshop_admin findshopadmin(this, nullptr);
    findshopadmin.setModal(true);
    findshopadmin.setGeometry(this->geometry());
    findshopadmin.exec();
    this->show();
}

