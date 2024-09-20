#include "../include/smart_turtle_farm/tab3turtlebotcontrolpannel.h"
#include "ui_tab3turtlebotcontrolpannel.h"

Tab3TurtleBotControlPannel::Tab3TurtleBotControlPannel(int argc, char **argv, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab3TurtleBotControlPannel)
{
    ui->setupUi(this);
    LINEAR_MAX = 0.22; //Max 0.22
    ANGULAR_MAX = 2.84; //Max 2.84

    LINEAR_INTERVAL = LINEAR_MAX/10;
    ANGULAR_INTERVAL = ANGULAR_MAX/10;

    base_cmd.linear.x = 0.0;
    base_cmd.linear.y = 0.0;
    base_cmd.linear.z = 0.0;
    base_cmd.angular.x = 0.0;
    base_cmd.angular.y = 0.0;
    base_cmd.angular.z = 0.0;
    linearX = 0;
    angularZ = 0;
    baseCmdFlag = false;
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

void Tab3TurtleBotControlPannel::on_pPBForward_clicked()
{
    if(linearX <= 9 )
        linearX++;

    cmdVelPubSlot(linearX,angularZ);
}

void Tab3TurtleBotControlPannel::on_pPBBackward_clicked()
{
    if(-9 <= linearX )
        linearX--;
    cmdVelPubSlot(linearX,angularZ);
}

void Tab3TurtleBotControlPannel::on_pPBleft_clicked()
{
    if(angularZ <= 9 )
        angularZ++;
    cmdVelPubSlot(linearX,angularZ);
}

void Tab3TurtleBotControlPannel::on_pPBright_clicked()
{
    if(-9 <= angularZ)
        angularZ--;
    cmdVelPubSlot(linearX,angularZ);
}

void Tab3TurtleBotControlPannel::on_pPBstop_clicked()
{
    linearX = 0;
    angularZ = 0;
    cmdVelPubSlot(linearX,angularZ);
}

void Tab3TurtleBotControlPannel::cmdVelPubSlot(int linear,int angular)
{
    QString strLinear;
    QString strAngular;

    base_cmd.linear.x = LINEAR_INTERVAL * linear;
    base_cmd.angular.z = ANGULAR_INTERVAL * angular;

    if(linear != 0 || angular !=0 )
    {
        prosNode->set_cmd_vel(base_cmd);
        prosNode->set_cmdBaseCmd(true);
    }
    else
        prosNode->set_cmdBaseCmd(false);

    strLinear = QString::number(linear * 10);
    strLinear+='%';
    strAngular = QString::number(angular * 10);
    strAngular+='%';
    ui->pLBlinear->setText(strLinear);
    ui->pLBangular->setText(strAngular);
}

