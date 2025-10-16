#ifndef MENU_USER_H
#define MENU_USER_H

#include <QDialog>

namespace Ui {
class menu_user;
}

class menu_user : public QDialog
{
    Q_OBJECT

public:
    explicit menu_user(QWidget *parent = nullptr);
    ~menu_user();

private:
    Ui::menu_user *ui;
};

#endif // MENU_USER_H
