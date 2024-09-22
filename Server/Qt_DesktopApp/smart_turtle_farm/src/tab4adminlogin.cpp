#include "../include/smart_turtle_farm/tab4adminlogin.h"
#include "ui_tab4adminlogin.h"

Tab4AdminLogin::Tab4AdminLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab4AdminLogin)
{
    ui->setupUi(this);
}

Tab4AdminLogin::~Tab4AdminLogin()
{
    delete ui;
}
