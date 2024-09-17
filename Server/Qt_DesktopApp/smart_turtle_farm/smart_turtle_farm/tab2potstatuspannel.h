#ifndef TAB2POTSTATUSPANNEL_H
#define TAB2POTSTATUSPANNEL_H

#include <QWidget>

namespace Ui {
class Tab2PotStatusPannel;
}

class Tab2PotStatusPannel : public QWidget
{
    Q_OBJECT

public:
    explicit Tab2PotStatusPannel(QWidget *parent = nullptr);
    ~Tab2PotStatusPannel();

private:
    Ui::Tab2PotStatusPannel *ui;
};

#endif // TAB2POTSTATUSPANNEL_H
