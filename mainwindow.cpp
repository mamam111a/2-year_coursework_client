#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regwindow.h"
#include "loginwindow.h"
#include "center.h"
#include "globals.h"
#include <QMessageBox>
#include <arpa/inet.h>
#include "finditem_result.h"
#include "sendInfo.h"
#include <finditem_user.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->show();
    this->setFixedSize(800, 600);
    centerWindow(this);
    socketMain = new QTcpSocket(this);
    socketMain->connectToHost("127.0.0.1", 7432);
    connect(this, &MainWindow::ServerMessage, this, &MainWindow::ShowNotification, Qt::QueuedConnection);
    connect(socketMain, &QTcpSocket::readyRead, this, &MainWindow::ReadReply);
    connect(socketMain, &QTcpSocket::connected, this, [](){ });
    connect(socketMain, &QTcpSocket::disconnected, this, [](){});
    // В MainWindow.cpp после получения данных с сервера

    connect(socketMain, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this, [this](QAbstractSocket::SocketError){
                QMessageBox::critical(this, "Ошибка", "Ошибка соединения: " + socketMain->errorString() + "\nПриложение будет закрыто.");
                QApplication::quit();
            });
}

void MainWindow::ShowNotification(const QString &msg)
{
    QString text = msg;
    if (!text.isEmpty() && text[0] == '!')
        text = text.mid(1);
    QMessageBox::information(this, "Сервер", text);
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
    connect(this, &MainWindow::ServerMessage, window, &loginwindow::CheckServerAuth);
    window->setModal(true);
    centerWindow(window);

    window->exec();
    delete window;
}
void MainWindow::OpenFindItemResult(const QString &message)
{
    finditem_result *resultWindow = new finditem_result(this, this);
    resultWindow->setModal(true);
    centerWindow(resultWindow);
    resultWindow->ShowSearchResultsBooks(message);
    resultWindow->show();
}
void MainWindow::OpenFindShopResult(const QString &message)
{
    finditem_result *resultWindow = new finditem_result(this, this);
    resultWindow->setModal(true);
    centerWindow(resultWindow);
    resultWindow->ShowSearchResultsShops(message);
    resultWindow->show();
}
void MainWindow::ReadReply()
{
    static QByteArray buffer;
    buffer.append(socketMain->readAll());

    while (buffer.size() >= 4) {
        quint32 len_net;
        memcpy(&len_net, buffer.constData(), 4);
        quint32 msgLen = ntohl(len_net);

        if (buffer.size() < 4 + msgLen)
            break;

        QByteArray msgBytes = buffer.mid(4, msgLen);
        QString message = QString::fromUtf8(msgBytes).trimmed();

        if (!message.isEmpty()) {
            if (message[0] == '!') {
                emit ServerMessage(message);
            } else if (message[0] == '*') {
                QStringList shops = message.mid(1).split('\n', Qt::SkipEmptyParts);
                shopsList = shops;
                emit DataServerShop(shops);
            } else if (message[0] == '#'){
                QStringList shopList = message.mid(1).split('\n', Qt::SkipEmptyParts);
                OpenFindItemResult(message);
            }
            else if (message[0] == '%'){
                QStringList shopList = message.mid(1).split('\n', Qt::SkipEmptyParts);
                OpenFindShopResult(message);
            }
            else if (message[0] == '@') {
                QStringList sections = message.mid(1).split('\n', Qt::SkipEmptyParts);
                sectionList = sections;
                emit DataServerSections(sections);
            }
            else if (message[0] == '?') {
                QStringList publisher = message.mid(1).split('\n', Qt::SkipEmptyParts);
                publisherList = publisher;
                emit DataPublisherSections(publisher);
            }
        }
        sendToServer(socketMain, "OK");
        buffer.remove(0, 4 + msgLen);
    }
}


void MainWindow::on_pushButton_clicked()
{
    QApplication::quit();
}

