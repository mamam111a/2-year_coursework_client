/********************************************************************************
** Form generated from reading UI file 'finditem.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDITEM_H
#define UI_FINDITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FindItem
{
public:
    QGroupBox *groupBox;
    QLabel *label_23;
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *section;
    QLabel *label_2;
    QLineEdit *author;
    QLabel *label_3;
    QLineEdit *name;
    QLabel *label_4;
    QLineEdit *publisher;
    QLabel *label_5;
    QLineEdit *publisher_year;
    QPushButton *pushButton_2;
    QLabel *label_10;

    void setupUi(QDialog *FindItem)
    {
        if (FindItem->objectName().isEmpty())
            FindItem->setObjectName("FindItem");
        FindItem->resize(800, 600);
        groupBox = new QGroupBox(FindItem);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(50, 100, 691, 471));
        label_23 = new QLabel(groupBox);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(-10, 40, 691, 91));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(260, 440, 171, 21));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 170, 691, 161));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        section = new QLineEdit(layoutWidget);
        section->setObjectName("section");

        formLayout->setWidget(0, QFormLayout::FieldRole, section);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        author = new QLineEdit(layoutWidget);
        author->setObjectName("author");

        formLayout->setWidget(1, QFormLayout::FieldRole, author);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        name = new QLineEdit(layoutWidget);
        name->setObjectName("name");

        formLayout->setWidget(2, QFormLayout::FieldRole, name);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        publisher = new QLineEdit(layoutWidget);
        publisher->setObjectName("publisher");

        formLayout->setWidget(3, QFormLayout::FieldRole, publisher);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        publisher_year = new QLineEdit(layoutWidget);
        publisher_year->setObjectName("publisher_year");

        formLayout->setWidget(4, QFormLayout::FieldRole, publisher_year);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(230, 370, 231, 31));
        label_10 = new QLabel(FindItem);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(190, 10, 411, 91));

        retranslateUi(FindItem);

        QMetaObject::connectSlotsByName(FindItem);
    } // setupUi

    void retranslateUi(QDialog *FindItem)
    {
        FindItem->setWindowTitle(QCoreApplication::translate("FindItem", "Dialog", nullptr));
        groupBox->setTitle(QString());
        label_23->setText(QCoreApplication::translate("FindItem", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">\320\224\320\273\321\217 \320\262\321\213\320\261\320\276\321\200\320\260 \320\275\320\265\321\201\320\272\320\276\320\273\321\214\320\272\320\270\321\205 \320\262\320\260\321\200\320\270\320\260\320\275\321\202\320\276\320\262 </span></p><p align=\"center\"><span style=\" font-size:14pt;\">\320\277\320\265\321\200\320\265\321\207\320\270\321\201\320\273\320\270\321\202\320\265 \320\272\321\200\320\270\321\202\320\265\321\200\320\270\320\270 \320\262 \320\276\320\264\320\275\320\276\320\271 \321\201\321\202\321\200\320\276\320\272\320\265, \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\321\217 \321\201\320\276\321\216\320\267 &quot;</span><span style=\" font-size:14pt; font-weight:700;\">\320\270\320\273\320\270</span><span style=\" font-size:14pt;\">&quot; </span></p><p align=\"center\"><span style=\" font-size:12pt;\">\320\235\320\260\320\277\321\200\320\270\320\274\320\265\321\200: &quot;\320\242\321\200\320\260\320\263"
                        "\320\265\320\264\320\270\321\217 \320\270\320\273\320\270 \320\272\320\276\320\274\320\265\320\264\320\270\321\217&quot;</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("FindItem", "\320\222\320\265\321\200\320\275\321\203\321\202\321\214\321\201\321\217 \320\275\320\260\320\267\320\260\320\264", nullptr));
        label->setText(QCoreApplication::translate("FindItem", "<html><head/><body><p><span style=\" font-size:16pt;\">\320\226\320\260\320\275\321\200</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("FindItem", "<html><head/><body><p><span style=\" font-size:16pt;\">\320\220\320\262\321\202\320\276\321\200</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("FindItem", "<html><head/><body><p><span style=\" font-size:16pt;\">\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("FindItem", "<html><head/><body><p><span style=\" font-size:16pt;\">\320\230\320\267\320\264\320\260\321\202\320\265\320\273\321\214</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("FindItem", "<html><head/><body><p><span style=\" font-size:16pt;\">\320\223\320\276\320\264 \320\262\321\213\320\277\321\203\321\201\320\272\320\260</span></p></body></html>", nullptr));
        pushButton_2->setText(QCoreApplication::translate("FindItem", "\320\223\320\276\321\202\320\276\320\262\320\276", nullptr));
        label_10->setText(QCoreApplication::translate("FindItem", "<html><head/><body><p align=\"center\"><span style=\" font-size:36pt;\">\360\237\224\216 \320\237\320\236\320\230\320\241\320\232 \360\237\224\216</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindItem: public Ui_FindItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDITEM_H
