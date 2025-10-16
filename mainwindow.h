#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_log_clicked();
    void on_reg_clicked();
    void ReadReply();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    MainWindow *m_mainWin;

signals:
    void ServerMessage(const QString &message);
};

#endif
