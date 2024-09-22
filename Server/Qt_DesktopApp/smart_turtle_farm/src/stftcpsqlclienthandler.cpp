#include "../include/smart_turtle_farm/stftcpsqlclienthandler.h"
#include <QDebug>

STFTcpSqlClientHandler::STFTcpSqlClientHandler(qintptr socketDescriptor, const QString &myid, QObject *parent)
    : QObject(parent), socketDescriptor(socketDescriptor), myid(myid) {}

void STFTcpSqlClientHandler::process() {
    socket = new QTcpSocket();
    connect(socket, &QTcpSocket::readyRead, this, [this]() {
        QByteArray data = socket->readAll();
        QString message = QString::fromUtf8(data);

        // 메시지를 [송신자ID] 형태로 파싱
        if (message.startsWith("[") && message.contains("]")) {
            int closeBracketIndex = message.indexOf("]");

            // 송신자 ID 추출
            QString senderId = message.mid(1, closeBracketIndex - 1);

            // 메시지 본문 추출 ("]" 이후의 문자열)
            QString messageBody = message.mid(closeBracketIndex + 1);

            // 메시지를 "@"로 구분하여 QStringList에 저장 -> SQL에 활용
            QStringList parsedMessages = messageBody.split("@");

            emit receivedSqlMessage(senderId,parsedMessages);
        } else {
            qDebug() << "Invalid message format received";
        }
    });
}

void STFTcpSqlClientHandler::saveSqlMessage(const QString &senderId, QStringList parsedMessage)
{

    qDebug() << senderId;
    /*
    if(senderId.contains("STF_POT"))
    {
        QDateTime dateTime = QDateTime::currentDateTime();

        bool ok;
        uint16_t illu = static_cast<uint8_t>(parsedMessage.at(0).toUInt(&ok));
        float_t temp_A = static_cast<float_t>(parsedMessage.at(1).toFloat(&ok));
        float_t humi_A = static_cast<float_t>(parsedMessage.at(2).toFloat(&ok));
        float_t temp_S = static_cast<float_t>(parsedMessage.at(3).toFloat(&ok));
        float_t humi_S = static_cast<float_t>(parsedMessage.at(4).toFloat(&ok));
        float_t EC_S = static_cast<float_t>(parsedMessage.at(5).toFloat(&ok));
        float_t pH_S = static_cast<float_t>(parsedMessage.at(6).toFloat(&ok));


        QString strQuery = "insert into pot_status(name , date , illu , temp_A , humi_A , temp_S , humi_S , EC_S , pH_S) values ( '" +
                           senderId + "' , '" +
                           dateTime.toString("yyyy/MM/dd hh:mm:ss") + "' , '" +
                           parsedMessage.at(0) + "' , '" +
                           parsedMessage.at(1) + "' , '" +
                           parsedMessage.at(2) + "' , '" +
                           parsedMessage.at(3) + "' , '" +
                           parsedMessage.at(4) + "' , '" +
                           parsedMessage.at(5) + "' , '" +
                           parsedMessage.at(6) + "')";

        QSqlQuery sqlQuery;
        if(!sqlQuery.exec(strQuery)){
            qDebug() << "insert query fail";;
        } else {
            qDebug() << "insert query ok";
        }
    }
    else if(senderId == "STF_POT2")
    {

    }
    */
}
