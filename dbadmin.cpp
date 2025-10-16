#include "dbadmin.h"
#include "ui_dbadmin.h"

DBadmin::DBadmin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DBadmin)
{
    ui->setupUi(this);
}

DBadmin::~DBadmin()
{
    delete ui;
}
