#ifndef USER_MENU_H
#define USER_MENU_H
#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class user_menu;
}

class user_menu : public QDialog
{
    Q_OBJECT

public:
    explicit user_menu(MainWindow *mainWin);
    ~user_menu();
    MainWindow* mainWindow;

private slots:
    void on_closeButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::user_menu *ui;

};

#endif // USER_MENU_H
