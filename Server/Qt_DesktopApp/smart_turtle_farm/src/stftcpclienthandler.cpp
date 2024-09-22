#include "../include/smart_turtle_farm/stftcpclienthandler.h"
#include <QDebug>

STFTcpClientHandler::STFTcpClientHandler(qintptr socketDescriptor, const QString &myid, QObject *parent)
    : QObject(parent), socketDescriptor(socketDescriptor), myid(myid) {}

void STFTcpClientHandler::process() {
    socket = new QTcpSocket();

    if (!socket->setSocketDescriptor(socketDescriptor)) {
        qDebug() << "Error setting socket descriptor";
        emit finished();
        return;
    }
    connect(socket, &QTcpSocket::readyRead, this, [this]() {
        while (socket->canReadLine()) {  // 라인 단위로 처리
            QByteArray data = socket->readLine();
            QString message = QString::fromUtf8(data);

            // 메시지를 [수신자ID] 형태로 파싱
            if (message.startsWith("[") && message.contains("]")) {
                int closeBracketIndex = message.indexOf("]");

                // 수신자 ID 추출
                QString receiverId = message.mid(1, closeBracketIndex - 1);

                // 메시지 본문 추출
                QString messageBody = message.mid(closeBracketIndex + 1);

                qDebug() << "수신자ID:" << receiverId;
                qDebug() << "메시지:" << messageBody;

                emit messageToServer(myid, receiverId, messageBody);
            } else {
                qDebug() << "Invalid message format received";
            }
        }
    });


    connect(socket, &QTcpSocket::disconnected,this,[this]() {
        socket->close();
        emit finished();
    });
}
