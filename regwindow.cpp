#include "regwindow.h"
#include "ui_regwindow.h"
#include <QScreen>
#include "globals.h"
#include "sendInfo.h"
#include <QMessageBox>
RegWindow::RegWindow(MainWindow *parentWindow)
    : QDialog(parentWindow)
    , ui(new Ui::RegWindow)
    , mainWindow(parentWindow)
{
    ui->setupUi(this);
    if(mainWindow)
        this->resize(mainWindow->size());
}

RegWindow::~RegWindow()
{
    delete ui;
}

void RegWindow::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString password = ui->password->text();
    QString code = ui->code->text();

    if (login.contains("|") || password.contains("|") || code.contains("|")) {
        QMessageBox::warning(this, "Ошибка", "Недопустимый символ '|'");
        return;
    }

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Логин и пароль не могут быть пустыми!");
        return;
    }

    QString message = "2|" + login + "|" + password + "|" + code;
    sendToServer(socketMain, message);
    this->close();
}

void RegWindow::on_pushButton_2_clicked()
{
    this->close();
}


void RegWindow::on_toolButton_password_pressed()
{
    ui->password->setEchoMode(QLineEdit::Normal);
}


void RegWindow::on_toolButton_password_released()
{
    ui->password->setEchoMode(QLineEdit::Password);
}


void RegWindow::on_toolButton_code_pressed()
{
    ui->code->setEchoMode(QLineEdit::Normal);
}


void RegWindow::on_toolButton_code_released()
{
    ui->code->setEchoMode(QLineEdit::Password);
}

