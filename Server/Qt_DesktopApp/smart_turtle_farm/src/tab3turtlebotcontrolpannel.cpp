#include "../include/smart_turtle_farm/tab3turtlebotcontrolpannel.h"
#include "ui_tab3turtlebotcontrolpannel.h"

Tab3TurtleBotControlPannel::Tab3TurtleBotControlPannel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab3TurtleBotControlPannel)
{
    ui->setupUi(this);
}

Tab3TurtleBotControlPannel::~Tab3TurtleBotControlPannel()
{
    delete ui;
}
