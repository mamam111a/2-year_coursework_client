#ifndef ADD_ITEM_H
#define ADD_ITEM_H
#include "adminmenu.h"
#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class add_item;
}

class add_item : public QDialog
{
    Q_OBJECT

public:
    explicit add_item(adminMenu* adminmenu);
    ~add_item();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
public slots:
    void AddSectionsToComboBox(const QStringList &section);

    void AddPublisherToComboBox(const QStringList &pub);

    void CheckState(QListWidgetItem *changedItem);

    void AddShopsToListWidget(const QStringList &shops);
    QString GetSelectedShopNumber();

private:
    Ui::add_item *ui;
    adminMenu* adminmenu;
};

#endif // ADD_ITEM_H
