#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "globals.h"
#include "sendInfo.h"
#include <QMessageBox>
#include "user_menu.h"
#include "adminmenu.h"
loginwindow::loginwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loginwindow)
{
    this->setFixedSize(800, 600);
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
    ui->login->clear();
    ui->password->clear();
}

void loginwindow::CheckServerAuth(const QString &message)
{
    if (message.contains("Вы подключились")) {
        MainWindow *mainWin = qobject_cast<MainWindow*>(parentWidget());
        if(message.contains("user")) {
            user_menu *usermenu = new user_menu(mainWin);
            usermenu->setAttribute(Qt::WA_DeleteOnClose);
            usermenu->setGeometry(mainWin->geometry());
            usermenu->show();
            this->close();
            mainWin->hide();
        }
        else if(message.contains("admin")) {
            adminMenu *adminmenu = new adminMenu(mainWin);
            adminmenu->setAttribute(Qt::WA_DeleteOnClose);
            adminmenu->setGeometry(mainWin->geometry());
            adminmenu->show();
            this->close();
            mainWin->hide();

        }
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

