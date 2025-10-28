#ifndef ADD_SHOP_H
#define ADD_SHOP_H
#include "adminmenu.h"
#include <QDialog>

namespace Ui {
class add_shop;
}

class add_shop : public QDialog
{
    Q_OBJECT

public:
    explicit add_shop(adminMenu* adminmenu);
    ~add_shop();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::add_shop *ui;
    adminMenu* adminmenu;
};

#endif // ADD_SHOP_H
