#ifndef REGWINDOW_H
#define REGWINDOW_H

#include <QDialog>
#include "mainwindow.h"
#include <QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui {
class RegWindow;
}
QT_END_NAMESPACE

class RegWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegWindow(MainWindow *parentWindow = nullptr);
    ~RegWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_toolButton_password_pressed();

    void on_toolButton_password_released();

    void on_toolButton_code_pressed();

    void on_toolButton_code_released();

private:
    Ui::RegWindow *ui;
    MainWindow *mainWindow;
};

#endif
