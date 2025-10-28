#ifndef UPDATE_SHOP_H
#define UPDATE_SHOP_H

#include <QDialog>
#include "adminmenu.h"
namespace Ui {
class update_shop;
}

class update_shop : public QDialog
{
    Q_OBJECT

public:
    explicit update_shop(adminMenu* adminmenu);
    ~update_shop();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::update_shop *ui;
    adminMenu* adminmenu;
};

#endif // UPDATE_SHOP_H
