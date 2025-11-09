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
    QStringList shopsList;

private slots:
    void on_log_clicked();
    void on_reg_clicked();
    void ReadReply();
    void ShowNotification(const QString &msg);
    void on_pushButton_clicked();
    void OpenFindItemResult(const QString &message);
    void OpenFindShopResult(const QString &message);

private:
    Ui::MainWindow *ui;
    MainWindow *m_mainWin;

signals:
    void ServerMessage(const QString &message);
    void DataServerShop(const QStringList &shops);
};

#endif
