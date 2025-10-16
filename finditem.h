#ifndef FINDITEM_H
#define FINDITEM_H
#include <QTcpSocket>
#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class FindItem;
}

class FindItem : public QDialog
{
    Q_OBJECT

public:
    explicit FindItem(MainWindow *mainWin);
    ~FindItem();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::FindItem *ui;
    MainWindow *mainWindow;
};

#endif // FINDITEM_H
