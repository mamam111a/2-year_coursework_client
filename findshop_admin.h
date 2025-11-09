#ifndef FINDSHOP_ADMIN_H
#define FINDSHOP_ADMIN_H

#include <QDialog>
#include "adminmenu.h"
#include "user_menu.h"
namespace Ui {
class findshop_admin;
}

class findshop_admin : public QDialog
{
    Q_OBJECT

public:
    explicit findshop_admin(adminMenu* adminmenu, user_menu *usermenu);
    ~findshop_admin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::findshop_admin *ui;
    adminMenu* adminmenu;
    user_menu *usermenu;
};

#endif // FINDSHOP_ADMIN_H
