#include "../include/smart_turtle_farm/mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(int argc, char** argv, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowTitle("Smart Turtle Farm ROS");
    pTab1ControlPannel= new Tab1ControlPannel(ui->pTab1);
    ui->pTab1->setLayout(pTab1ControlPannel->layout());
    pTab2PotStatusPannel = new Tab2PotStatusPannel(ui->pTab2);
    ui->pTab2->setLayout(pTab2PotStatusPannel->layout());
    pTab3TurtleBotControlPannel = new Tab3TurtleBotControlPannel(argc, argv, ui->pTab3);
    ui->pTab3->setLayout(pTab3TurtleBotControlPannel->layout());
    pTab4AdminLogin = new Tab4AdminLogin(ui->pTab4);
    ui->pTab4->setLayout(pTab4AdminLogin->layout());

    //pTab4AdminPannel = new Tab4AdminPannel(ui->pTab4);
    //ui->pTab4->setLayout(pTab4AdminPannel->layout());

    ui->pTabWidget->setCurrentIndex(0);
}

MainWidget::~MainWidget()
{
    delete ui;
}

