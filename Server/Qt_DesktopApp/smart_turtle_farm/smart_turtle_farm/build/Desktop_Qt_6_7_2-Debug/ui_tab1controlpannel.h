/********************************************************************************
** Form generated from reading UI file 'tab1controlpannel.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB1CONTROLPANNEL_H
#define UI_TAB1CONTROLPANNEL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tab1ControlPannel
{
public:
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *plabelBack;
    QPushButton *pPot1PBSun;
    QPushButton *pPot1PBWater;
    QPushButton *pPot2PBSun;
    QPushButton *pPot2PBWater;
    QPushButton *pPot3PBSun;
    QPushButton *pPot3PBWater;
    QLabel *plabelPot1;
    QLabel *plabelPot2;
    QLabel *plabelPot3;
    QLabel *plabelPotSlider;

    void setupUi(QWidget *Tab1ControlPannel)
    {
        if (Tab1ControlPannel->objectName().isEmpty())
            Tab1ControlPannel->setObjectName("Tab1ControlPannel");
        Tab1ControlPannel->resize(860, 512);
        horizontalLayout = new QHBoxLayout(Tab1ControlPannel);
        horizontalLayout->setObjectName("horizontalLayout");
        scrollArea = new QScrollArea(Tab1ControlPannel);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 840, 492));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy);
        plabelBack = new QLabel(scrollAreaWidgetContents);
        plabelBack->setObjectName("plabelBack");
        plabelBack->setGeometry(QRect(0, 0, 841, 491));
        sizePolicy.setHeightForWidth(plabelBack->sizePolicy().hasHeightForWidth());
        plabelBack->setSizePolicy(sizePolicy);
        plabelBack->setPixmap(QPixmap(QString::fromUtf8(":/STF_Images/STF_Images/STF_Overview.png")));
        plabelBack->setScaledContents(true);
        pPot1PBSun = new QPushButton(scrollAreaWidgetContents);
        pPot1PBSun->setObjectName("pPot1PBSun");
        pPot1PBSun->setGeometry(QRect(260, 280, 41, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/STF_Images/STF_Images/STF_Button_Sun.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pPot1PBSun->setIcon(icon);
        pPot1PBSun->setIconSize(QSize(32, 32));
        pPot1PBSun->setCheckable(true);
        pPot1PBWater = new QPushButton(scrollAreaWidgetContents);
        pPot1PBWater->setObjectName("pPot1PBWater");
        pPot1PBWater->setGeometry(QRect(300, 280, 41, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/STF_Images/STF_Images/STF_Button_Water.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pPot1PBWater->setIcon(icon1);
        pPot1PBWater->setIconSize(QSize(32, 32));
        pPot1PBWater->setCheckable(true);
        pPot2PBSun = new QPushButton(scrollAreaWidgetContents);
        pPot2PBSun->setObjectName("pPot2PBSun");
        pPot2PBSun->setGeometry(QRect(380, 280, 41, 41));
        pPot2PBSun->setIcon(icon);
        pPot2PBSun->setIconSize(QSize(32, 32));
        pPot2PBSun->setCheckable(true);
        pPot2PBWater = new QPushButton(scrollAreaWidgetContents);
        pPot2PBWater->setObjectName("pPot2PBWater");
        pPot2PBWater->setGeometry(QRect(420, 280, 41, 41));
        pPot2PBWater->setIcon(icon1);
        pPot2PBWater->setIconSize(QSize(32, 32));
        pPot2PBWater->setCheckable(true);
        pPot3PBSun = new QPushButton(scrollAreaWidgetContents);
        pPot3PBSun->setObjectName("pPot3PBSun");
        pPot3PBSun->setGeometry(QRect(510, 280, 41, 41));
        pPot3PBSun->setIcon(icon);
        pPot3PBSun->setIconSize(QSize(32, 32));
        pPot3PBSun->setCheckable(true);
        pPot3PBWater = new QPushButton(scrollAreaWidgetContents);
        pPot3PBWater->setObjectName("pPot3PBWater");
        pPot3PBWater->setGeometry(QRect(550, 280, 41, 41));
        pPot3PBWater->setIcon(icon1);
        pPot3PBWater->setIconSize(QSize(32, 32));
        pPot3PBWater->setCheckable(true);
        plabelPot1 = new QLabel(scrollAreaWidgetContents);
        plabelPot1->setObjectName("plabelPot1");
        plabelPot1->setGeometry(QRect(250, 170, 91, 111));
        plabelPot1->setPixmap(QPixmap(QString::fromUtf8(":/STF_Images/STF_Images/STF_LTC.png")));
        plabelPot1->setScaledContents(true);
        plabelPot2 = new QLabel(scrollAreaWidgetContents);
        plabelPot2->setObjectName("plabelPot2");
        plabelPot2->setGeometry(QRect(370, 170, 91, 111));
        plabelPot2->setPixmap(QPixmap(QString::fromUtf8(":/STF_Images/STF_Images/STF_LTC.png")));
        plabelPot2->setScaledContents(true);
        plabelPot3 = new QLabel(scrollAreaWidgetContents);
        plabelPot3->setObjectName("plabelPot3");
        plabelPot3->setGeometry(QRect(500, 170, 91, 111));
        plabelPot3->setPixmap(QPixmap(QString::fromUtf8(":/STF_Images/STF_Images/STF_LTC.png")));
        plabelPot3->setScaledContents(true);
        plabelPotSlider = new QLabel(scrollAreaWidgetContents);
        plabelPotSlider->setObjectName("plabelPotSlider");
        plabelPotSlider->setGeometry(QRect(220, 210, 401, 91));
        plabelPotSlider->setPixmap(QPixmap(QString::fromUtf8(":/STF_Images/STF_Images/STF_PotSlider.png")));
        plabelPotSlider->setScaledContents(true);
        scrollArea->setWidget(scrollAreaWidgetContents);
        plabelBack->raise();
        plabelPotSlider->raise();
        plabelPot1->raise();
        plabelPot2->raise();
        plabelPot3->raise();
        pPot1PBSun->raise();
        pPot1PBWater->raise();
        pPot2PBSun->raise();
        pPot2PBWater->raise();
        pPot3PBSun->raise();
        pPot3PBWater->raise();

        horizontalLayout->addWidget(scrollArea);


        retranslateUi(Tab1ControlPannel);

        QMetaObject::connectSlotsByName(Tab1ControlPannel);
    } // setupUi

    void retranslateUi(QWidget *Tab1ControlPannel)
    {
        Tab1ControlPannel->setWindowTitle(QCoreApplication::translate("Tab1ControlPannel", "Form", nullptr));
        plabelBack->setText(QString());
        pPot1PBSun->setText(QString());
        pPot1PBWater->setText(QString());
        pPot2PBSun->setText(QString());
        pPot2PBWater->setText(QString());
        pPot3PBSun->setText(QString());
        pPot3PBWater->setText(QString());
        plabelPot1->setText(QString());
        plabelPot2->setText(QString());
        plabelPot3->setText(QString());
        plabelPotSlider->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Tab1ControlPannel: public Ui_Tab1ControlPannel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB1CONTROLPANNEL_H
