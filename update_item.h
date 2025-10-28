#ifndef UPDATE_ITEM_H
#define UPDATE_ITEM_H
#include "adminmenu.h"
#include <QDialog>

namespace Ui {
class update_item;
}

class update_item : public QDialog
{
    Q_OBJECT

public:
    explicit update_item(adminMenu* adminmenu);
    ~update_item();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::update_item *ui;
    adminMenu* adminmenu;
};

#endif
