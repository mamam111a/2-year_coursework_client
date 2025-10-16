#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regwindow.h"
#include "loginwindow.h"
#include "center.h"
#include "globals.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->show();
    centerWindow(this);
    socketMain = new QTcpSocket(this);
    socketMain->connectToHost("127.0.0.1", 7432);
    connect(socketMain, &QTcpSocket::readyRead, this, &MainWindow::ReadReply);
    connect(socketMain, &QTcpSocket::connected, this, [](){ });
    connect(socketMain, &QTcpSocket::disconnected, this, [](){});
    connect(socketMain, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this, [this](QAbstractSocket::SocketError){
                QMessageBox::critical(this, "Ошибка", "Ошибка соединения: " + socketMain->errorString());
            });
}
MainWindow::~MainWindow()
{
    if(socketMain)
        socketMain->close();
    delete ui;
}
void MainWindow::on_reg_clicked()
{
    RegWindow *window = new RegWindow(this);
    window->setModal(true);
    centerWindow(window);
    window->exec();
    delete window;
}
void MainWindow::on_log_clicked()
{
    loginwindow *window = new loginwindow(this);
    window->setModal(true);
    centerWindow(window);
    connect(this, &MainWindow::ServerMessage,
            window, &loginwindow::CheckServerAuth);
    window->exec();
    delete window;
}

void MainWindow::ReadReply()
{
    QByteArray data = socketMain->readAll();
    QString message = QString::fromUtf8(data);
    emit ServerMessage(message);
    QMessageBox::information(this, "Сервер", message);
}

void MainWindow::on_pushButton_clicked()
{
    QApplication::quit();
}

