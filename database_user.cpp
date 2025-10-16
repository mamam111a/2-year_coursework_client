#include "database_user.h"
#include "ui_database_user.h"

Database_user::Database_user(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Database_user)
{
    ui->setupUi(this);
}

Database_user::~Database_user()
{
    delete ui;
}

void Database_user::on_pushButton_clicked()
{

}

