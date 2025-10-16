#ifndef DATABASE_USER_H
#define DATABASE_USER_H

#include <QDialog>

namespace Ui {
class Database_user;
}

class Database_user : public QDialog
{
    Q_OBJECT

public:
    explicit Database_user(QWidget *parent = nullptr);
    ~Database_user();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Database_user *ui;
};

#endif // DATABASE_USER_H
