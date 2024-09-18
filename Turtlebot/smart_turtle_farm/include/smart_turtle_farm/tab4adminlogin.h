#ifndef TAB4ADMINLOGIN_H
#define TAB4ADMINLOGIN_H

#include <QWidget>

namespace Ui {
class Tab4AdminLogin;
}

class Tab4AdminLogin : public QWidget
{
    Q_OBJECT

public:
    explicit Tab4AdminLogin(QWidget *parent = nullptr);
    ~Tab4AdminLogin();

private:
    Ui::Tab4AdminLogin *ui;
};

#endif // TAB4ADMINLOGIN_H
