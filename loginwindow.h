#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QTcpSocket>
namespace Ui {
class loginwindow;
}

class loginwindow : public QDialog
{
    Q_OBJECT

public:
    explicit loginwindow(QWidget *parent = nullptr);
    ~loginwindow();

private:
    Ui::loginwindow *ui;
private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void on_toolButton_pressed();
    void on_toolButton_released();

public slots:
    void CheckServerAuth(const QString &message);
};

#endif
