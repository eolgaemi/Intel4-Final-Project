/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *pTabWidget;
    QWidget *pTab1;
    QWidget *pTab2;
    QWidget *pTab3;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName("MainWidget");
        MainWidget->resize(890, 560);
        horizontalLayout = new QHBoxLayout(MainWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        pTabWidget = new QTabWidget(MainWidget);
        pTabWidget->setObjectName("pTabWidget");
        pTab1 = new QWidget();
        pTab1->setObjectName("pTab1");
        pTabWidget->addTab(pTab1, QString());
        pTab2 = new QWidget();
        pTab2->setObjectName("pTab2");
        pTabWidget->addTab(pTab2, QString());
        pTab3 = new QWidget();
        pTab3->setObjectName("pTab3");
        pTabWidget->addTab(pTab3, QString());

        horizontalLayout->addWidget(pTabWidget);


        retranslateUi(MainWidget);

        pTabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QCoreApplication::translate("MainWidget", "MainWidget", nullptr));
        pTabWidget->setTabText(pTabWidget->indexOf(pTab1), QCoreApplication::translate("MainWidget", "\354\240\204\354\262\264", nullptr));
        pTabWidget->setTabText(pTabWidget->indexOf(pTab2), QCoreApplication::translate("MainWidget", "\354\204\274\354\204\234", nullptr));
        pTabWidget->setTabText(pTabWidget->indexOf(pTab3), QCoreApplication::translate("MainWidget", "\354\230\201\354\203\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
