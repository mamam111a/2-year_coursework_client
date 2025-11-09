#ifndef FINDITEM_USER_H
#define FINDITEM_USER_H
#include <QTcpSocket>
#include <QDialog>
#include "mainwindow.h"
#include <QListWidgetItem>
#include "user_menu.h"
namespace Ui {
class FindItem;
}

class FindItem : public QDialog
{
    Q_OBJECT

public:
    explicit FindItem(user_menu* usermenu);
    ~FindItem();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void CheckState(QListWidgetItem *changedItem);
public slots:
    void AddShopsToListWidget(const QStringList &shops);
private:
    Ui::FindItem *ui;
    user_menu* usermenu;
    MainWindow *mainWindow;
signals:
    void DataServerShop(const QString &data);
};

#endif // FINDITEM_USER_H
