#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "globals.h"
#include "sendInfo.h"
#include <QMessageBox>
#include "finditem.h"
#include "center.h"
loginwindow::loginwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loginwindow)
{
    ui->setupUi(this);
}

loginwindow::~loginwindow()
{
    delete ui;
}

void loginwindow::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString password = ui->password->text();

    if (login.contains("|") || password.contains("|")) {
        QMessageBox::warning(this, "Ошибка", "Недопустимый символ '|'");
        return;
    }

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Логин и пароль не могут быть пустыми!");
        return;
    }

    QString message = "1|" + login + "|" + password;

    sendToServer(socketMain, message);

}

void loginwindow::CheckServerAuth(const QString &message)
{
    if (message.contains("Вы подключились")) {

        MainWindow *mainWin = qobject_cast<MainWindow*>(parentWidget());

        if(message.contains("user")) {
            FindItem *findWin = new FindItem(mainWin);
            findWin->setAttribute(Qt::WA_DeleteOnClose);
            findWin->setGeometry(mainWin->geometry());
            findWin->show();
            this->close();
        }
        //далее дла администратора
    }
}
void loginwindow::on_pushButton_2_clicked()
{
    this->close();
}


void loginwindow::on_toolButton_pressed()
{
    ui->password->setEchoMode(QLineEdit::Normal);
}


void loginwindow::on_toolButton_released()
{
    ui->password->setEchoMode(QLineEdit::Password);
}

