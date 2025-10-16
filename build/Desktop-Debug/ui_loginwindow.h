/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginwindow
{
public:
    QPushButton *pushButton;
    QLabel *label_4;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *login;
    QLabel *label_2;
    QLineEdit *password;
    QToolButton *toolButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *loginwindow)
    {
        if (loginwindow->objectName().isEmpty())
            loginwindow->setObjectName("loginwindow");
        loginwindow->resize(800, 600);
        pushButton = new QPushButton(loginwindow);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(320, 400, 131, 31));
        label_4 = new QLabel(loginwindow);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(220, 120, 331, 61));
        groupBox = new QGroupBox(loginwindow);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(230, 190, 311, 191));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(41, 70, 223, 60));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        login = new QLineEdit(layoutWidget);
        login->setObjectName("login");

        formLayout->setWidget(0, QFormLayout::FieldRole, login);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        password = new QLineEdit(groupBox);
        password->setObjectName("password");
        password->setGeometry(QRect(121, 104, 141, 26));
        password->setEchoMode(QLineEdit::Password);
        toolButton = new QToolButton(groupBox);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(270, 100, 30, 33));
        pushButton_2 = new QPushButton(loginwindow);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(300, 530, 171, 21));

        retranslateUi(loginwindow);

        QMetaObject::connectSlotsByName(loginwindow);
    } // setupUi

    void retranslateUi(QDialog *loginwindow)
    {
        loginwindow->setWindowTitle(QCoreApplication::translate("loginwindow", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("loginwindow", "\320\223\320\276\321\202\320\276\320\262\320\276", nullptr));
        label_4->setText(QCoreApplication::translate("loginwindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:28pt;\">\360\237\221\244  </span><span style=\" font-size:26pt;\">\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217  </span><span style=\" font-size:28pt;\">\360\237\221\244</span></p></body></html>", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("loginwindow", "<html><head/><body><p><span style=\" font-size:16pt;\">\320\233\320\276\320\263\320\270\320\275</span></p></body></html>", nullptr));
        login->setPlaceholderText(QCoreApplication::translate("loginwindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\273\320\276\320\263\320\270\320\275", nullptr));
        label_2->setText(QCoreApplication::translate("loginwindow", "<html><head/><body><p><span style=\" font-size:16pt;\">\320\237\320\260\321\200\320\276\320\273\321\214</span></p></body></html>", nullptr));
        password->setPlaceholderText(QCoreApplication::translate("loginwindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
#if QT_CONFIG(tooltip)
        toolButton->setToolTip(QCoreApplication::translate("loginwindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214/\321\201\320\272\321\200\321\213\321\202\321\214 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton->setText(QCoreApplication::translate("loginwindow", "\360\237\221\201", nullptr));
        pushButton_2->setText(QCoreApplication::translate("loginwindow", "\320\222\320\265\321\200\320\275\321\203\321\202\321\214\321\201\321\217 \320\275\320\260\320\267\320\260\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginwindow: public Ui_loginwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
