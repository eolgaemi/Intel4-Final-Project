#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "tab1controlpannel.h"
#include "tab2potstatuspannel.h"
#include "tab3turtlebotcontrolpannel.h"
#include "tab4adminlogin.h"
#include "tab4adminpannel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(int argc, char** argv, QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    Tab1ControlPannel *pTab1ControlPannel;
    Tab2PotStatusPannel *pTab2PotStatusPannel;
    Tab3TurtleBotControlPannel *pTab3TurtleBotControlPannel;
    Tab4AdminLogin *pTab4AdminLogin;
    Tab4AdminPannel *pTab4AdminPannel;
};
#endif // MAINWIDGET_H
