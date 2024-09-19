#include "../include/smart_turtle_farm/tab3turtlebotcontrolpannel.h"
#include "ui_tab3turtlebotcontrolpannel.h"

Tab3TurtleBotControlPannel::Tab3TurtleBotControlPannel(int argc, char **argv, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab3TurtleBotControlPannel)
{
    ui->setupUi(this);
    LINEAR_MAX = 0.22; //Max 0.22
    ANGULAR_MAX = 2.84; //Max 2.84

    prosNode = new RosNode(argc, argv);
    prosNode->pLcamView = ui->pLcamView;
    prosNode->start();

    connect(ui->pPBCoord1, SIGNAL(clicked()),this, SLOT(goal_Pub_Coord1()));
    connect(ui->pPBCoord2, SIGNAL(clicked()),this, SLOT(goal_Pub_Coord2()));
    connect(ui->pPBCoord3, SIGNAL(clicked()),this, SLOT(goal_Pub_Coord3()));
    connect(ui->pPBCoord4, SIGNAL(clicked()),this, SLOT(goal_Pub_Coord4()));
    connect(ui->pPBCoord5, SIGNAL(clicked()),this, SLOT(goal_Pub_Coord5()));
    connect(ui->pPBCoord6, SIGNAL(clicked()),this, SLOT(goal_Pub_Coord6()));
}

Tab3TurtleBotControlPannel::~Tab3TurtleBotControlPannel()
{
    delete ui;
}

void Tab3TurtleBotControlPannel::goal_Pub_Coord1()
{
   prosNode->go_goal("map",0.0, 0.0, 0.0, 0.9);
}

void Tab3TurtleBotControlPannel::goal_Pub_Coord2()
{
   prosNode->go_goal("map",0.0, 0.0, 0.0, 0.9);
}

void Tab3TurtleBotControlPannel::goal_Pub_Coord3()
{
   prosNode->go_goal("map",0.0, 0.0, 0.0, 0.9);
}

void Tab3TurtleBotControlPannel::goal_Pub_Coord4()
{
   prosNode->go_goal("map",0.0, 0.0, 0.0, 0.9);
}

void Tab3TurtleBotControlPannel::goal_Pub_Coord5()
{
   prosNode->go_goal("map",0.0, 0.0, 0.0, 0.9);
}

void Tab3TurtleBotControlPannel::goal_Pub_Coord6()
{
   prosNode->go_goal("map",0.0, 0.0, 0.0, 0.9);
}

void Tab3TurtleBotControlPannel::on_pPBup_clicked()
{

}

void Tab3TurtleBotControlPannel::on_pPBdown_clicked()
{

}

void Tab3TurtleBotControlPannel::on_pPBleft_clicked()
{

}

void Tab3TurtleBotControlPannel::on_pPBright_clicked()
{

}

void Tab3TurtleBotControlPannel::on_pPBstop_clicked()
{

}
