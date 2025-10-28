#ifndef ADMINMENU_H
#define ADMINMENU_H
#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class adminMenu;
}

class adminMenu : public QDialog
{
    Q_OBJECT

public:
    explicit adminMenu(MainWindow *mainWin);
    ~adminMenu();

private slots:
    void on_closeButton_clicked();

    void on_addbooks_clicked();

    void on_addshops_clicked();

    void on_deletebooks_clicked();

    void on_deleteshops_clicked();

    void on_updatebooks_clicked();

    void on_updateshops_clicked();

    void on_readbooks_clicked();

    void on_readshops_clicked();

private:
    Ui::adminMenu *ui;
    MainWindow* mainWindow;

};

#endif // ADMINMENU_H
