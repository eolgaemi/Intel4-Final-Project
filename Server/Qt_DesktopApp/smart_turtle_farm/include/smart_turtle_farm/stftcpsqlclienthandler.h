#ifndef STFTCPSQLCLIENTHANDLER_H
#define STFTCPSQLCLIENTHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include "stftcpserver.h"

class STFTcpSqlClientHandler : public QObject
{
    Q_OBJECT

public:
    explicit STFTcpSqlClientHandler(qintptr socketDescriptor, const QString &myid = "", QObject *parent = nullptr);

signals:
    void receivedSqlMessage(const QString &senderId, QStringList parsedMessage);
    void finished();

public slots:
    void process();
    void saveSqlMessage(const QString &senderId, QStringList parsedMessage);

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    QString myid;
};

#endif // STFTCPSQLCLIENTHANDLER_H
