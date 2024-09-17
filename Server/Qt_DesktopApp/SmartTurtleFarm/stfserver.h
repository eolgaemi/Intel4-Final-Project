#ifndef STFSERVER_H
#define STFSERVER_H

#include <QObject>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>

class STFServer : public QObject
{
    Q_OBJECT
public:
    explicit STFServer(QObject *parent = nullptr);

signals:
};

#endif // STFSERVER_H
