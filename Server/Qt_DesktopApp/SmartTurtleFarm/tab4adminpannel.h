#ifndef TAB4ADMINPANNEL_H
#define TAB4ADMINPANNEL_H

#include <QWidget>

namespace Ui {
class Tab4AdminPannel;
}

class Tab4AdminPannel : public QWidget
{
    Q_OBJECT

public:
    explicit Tab4AdminPannel(QWidget *parent = nullptr);
    ~Tab4AdminPannel();

private:
    Ui::Tab4AdminPannel *ui;
};

#endif // TAB4ADMINPANNEL_H
