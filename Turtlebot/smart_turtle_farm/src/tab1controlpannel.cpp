#include "../include/smart_turtle_farm/tab1controlpannel.h"
#include "ui_tab1controlpannel.h"

Tab1ControlPannel::Tab1ControlPannel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab1ControlPannel)
{
    ui->setupUi(this);
}

Tab1ControlPannel::~Tab1ControlPannel()
{
    delete ui;
}
