/********************************************************************************
** Form generated from reading UI file 'tab2potstatuspannel.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB2POTSTATUSPANNEL_H
#define UI_TAB2POTSTATUSPANNEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tab2PotStatusPannel
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QComboBox *pCBPotNum;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *plabelPotFace;
    QLCDNumber *pLNPotIllu;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_8;
    QLCDNumber *pLNPotAirTemp;
    QLCDNumber *pLNPotAirHumi;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_6;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_10;
    QLCDNumber *pLNPotGndTemp;
    QLCDNumber *pLNPotGndHumi;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_8;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_14;
    QLCDNumber *pLNPotGndEC;
    QLCDNumber *pLNPotGndPH;

    void setupUi(QWidget *Tab2PotStatusPannel)
    {
        if (Tab2PotStatusPannel->objectName().isEmpty())
            Tab2PotStatusPannel->setObjectName("Tab2PotStatusPannel");
        Tab2PotStatusPannel->resize(860, 512);
        horizontalLayoutWidget = new QWidget(Tab2PotStatusPannel);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 831, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pCBPotNum = new QComboBox(horizontalLayoutWidget);
        pCBPotNum->addItem(QString());
        pCBPotNum->addItem(QString());
        pCBPotNum->addItem(QString());
        pCBPotNum->setObjectName("pCBPotNum");
        pCBPotNum->setEnabled(true);
        pCBPotNum->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        pCBPotNum->setFrame(true);

        horizontalLayout->addWidget(pCBPotNum);

        verticalLayoutWidget = new QWidget(Tab2PotStatusPannel);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 70, 411, 421));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(7);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");
        label_2->setTextFormat(Qt::TextFormat::AutoText);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(label_2);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(label_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        plabelPotFace = new QLabel(verticalLayoutWidget);
        plabelPotFace->setObjectName("plabelPotFace");
        plabelPotFace->setMaximumSize(QSize(200, 170));
        plabelPotFace->setStyleSheet(QString::fromUtf8("border-color: rgb(222, 221, 218);"));
        plabelPotFace->setPixmap(QPixmap(QString::fromUtf8(":/STF_Image/STF_Image/STF_Smile.png")));
        plabelPotFace->setScaledContents(true);

        horizontalLayout_4->addWidget(plabelPotFace);

        pLNPotIllu = new QLCDNumber(verticalLayoutWidget);
        pLNPotIllu->setObjectName("pLNPotIllu");

        horizontalLayout_4->addWidget(pLNPotIllu);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_6->addWidget(label_4);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName("label_5");
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_6->addWidget(label_5);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        pLNPotAirTemp = new QLCDNumber(verticalLayoutWidget);
        pLNPotAirTemp->setObjectName("pLNPotAirTemp");

        horizontalLayout_8->addWidget(pLNPotAirTemp);

        pLNPotAirHumi = new QLCDNumber(verticalLayoutWidget);
        pLNPotAirHumi->setObjectName("pLNPotAirHumi");

        horizontalLayout_8->addWidget(pLNPotAirHumi);


        verticalLayout->addLayout(horizontalLayout_8);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 6);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 6);
        verticalLayoutWidget_2 = new QWidget(Tab2PotStatusPannel);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(430, 70, 411, 421));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_6 = new QLabel(verticalLayoutWidget_2);
        label_6->setObjectName("label_6");
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_9->addWidget(label_6);

        label_7 = new QLabel(verticalLayoutWidget_2);
        label_7->setObjectName("label_7");
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_9->addWidget(label_7);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        pLNPotGndTemp = new QLCDNumber(verticalLayoutWidget_2);
        pLNPotGndTemp->setObjectName("pLNPotGndTemp");

        horizontalLayout_10->addWidget(pLNPotGndTemp);

        pLNPotGndHumi = new QLCDNumber(verticalLayoutWidget_2);
        pLNPotGndHumi->setObjectName("pLNPotGndHumi");

        horizontalLayout_10->addWidget(pLNPotGndHumi);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_8 = new QLabel(verticalLayoutWidget_2);
        label_8->setObjectName("label_8");
        label_8->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_11->addWidget(label_8);

        label_9 = new QLabel(verticalLayoutWidget_2);
        label_9->setObjectName("label_9");
        label_9->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_11->addWidget(label_9);


        verticalLayout_2->addLayout(horizontalLayout_11);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        pLNPotGndEC = new QLCDNumber(verticalLayoutWidget_2);
        pLNPotGndEC->setObjectName("pLNPotGndEC");

        horizontalLayout_14->addWidget(pLNPotGndEC);

        pLNPotGndPH = new QLCDNumber(verticalLayoutWidget_2);
        pLNPotGndPH->setObjectName("pLNPotGndPH");

        horizontalLayout_14->addWidget(pLNPotGndPH);


        verticalLayout_2->addLayout(horizontalLayout_14);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 6);
        verticalLayout_2->setStretch(2, 1);
        verticalLayout_2->setStretch(3, 6);

        retranslateUi(Tab2PotStatusPannel);

        QMetaObject::connectSlotsByName(Tab2PotStatusPannel);
    } // setupUi

    void retranslateUi(QWidget *Tab2PotStatusPannel)
    {
        Tab2PotStatusPannel->setWindowTitle(QCoreApplication::translate("Tab2PotStatusPannel", "Form", nullptr));
        pCBPotNum->setItemText(0, QCoreApplication::translate("Tab2PotStatusPannel", "\355\231\224\353\266\2041", nullptr));
        pCBPotNum->setItemText(1, QCoreApplication::translate("Tab2PotStatusPannel", "\355\231\224\353\266\2042", nullptr));
        pCBPotNum->setItemText(2, QCoreApplication::translate("Tab2PotStatusPannel", "\355\231\224\353\266\2043", nullptr));

        label_2->setText(QCoreApplication::translate("Tab2PotStatusPannel", "\354\242\205\355\225\251 \355\231\224\353\266\204 \354\203\201\355\203\234", nullptr));
        label_3->setText(QCoreApplication::translate("Tab2PotStatusPannel", "\354\241\260\353\217\204", nullptr));
        plabelPotFace->setText(QString());
        label_4->setText(QCoreApplication::translate("Tab2PotStatusPannel", "\352\263\265\352\270\260 \354\244\221 \354\230\250\353\217\204", nullptr));
        label_5->setText(QCoreApplication::translate("Tab2PotStatusPannel", "\352\263\265\352\270\260 \354\244\221 \354\212\265\353\217\204", nullptr));
        label_6->setText(QCoreApplication::translate("Tab2PotStatusPannel", "\355\206\240\354\226\221 \354\206\215 \354\230\250\353\217\204", nullptr));
        label_7->setText(QCoreApplication::translate("Tab2PotStatusPannel", "\355\206\240\354\226\221 \354\206\215 \354\212\265\353\217\204", nullptr));
        label_8->setText(QCoreApplication::translate("Tab2PotStatusPannel", "\355\206\240\354\226\221 \354\227\274\353\245\230\353\237\211", nullptr));
        label_9->setText(QCoreApplication::translate("Tab2PotStatusPannel", "\355\206\240\354\226\221 pH \352\260\222", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tab2PotStatusPannel: public Ui_Tab2PotStatusPannel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB2POTSTATUSPANNEL_H
