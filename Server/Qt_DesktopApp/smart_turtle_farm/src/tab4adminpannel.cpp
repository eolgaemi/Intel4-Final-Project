#include "../include/smart_turtle_farm/tab4adminpannel.h"
#include "ui_tab4adminpannel.h"

Tab4AdminPannel::Tab4AdminPannel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab4AdminPannel)
{
    ui->setupUi(this);
}

Tab4AdminPannel::~Tab4AdminPannel()
{
    delete ui;
}
