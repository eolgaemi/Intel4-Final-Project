#ifndef TAB3TURTLEBOTCONTROLPANNEL_H
#define TAB3TURTLEBOTCONTROLPANNEL_H

#include <QWidget>
#include <QDebug>
#include "rosnode.h"

namespace Ui {
class Tab3TurtleBotControlPannel;
}

class Tab3TurtleBotControlPannel : public QWidget
{
    Q_OBJECT

public:
    explicit Tab3TurtleBotControlPannel(int argc, char **argv, QWidget *parent = nullptr);
    ~Tab3TurtleBotControlPannel();

private:
    Ui::Tab3TurtleBotControlPannel *ui;
    RosNode *prosNode;
    geometry_msgs::Twist base_cmd;
    bool baseCmdFlag;
    int linearX;
    int angularZ;
    float LINEAR_MAX;
    float ANGULAR_MAX;

    float LINEAR_INTERVAL;
    float ANGULAR_INTERVAL;

private slots:
    void goal_Pub_Coord1();
    void goal_Pub_Coord2();
    void goal_Pub_Coord3();
    void goal_Pub_Coord4();
    void goal_Pub_Coord5();
    void goal_Pub_Coord6();

    void on_pPBForward_clicked();
    void on_pPBBackward_clicked();
    void on_pPBleft_clicked();
    void on_pPBright_clicked();
    void on_pPBstop_clicked();
    void cmdVelPubSlot(int,int);

};

#endif // TAB3TURTLEBOTCONTROLPANNEL_H
