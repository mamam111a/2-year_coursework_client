#ifndef FINDITEM_ADMIN_H
#define FINDITEM_ADMIN_H
#include "adminmenu.h"
#include <QDialog>
namespace Ui {
class finditem_admin;
}

class finditem_admin : public QDialog
{
    Q_OBJECT

public:
    explicit finditem_admin(adminMenu* adminmenu);
    ~finditem_admin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::finditem_admin *ui;
    adminMenu* adminmenu;
};

#endif // FINDITEM_ADMIN_H
