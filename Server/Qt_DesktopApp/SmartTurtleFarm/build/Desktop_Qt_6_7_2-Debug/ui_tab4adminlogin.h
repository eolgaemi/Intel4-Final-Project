/********************************************************************************
** Form generated from reading UI file 'tab4adminlogin.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB4ADMINLOGIN_H
#define UI_TAB4ADMINLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tab4AdminLogin
{
public:
    QPlainTextEdit *pPT_ID;
    QPlainTextEdit *pPT_PWD;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pPB_Admin_Login;

    void setupUi(QWidget *Tab4AdminLogin)
    {
        if (Tab4AdminLogin->objectName().isEmpty())
            Tab4AdminLogin->setObjectName("Tab4AdminLogin");
        Tab4AdminLogin->resize(860, 512);
        pPT_ID = new QPlainTextEdit(Tab4AdminLogin);
        pPT_ID->setObjectName("pPT_ID");
        pPT_ID->setGeometry(QRect(280, 330, 311, 31));
        pPT_PWD = new QPlainTextEdit(Tab4AdminLogin);
        pPT_PWD->setObjectName("pPT_PWD");
        pPT_PWD->setGeometry(QRect(280, 410, 311, 31));
        label = new QLabel(Tab4AdminLogin);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 340, 66, 18));
        label_2 = new QLabel(Tab4AdminLogin);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 420, 91, 18));
        label_3 = new QLabel(Tab4AdminLogin);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(570, 60, 241, 211));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/STF_Image/STF_Image/STF_Logo.png")));
        label_3->setScaledContents(true);
        label_4 = new QLabel(Tab4AdminLogin);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 110, 471, 141));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/STF_Image/STF_Image/STF_Title.png")));
        label_4->setScaledContents(true);
        pPB_Admin_Login = new QPushButton(Tab4AdminLogin);
        pPB_Admin_Login->setObjectName("pPB_Admin_Login");
        pPB_Admin_Login->setGeometry(QRect(630, 330, 88, 111));

        retranslateUi(Tab4AdminLogin);

        QMetaObject::connectSlotsByName(Tab4AdminLogin);
    } // setupUi

    void retranslateUi(QWidget *Tab4AdminLogin)
    {
        Tab4AdminLogin->setWindowTitle(QCoreApplication::translate("Tab4AdminLogin", "Form", nullptr));
        label->setText(QCoreApplication::translate("Tab4AdminLogin", "ID:", nullptr));
        label_2->setText(QCoreApplication::translate("Tab4AdminLogin", "PASSWORD:", nullptr));
        label_3->setText(QString());
        label_4->setText(QString());
        pPB_Admin_Login->setText(QCoreApplication::translate("Tab4AdminLogin", "\353\241\234\352\267\270\354\235\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tab4AdminLogin: public Ui_Tab4AdminLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB4ADMINLOGIN_H
