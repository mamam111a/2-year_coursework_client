/********************************************************************************
** Form generated from reading UI file 'regwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGWINDOW_H
#define UI_REGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegWindow
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *login;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *password;
    QToolButton *toolButton_password;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *code;
    QToolButton *toolButton_code;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *RegWindow)
    {
        if (RegWindow->objectName().isEmpty())
            RegWindow->setObjectName("RegWindow");
        RegWindow->resize(800, 600);
        groupBox = new QGroupBox(RegWindow);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(170, 150, 441, 191));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 20, 401, 161));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        login = new QLineEdit(layoutWidget);
        login->setObjectName("login");

        horizontalLayout->addWidget(login);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        password = new QLineEdit(layoutWidget);
        password->setObjectName("password");
        password->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(password);

        toolButton_password = new QToolButton(layoutWidget);
        toolButton_password->setObjectName("toolButton_password");

        horizontalLayout_2->addWidget(toolButton_password);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        code = new QLineEdit(layoutWidget);
        code->setObjectName("code");
        code->setEchoMode(QLineEdit::Password);

        horizontalLayout_3->addWidget(code);

        toolButton_code = new QToolButton(layoutWidget);
        toolButton_code->setObjectName("toolButton_code");

        horizontalLayout_3->addWidget(toolButton_code);


        verticalLayout->addLayout(horizontalLayout_3);

        label_4 = new QLabel(RegWindow);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(220, 80, 341, 61));
        label_5 = new QLabel(RegWindow);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(100, 400, 581, 81));
        pushButton = new QPushButton(RegWindow);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(320, 360, 131, 31));
        pushButton_2 = new QPushButton(RegWindow);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(310, 540, 161, 21));

        retranslateUi(RegWindow);

        QMetaObject::connectSlotsByName(RegWindow);
    } // setupUi

    void retranslateUi(QDialog *RegWindow)
    {
        RegWindow->setWindowTitle(QCoreApplication::translate("RegWindow", "Dialog", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("RegWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">\320\233\320\276\320\263\320\270\320\275</span></p></body></html>", nullptr));
        login->setPlaceholderText(QCoreApplication::translate("RegWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\273\320\276\320\263\320\270\320\275", nullptr));
        label_2->setText(QCoreApplication::translate("RegWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">\320\237\320\260\321\200\320\276\320\273\321\214</span></p></body></html>", nullptr));
        password->setPlaceholderText(QCoreApplication::translate("RegWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_password->setToolTip(QCoreApplication::translate("RegWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214/\321\201\320\272\321\200\321\213\321\202\321\214 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_password->setText(QCoreApplication::translate("RegWindow", "\360\237\221\201", nullptr));
        label_3->setText(QCoreApplication::translate("RegWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">\320\232\320\276\320\264 \320\260\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200\320\260</span></p></body></html>", nullptr));
        code->setPlaceholderText(QCoreApplication::translate("RegWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\272\320\276\320\264", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_code->setToolTip(QCoreApplication::translate("RegWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214/\321\201\320\272\321\200\321\213\321\202\321\214 \320\272\320\276\320\264", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_code->setText(QCoreApplication::translate("RegWindow", "\360\237\221\201", nullptr));
        label_4->setText(QCoreApplication::translate("RegWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:26pt;\">\360\237\223\235  \320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217  \360\237\223\235</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("RegWindow", "<html><head/><body><p align=\"center\">\320\232\320\276\320\264 \320\260\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200\320\260 \321\203\320\272\320\260\320\267\321\213\320\262\320\260\320\265\321\202\321\201\321\217 \320\262 \321\201\320\273\321\203\321\207\320\260\320\265 \321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\320\270 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\320\260 \320\260\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200\320\260. </p><p align=\"center\">\320\225\321\201\320\273\320\270 \320\262\321\213 \320\276\320\261\321\213\321\207\320\275\321\213\320\271 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214 - \320\276\321\201\321\202\320\260\320\262\321\214\321\202\320\265 \320\277\320\276\320\273\320\265 \320\277\321\203\321\201\321\202\321\213\320\274.</p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("RegWindow", "\320\223\320\276\321\202\320\276\320\262\320\276", nullptr));
        pushButton_2->setText(QCoreApplication::translate("RegWindow", "\320\222\320\265\321\200\320\275\321\203\321\202\321\214\321\201\321\217 \320\275\320\260\320\267\320\260\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegWindow: public Ui_RegWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGWINDOW_H
