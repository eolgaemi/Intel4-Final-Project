/********************************************************************************
** Form generated from reading UI file 'tab4adminpannel.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB4ADMINPANNEL_H
#define UI_TAB4ADMINPANNEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tab4AdminPannel
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_5;
    QLabel *plabelTutleStatus;
    QLabel *label;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_6;
    QLabel *plabelPot1Status;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_7;
    QLabel *plabelPot2Status;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_8;
    QLabel *plabelPot3Status;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_13;
    QPushButton *pPBServerStart;
    QPushButton *pPBServerRestart;
    QPushButton *pPBServerStop;
    QVBoxLayout *verticalLayout_7;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_9;
    QLineEdit *pLE_ID;
    QLineEdit *pLE_Pwd;
    QLineEdit *pLE_Msg;
    QPushButton *pPB_Send;

    void setupUi(QWidget *Tab4AdminPannel)
    {
        if (Tab4AdminPannel->objectName().isEmpty())
            Tab4AdminPannel->setObjectName("Tab4AdminPannel");
        Tab4AdminPannel->resize(860, 512);
        horizontalLayout_2 = new QHBoxLayout(Tab4AdminPannel);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_5 = new QLabel(Tab4AdminPannel);
        label_5->setObjectName("label_5");
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_11->addWidget(label_5);

        plabelTutleStatus = new QLabel(Tab4AdminPannel);
        plabelTutleStatus->setObjectName("plabelTutleStatus");
        plabelTutleStatus->setMaximumSize(QSize(35, 35));
        plabelTutleStatus->setPixmap(QPixmap(QString::fromUtf8(":/STF_Images/STF_Images/STF_Green.png")));
        plabelTutleStatus->setScaledContents(true);

        horizontalLayout_11->addWidget(plabelTutleStatus);

        horizontalLayout_11->setStretch(0, 3);
        horizontalLayout_11->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_11);

        label = new QLabel(Tab4AdminPannel);
        label->setObjectName("label");
        label->setMaximumSize(QSize(200, 190));
        label->setPixmap(QPixmap(QString::fromUtf8(":/STF_Images/STF_Images/STF_TurtleBot.png")));
        label->setScaledContents(true);

        verticalLayout_3->addWidget(label);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 5);

        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        label_6 = new QLabel(Tab4AdminPannel);
        label_6->setObjectName("label_6");
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_12->addWidget(label_6);

        plabelPot1Status = new QLabel(Tab4AdminPannel);
        plabelPot1Status->setObjectName("plabelPot1Status");
        plabelPot1Status->setMaximumSize(QSize(35, 35));
        plabelPot1Status->setPixmap(QPixmap(QString::fromUtf8(":/STF_Images/STF_Images/STF_Yellow.png")));
        plabelPot1Status->setScaledContents(true);

        horizontalLayout_12->addWidget(plabelPot1Status);

        horizontalLayout_12->setStretch(0, 3);
        horizontalLayout_12->setStretch(1, 1);

        verticalLayout_4->addLayout(horizontalLayout_12);

        label_3 = new QLabel(Tab4AdminPannel);
        label_3->setObjectName("label_3");
        label_3->setMaximumSize(QSize(200, 190));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/STF_Images/STF_Images/STF_Linetracer.png")));
        label_3->setScaledContents(true);

        verticalLayout_4->addWidget(label_3);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(1, 5);

        horizontalLayout_3->addLayout(verticalLayout_4);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        label_7 = new QLabel(Tab4AdminPannel);
        label_7->setObjectName("label_7");
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_13->addWidget(label_7);

        plabelPot2Status = new QLabel(Tab4AdminPannel);
        plabelPot2Status->setObjectName("plabelPot2Status");
        plabelPot2Status->setMaximumSize(QSize(35, 35));
        plabelPot2Status->setPixmap(QPixmap(QString::fromUtf8(":/STF_Images/STF_Images/STF_Red.png")));
        plabelPot2Status->setScaledContents(true);

        horizontalLayout_13->addWidget(plabelPot2Status);

        horizontalLayout_13->setStretch(0, 3);
        horizontalLayout_13->setStretch(1, 1);

        verticalLayout_5->addLayout(horizontalLayout_13);

        label_2 = new QLabel(Tab4AdminPannel);
        label_2->setObjectName("label_2");
        label_2->setMaximumSize(QSize(200, 190));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/STF_Images/STF_Images/STF_Linetracer.png")));
        label_2->setScaledContents(true);

        verticalLayout_5->addWidget(label_2);

        verticalLayout_5->setStretch(0, 1);
        verticalLayout_5->setStretch(1, 5);

        horizontalLayout_5->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        label_8 = new QLabel(Tab4AdminPannel);
        label_8->setObjectName("label_8");
        label_8->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_14->addWidget(label_8);

        plabelPot3Status = new QLabel(Tab4AdminPannel);
        plabelPot3Status->setObjectName("plabelPot3Status");
        plabelPot3Status->setMaximumSize(QSize(35, 35));
        plabelPot3Status->setPixmap(QPixmap(QString::fromUtf8(":/STF_Images/STF_Images/STF_Green.png")));
        plabelPot3Status->setScaledContents(true);

        horizontalLayout_14->addWidget(plabelPot3Status);

        horizontalLayout_14->setStretch(0, 3);
        horizontalLayout_14->setStretch(1, 1);

        verticalLayout_6->addLayout(horizontalLayout_14);

        label_4 = new QLabel(Tab4AdminPannel);
        label_4->setObjectName("label_4");
        label_4->setMaximumSize(QSize(200, 190));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/STF_Images/STF_Images/STF_Linetracer.png")));
        label_4->setScaledContents(true);

        verticalLayout_6->addWidget(label_4);

        verticalLayout_6->setStretch(0, 1);
        verticalLayout_6->setStretch(1, 5);

        horizontalLayout_5->addLayout(verticalLayout_6);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_5);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_13 = new QLabel(Tab4AdminPannel);
        label_13->setObjectName("label_13");
        label_13->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_7->addWidget(label_13);

        pPBServerStart = new QPushButton(Tab4AdminPannel);
        pPBServerStart->setObjectName("pPBServerStart");

        horizontalLayout_7->addWidget(pPBServerStart);

        pPBServerRestart = new QPushButton(Tab4AdminPannel);
        pPBServerRestart->setObjectName("pPBServerRestart");

        horizontalLayout_7->addWidget(pPBServerRestart);

        pPBServerStop = new QPushButton(Tab4AdminPannel);
        pPBServerStop->setObjectName("pPBServerStop");

        horizontalLayout_7->addWidget(pPBServerStop);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 1);
        horizontalLayout_7->setStretch(2, 1);
        horizontalLayout_7->setStretch(3, 1);

        verticalLayout_2->addLayout(horizontalLayout_7);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        textEdit = new QTextEdit(Tab4AdminPannel);
        textEdit->setObjectName("textEdit");

        verticalLayout_7->addWidget(textEdit);


        verticalLayout_2->addLayout(verticalLayout_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        pLE_ID = new QLineEdit(Tab4AdminPannel);
        pLE_ID->setObjectName("pLE_ID");

        horizontalLayout_9->addWidget(pLE_ID);

        pLE_Pwd = new QLineEdit(Tab4AdminPannel);
        pLE_Pwd->setObjectName("pLE_Pwd");

        horizontalLayout_9->addWidget(pLE_Pwd);

        pLE_Msg = new QLineEdit(Tab4AdminPannel);
        pLE_Msg->setObjectName("pLE_Msg");

        horizontalLayout_9->addWidget(pLE_Msg);

        pPB_Send = new QPushButton(Tab4AdminPannel);
        pPB_Send->setObjectName("pPB_Send");

        horizontalLayout_9->addWidget(pPB_Send);

        horizontalLayout_9->setStretch(0, 2);
        horizontalLayout_9->setStretch(1, 2);
        horizontalLayout_9->setStretch(2, 4);
        horizontalLayout_9->setStretch(3, 1);

        verticalLayout_2->addLayout(horizontalLayout_9);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 10);
        verticalLayout_2->setStretch(2, 1);

        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(Tab4AdminPannel);

        QMetaObject::connectSlotsByName(Tab4AdminPannel);
    } // setupUi

    void retranslateUi(QWidget *Tab4AdminPannel)
    {
        Tab4AdminPannel->setWindowTitle(QCoreApplication::translate("Tab4AdminPannel", "Form", nullptr));
        label_5->setText(QCoreApplication::translate("Tab4AdminPannel", "\352\264\200\353\246\254\354\236\220 \353\264\207 (\352\274\254\353\266\201)", nullptr));
        plabelTutleStatus->setText(QString());
        label->setText(QString());
        label_6->setText(QCoreApplication::translate("Tab4AdminPannel", "\355\231\224\353\266\204 1", nullptr));
        plabelPot1Status->setText(QString());
        label_3->setText(QString());
        label_7->setText(QCoreApplication::translate("Tab4AdminPannel", "\355\231\224\353\266\204 2", nullptr));
        plabelPot2Status->setText(QString());
        label_2->setText(QString());
        label_8->setText(QCoreApplication::translate("Tab4AdminPannel", "\355\231\224\353\266\204 3", nullptr));
        plabelPot3Status->setText(QString());
        label_4->setText(QString());
        label_13->setText(QCoreApplication::translate("Tab4AdminPannel", "\354\204\234\353\262\204\352\264\200\353\246\254", nullptr));
        pPBServerStart->setText(QCoreApplication::translate("Tab4AdminPannel", "\354\213\234\354\236\221", nullptr));
        pPBServerRestart->setText(QCoreApplication::translate("Tab4AdminPannel", "\354\236\254\354\213\234\353\217\231", nullptr));
        pPBServerStop->setText(QCoreApplication::translate("Tab4AdminPannel", "\354\242\205\353\243\214", nullptr));
        pLE_ID->setPlaceholderText(QCoreApplication::translate("Tab4AdminPannel", "ID", nullptr));
        pLE_Pwd->setPlaceholderText(QCoreApplication::translate("Tab4AdminPannel", "Password", nullptr));
        pLE_Msg->setPlaceholderText(QCoreApplication::translate("Tab4AdminPannel", "Message", nullptr));
        pPB_Send->setText(QCoreApplication::translate("Tab4AdminPannel", "\354\240\204\354\206\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tab4AdminPannel: public Ui_Tab4AdminPannel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB4ADMINPANNEL_H
