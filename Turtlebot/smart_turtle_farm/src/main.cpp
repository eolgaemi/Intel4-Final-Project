#include "../include/smart_turtle_farm/mainwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w(argc, argv);
    w.show();
    return a.exec();
}
