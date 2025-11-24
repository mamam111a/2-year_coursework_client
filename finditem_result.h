#ifndef FINDITEM_RESULT_H
#define FINDITEM_RESULT_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class finditem_result;
}

class finditem_result : public QDialog
{
    Q_OBJECT

public:
    explicit finditem_result(MainWindow *mainWin, QWidget *parent = nullptr);
    ~finditem_result();

private:
    Ui::finditem_result *ui;
    MainWindow *mainWindow;
public slots:
    void ShowSearchResultsBooks(const QString &message);
    void ShowSearchResultsShops(const QString &message);
private slots:
    void CopySelectedCells();
    void on_pushButton_clicked();
    void on_copyButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // FINDITEM_RESULT_H
