#ifndef TAB1CONTROLPANNEL_H
#define TAB1CONTROLPANNEL_H

#include <QWidget>

namespace Ui {
class Tab1ControlPannel;
}

class Tab1ControlPannel : public QWidget
{
    Q_OBJECT

public:
    explicit Tab1ControlPannel(QWidget *parent = nullptr);
    ~Tab1ControlPannel();

private:
    Ui::Tab1ControlPannel *ui;
};

#endif // TAB1CONTROLPANNEL_H
