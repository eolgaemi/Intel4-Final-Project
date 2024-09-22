#ifndef TAB3TURTLEBOTCONTROLPANNEL_H
#define TAB3TURTLEBOTCONTROLPANNEL_H

#include <QWidget>

namespace Ui {
class Tab3TurtleBotControlPannel;
}

class Tab3TurtleBotControlPannel : public QWidget
{
    Q_OBJECT

public:
    explicit Tab3TurtleBotControlPannel(QWidget *parent = nullptr);
    ~Tab3TurtleBotControlPannel();

private:
    Ui::Tab3TurtleBotControlPannel *ui;
};

#endif // TAB3TURTLEBOTCONTROLPANNEL_H
