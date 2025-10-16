#ifndef DBADMIN_H
#define DBADMIN_H

#include <QDialog>

namespace Ui {
class DBadmin;
}

class DBadmin : public QDialog
{
    Q_OBJECT

public:
    explicit DBadmin(QWidget *parent = nullptr);
    ~DBadmin();

private:
    Ui::DBadmin *ui;
};

#endif // DBADMIN_H
