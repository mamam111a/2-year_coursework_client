#ifndef FINDITEM_ADMIN_H
#define FINDITEM_ADMIN_H
#include "adminmenu.h"
#include <QDialog>
#include <QListWidgetItem>
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
    void CheckState(QListWidgetItem *changedItem);
public slots:
    void AddShopsToListWidget(const QStringList &shops);
    void AddSectionsToComboBox(const QStringList &section);
    void AddPublisherToComboBox(const QStringList &pub);
private:
    Ui::finditem_admin *ui;
    adminMenu* adminmenu;
};

#endif // FINDITEM_ADMIN_H
