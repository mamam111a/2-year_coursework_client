/********************************************************************************
** Form generated from reading UI file 'database_user.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABASE_USER_H
#define UI_DATABASE_USER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Database_user
{
public:
    QPushButton *pushButton_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *Database_user)
    {
        if (Database_user->objectName().isEmpty())
            Database_user->setObjectName("Database_user");
        Database_user->resize(906, 586);
        pushButton_3 = new QPushButton(Database_user);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(360, 500, 181, 31));
        widget = new QWidget(Database_user);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(290, 100, 321, 281));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("call-start")));
        pushButton->setIcon(icon);

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);


        retranslateUi(Database_user);

        QMetaObject::connectSlotsByName(Database_user);
    } // setupUi

    void retranslateUi(QDialog *Database_user)
    {
        Database_user->setWindowTitle(QCoreApplication::translate("Database_user", "Dialog", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Database_user", "\320\222\321\213\321\205\320\276\320\264", nullptr));
#if QT_CONFIG(tooltip)
        pushButton->setToolTip(QCoreApplication::translate("Database_user", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        pushButton->setWhatsThis(QCoreApplication::translate("Database_user", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        pushButton->setText(QCoreApplication::translate("Database_user", "\320\235\320\260\320\271\321\202\320\270 \321\202\320\276\320\262\320\260\321\200", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Database_user", "\320\235\320\260\320\271\321\202\320\270 \320\274\320\260\320\263\320\260\320\267\320\270\320\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Database_user: public Ui_Database_user {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATABASE_USER_H
