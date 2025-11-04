#include "regwindow.h"
#include "ui_regwindow.h"
#include <QScreen>
#include "globals.h"
#include "sendInfo.h"
#include <QMessageBox>
#include <QRegularExpression>
RegWindow::RegWindow(MainWindow *parentWindow)
    : QDialog(parentWindow)
    , ui(new Ui::RegWindow)
    , mainWindow(parentWindow)
{
    this->setFixedSize(800, 600);
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
    if (login.length() < 8) {
        QMessageBox::warning(this, "Ошибка", "Логин должен содержать не менее 8 символов.");
        return;
    }
    QRegularExpression regex("^[a-zA-Z0-9]+$"); // только латинские буквы и цифры
    QRegularExpressionMatch match = regex.match(login);
    if (!match.hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Логин может содержать только буквы и цифры.");
        return;
    }
    QRegularExpression strongPass("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[^A-Za-z0-9]).{8,}$");

    if (!strongPass.match(password).hasMatch()) {
        QMessageBox::warning(this, "Ошибка",
                             "Пароль должен содержать не менее 8 символов, включая:\n"
                             "• Заглавную и строчную букву\n"
                             "• Цифру\n"
                             "• Специальный символ, например: !@#$%^&*()_+-={}[]\\:;\"'<>,.?/~`");
        return;
    }
    QString message = "2|" + login + "|" + password + "|" + code;
    sendToServer(socketMain, message);
    ui->login->clear();
    ui->password->clear();
    ui->code->clear();
    //this->close();
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

