/********************************************************************************
** Form generated from reading UI file 'tab3turtlebotcontrolpannel.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB3TURTLEBOTCONTROLPANNEL_H
#define UI_TAB3TURTLEBOTCONTROLPANNEL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tab3TurtleBotControlPannel
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGraphicsView *pGVCam;
    QPushButton *pPBCamStart;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *plabelFruitStatus;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLabel *plabelLeafStatus;
    QGridLayout *gridLayout_4;
    QPushButton *pPBCoord4;
    QPushButton *pPBCoord2;
    QPushButton *pPBCoord1;
    QPushButton *pPBCoord5;
    QPushButton *pPBCoord3;
    QPushButton *pPBCoord6;
    QGridLayout *gridLayout_2;
    QPushButton *pPBright;
    QPushButton *pPBup;
    QPushButton *pPBdown;
    QPushButton *pPBstop;
    QPushButton *pPBleft;

    void setupUi(QWidget *Tab3TurtleBotControlPannel)
    {
        if (Tab3TurtleBotControlPannel->objectName().isEmpty())
            Tab3TurtleBotControlPannel->setObjectName("Tab3TurtleBotControlPannel");
        Tab3TurtleBotControlPannel->resize(860, 512);
        horizontalLayout_2 = new QHBoxLayout(Tab3TurtleBotControlPannel);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        pGVCam = new QGraphicsView(Tab3TurtleBotControlPannel);
        pGVCam->setObjectName("pGVCam");

        verticalLayout->addWidget(pGVCam);

        pPBCamStart = new QPushButton(Tab3TurtleBotControlPannel);
        pPBCamStart->setObjectName("pPBCamStart");

        verticalLayout->addWidget(pPBCamStart);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(Tab3TurtleBotControlPannel);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(label);

        plabelFruitStatus = new QLabel(Tab3TurtleBotControlPannel);
        plabelFruitStatus->setObjectName("plabelFruitStatus");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plabelFruitStatus->sizePolicy().hasHeightForWidth());
        plabelFruitStatus->setSizePolicy(sizePolicy);
        plabelFruitStatus->setMaximumSize(QSize(240, 110));
        plabelFruitStatus->setPixmap(QPixmap(QString::fromUtf8(":/STF_Image/STF_Image/STF_Danger.png")));
        plabelFruitStatus->setScaledContents(true);

        horizontalLayout_3->addWidget(plabelFruitStatus);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        label_3 = new QLabel(Tab3TurtleBotControlPannel);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_4->addWidget(label_3);

        plabelLeafStatus = new QLabel(Tab3TurtleBotControlPannel);
        plabelLeafStatus->setObjectName("plabelLeafStatus");
        plabelLeafStatus->setMaximumSize(QSize(240, 110));
        plabelLeafStatus->setPixmap(QPixmap(QString::fromUtf8(":/STF_Image/STF_Image/STF_Good.png")));
        plabelLeafStatus->setScaledContents(true);

        horizontalLayout_4->addWidget(plabelLeafStatus);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 2);

        verticalLayout_3->addLayout(horizontalLayout_4);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        pPBCoord4 = new QPushButton(Tab3TurtleBotControlPannel);
        pPBCoord4->setObjectName("pPBCoord4");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pPBCoord4->sizePolicy().hasHeightForWidth());
        pPBCoord4->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(pPBCoord4, 1, 0, 1, 1);

        pPBCoord2 = new QPushButton(Tab3TurtleBotControlPannel);
        pPBCoord2->setObjectName("pPBCoord2");
        sizePolicy1.setHeightForWidth(pPBCoord2->sizePolicy().hasHeightForWidth());
        pPBCoord2->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(pPBCoord2, 0, 1, 1, 1);

        pPBCoord1 = new QPushButton(Tab3TurtleBotControlPannel);
        pPBCoord1->setObjectName("pPBCoord1");
        sizePolicy1.setHeightForWidth(pPBCoord1->sizePolicy().hasHeightForWidth());
        pPBCoord1->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(pPBCoord1, 0, 0, 1, 1);

        pPBCoord5 = new QPushButton(Tab3TurtleBotControlPannel);
        pPBCoord5->setObjectName("pPBCoord5");
        sizePolicy1.setHeightForWidth(pPBCoord5->sizePolicy().hasHeightForWidth());
        pPBCoord5->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(pPBCoord5, 1, 1, 1, 1);

        pPBCoord3 = new QPushButton(Tab3TurtleBotControlPannel);
        pPBCoord3->setObjectName("pPBCoord3");
        sizePolicy1.setHeightForWidth(pPBCoord3->sizePolicy().hasHeightForWidth());
        pPBCoord3->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(pPBCoord3, 0, 2, 1, 1);

        pPBCoord6 = new QPushButton(Tab3TurtleBotControlPannel);
        pPBCoord6->setObjectName("pPBCoord6");
        sizePolicy1.setHeightForWidth(pPBCoord6->sizePolicy().hasHeightForWidth());
        pPBCoord6->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(pPBCoord6, 1, 2, 1, 1);


        verticalLayout_3->addLayout(gridLayout_4);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 1);
        verticalLayout_3->setStretch(2, 1);

        verticalLayout_2->addLayout(verticalLayout_3);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        pPBright = new QPushButton(Tab3TurtleBotControlPannel);
        pPBright->setObjectName("pPBright");
        sizePolicy1.setHeightForWidth(pPBright->sizePolicy().hasHeightForWidth());
        pPBright->setSizePolicy(sizePolicy1);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::GoNext));
        pPBright->setIcon(icon);
        pPBright->setIconSize(QSize(72, 72));

        gridLayout_2->addWidget(pPBright, 1, 2, 1, 1);

        pPBup = new QPushButton(Tab3TurtleBotControlPannel);
        pPBup->setObjectName("pPBup");
        sizePolicy1.setHeightForWidth(pPBup->sizePolicy().hasHeightForWidth());
        pPBup->setSizePolicy(sizePolicy1);
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::GoUp));
        pPBup->setIcon(icon1);
        pPBup->setIconSize(QSize(72, 72));

        gridLayout_2->addWidget(pPBup, 0, 1, 1, 1);

        pPBdown = new QPushButton(Tab3TurtleBotControlPannel);
        pPBdown->setObjectName("pPBdown");
        sizePolicy1.setHeightForWidth(pPBdown->sizePolicy().hasHeightForWidth());
        pPBdown->setSizePolicy(sizePolicy1);
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::GoDown));
        pPBdown->setIcon(icon2);
        pPBdown->setIconSize(QSize(72, 72));

        gridLayout_2->addWidget(pPBdown, 1, 1, 1, 1);

        pPBstop = new QPushButton(Tab3TurtleBotControlPannel);
        pPBstop->setObjectName("pPBstop");
        sizePolicy1.setHeightForWidth(pPBstop->sizePolicy().hasHeightForWidth());
        pPBstop->setSizePolicy(sizePolicy1);
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStop));
        pPBstop->setIcon(icon3);
        pPBstop->setIconSize(QSize(72, 72));

        gridLayout_2->addWidget(pPBstop, 0, 2, 1, 1);

        pPBleft = new QPushButton(Tab3TurtleBotControlPannel);
        pPBleft->setObjectName("pPBleft");
        sizePolicy1.setHeightForWidth(pPBleft->sizePolicy().hasHeightForWidth());
        pPBleft->setSizePolicy(sizePolicy1);
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::GoPrevious));
        pPBleft->setIcon(icon4);
        pPBleft->setIconSize(QSize(72, 72));

        gridLayout_2->addWidget(pPBleft, 1, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);

        verticalLayout_2->setStretch(0, 2);
        verticalLayout_2->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(Tab3TurtleBotControlPannel);

        QMetaObject::connectSlotsByName(Tab3TurtleBotControlPannel);
    } // setupUi

    void retranslateUi(QWidget *Tab3TurtleBotControlPannel)
    {
        Tab3TurtleBotControlPannel->setWindowTitle(QCoreApplication::translate("Tab3TurtleBotControlPannel", "Form", nullptr));
        pPBCamStart->setText(QCoreApplication::translate("Tab3TurtleBotControlPannel", "Camera Start", nullptr));
        label->setText(QCoreApplication::translate("Tab3TurtleBotControlPannel", "\354\227\264\353\247\244 \354\203\201\355\203\234", nullptr));
        plabelFruitStatus->setText(QString());
        label_3->setText(QCoreApplication::translate("Tab3TurtleBotControlPannel", "\354\236\216 \354\203\201\355\203\234", nullptr));
        plabelLeafStatus->setText(QString());
        pPBCoord4->setText(QCoreApplication::translate("Tab3TurtleBotControlPannel", "\354\242\214\355\221\2344", nullptr));
        pPBCoord2->setText(QCoreApplication::translate("Tab3TurtleBotControlPannel", "\354\242\214\355\221\2342", nullptr));
        pPBCoord1->setText(QCoreApplication::translate("Tab3TurtleBotControlPannel", "\354\242\214\355\221\2341", nullptr));
        pPBCoord5->setText(QCoreApplication::translate("Tab3TurtleBotControlPannel", "\354\242\214\355\221\2345", nullptr));
        pPBCoord3->setText(QCoreApplication::translate("Tab3TurtleBotControlPannel", "\354\242\214\355\221\2343", nullptr));
        pPBCoord6->setText(QCoreApplication::translate("Tab3TurtleBotControlPannel", "\354\242\214\355\221\2346", nullptr));
        pPBright->setText(QString());
        pPBup->setText(QString());
        pPBdown->setText(QString());
        pPBstop->setText(QString());
        pPBleft->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Tab3TurtleBotControlPannel: public Ui_Tab3TurtleBotControlPannel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB3TURTLEBOTCONTROLPANNEL_H
