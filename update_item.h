#ifndef UPDATE_ITEM_H
#define UPDATE_ITEM_H
#include "adminmenu.h"
#include <QDialog>
#include <QListWidgetItem>
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
public slots:
    void AddSectionsToComboBox(const QStringList &section);

    void AddPublisherToComboBox(const QStringList &pub);

    void CheckState(QListWidgetItem *changedItem);

    void AddShopsToListWidget(const QStringList &shops);
    QString GetSelectedShopNumber();
private:
    Ui::update_item *ui;
    adminMenu* adminmenu;
};

#endif
