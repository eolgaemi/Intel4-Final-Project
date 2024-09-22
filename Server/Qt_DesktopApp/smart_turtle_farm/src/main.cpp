#include "../include/smart_turtle_farm/mainwidget.h"
#include "../include/smart_turtle_farm/stftcpserver.h"
#include "../include/smart_turtle_farm/stftcpclienthandler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w(argc, argv);
    STFTcpServer *pSTFTcpServer = STFTcpServer::getInstance();
    pSTFTcpServer->startServer();
    w.show();
    return a.exec();
}
