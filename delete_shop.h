#ifndef DELETE_SHOP_H
#define DELETE_SHOP_H
#include "adminmenu.h"
#include <QDialog>

namespace Ui {
class delete_shop;
}

class delete_shop : public QDialog
{
    Q_OBJECT

public:
    explicit delete_shop(adminMenu* adminmenu);
    ~delete_shop();

private slots:
    void on_pushButton_2_clicked();


    void on_pushButton_clicked();

private:
    Ui::delete_shop *ui;
    adminMenu* adminmenu;
};

#endif // DELETE_SHOP_H
