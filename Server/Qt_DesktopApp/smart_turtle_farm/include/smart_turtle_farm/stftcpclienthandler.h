#ifndef STFTCPCLIENTHANDLER_H
#define STFTCPCLIENTHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include "stftcpserver.h"

class STFTcpClientHandler : public QObject
{
    Q_OBJECT

public:
    explicit STFTcpClientHandler(qintptr socketDescriptor, const QString &myid = "", QObject *parent = nullptr);

signals:
    void messageToServer(const QString &myid,const QString &receiverId, const QString &message);
    void finished();

public slots:
    void process();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    QString myid;
};


#endif // STFTCPCLIENTHANDLER_H
