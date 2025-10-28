#ifndef DELETE_ITEM_H
#define DELETE_ITEM_H

#include <QDialog>
#include "adminmenu.h"
namespace Ui {
class delete_item;
}

class delete_item : public QDialog
{
    Q_OBJECT

public:
    explicit delete_item(adminMenu* adminmenu);
    ~delete_item();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::delete_item *ui;
    adminMenu* adminmenu;
};

#endif // DELETE_ITEM_H
