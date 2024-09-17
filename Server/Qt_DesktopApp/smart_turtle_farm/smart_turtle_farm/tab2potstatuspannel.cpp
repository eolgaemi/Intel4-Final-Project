#include "tab2potstatuspannel.h"
#include "ui_tab2potstatuspannel.h"

Tab2PotStatusPannel::Tab2PotStatusPannel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab2PotStatusPannel)
{
    ui->setupUi(this);
}

Tab2PotStatusPannel::~Tab2PotStatusPannel()
{
    delete ui;
}
