#include "../include/smart_turtle_farm/stftcpserver.h"
#include <QThreadPool>

STFTcpServer* STFTcpServer::pTcpServer = nullptr;

STFTcpServer* STFTcpServer::getInstance()
{
    return pTcpServer;
}

// 생성자: 외부에서 객체 생성을 막기 위해 private
STFTcpServer::STFTcpServer(QObject *parent)
    : QTcpServer(parent) {
}

// 소멸자
STFTcpServer::~STFTcpServer()
{
    if (pTcpServer)
    {
        delete pTcpServer;
        pTcpServer = nullptr;
    }
}

// 서버 시작 함수
void STFTcpServer::startServer()
{
    if (this->pTcpServer == nullptr)
    {
        this->pTcpServer = new STFTcpServer();
    }

    if (!this->listen(QHostAddress("10.42.0.1"), 5000))
    {
        qDebug() << "Server could not be started";
    } else
    {
        qDebug() << "Server started!";
    }
}

void STFTcpServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *clientSocket = new QTcpSocket(this);

    if (!clientSocket->setSocketDescriptor(socketDescriptor)) {
        qDebug() << "Error setting socket descriptor";
        return;
    }

    // 클라이언트 인증 처리
    connect(clientSocket, &QTcpSocket::readyRead, this, [this, clientSocket]() {
        authentication(clientSocket);
    });

    // 연결 종료 시 소켓 삭제
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
}

void STFTcpServer::authentication(QTcpSocket *clientSocket)
{
    QByteArray data = clientSocket->readAll();
    QString receivedMessage = QString::fromUtf8(data);

    QString clientId = parseClientId(receivedMessage);
    QString password = parsePassword(receivedMessage);

    if (clientCredentials.contains(clientId) && clientCredentials[clientId] == password) {
        qDebug() << "Authentication success for client:" << clientId;

        // 인증된 클라이언트를 관리하는 소켓 목록에 추가
        clientSockets[clientId] = clientSocket;

        // 인증 성공 후 메시지 처리
        disconnect(clientSocket, &QTcpSocket::readyRead, nullptr, nullptr); // 기존 readyRead 연결 해제
        onAuthenticationSuccess(clientId, clientSocket); // 인증 성공 후 핸들러 호출
    } else {
        qDebug() << "Authentication failed for client";
        clientSocket->disconnectFromHost();
    }
}

void STFTcpServer::onAuthenticationSuccess(const QString &userId, QTcpSocket *clientSocket)
{
    qDebug() << "Authentication successful for user:" << userId;

    // 환영 메시지 전송
    clientSocket->write("Welcome, " + userId.toUtf8() + "\r\n");

    // 스레드 풀에서 클라이언트 작업을 처리
    QThreadPool::globalInstance()->start(new ClientTask(clientSocket, userId));
}

QString STFTcpServer::parseClientId(const QString &message) {
    int colonIndex = message.indexOf(":");
    if (colonIndex != -1 && message.startsWith("[") && message.endsWith("]")) {
        return message.mid(1, colonIndex - 1);
    }
    return QString();
}

QString STFTcpServer::parsePassword(const QString &message) {
    int colonIndex = message.indexOf(":");
    if (colonIndex != -1 && message.startsWith("[") && message.endsWith("]")) {
        return message.mid(colonIndex + 1, message.length() - colonIndex - 2);
    }
    return QString();
}

QTcpSocket* STFTcpServer::getSockets(const QString &ID) {
    if (clientSockets.contains(ID)) {
        return clientSockets.value(ID, nullptr);
    }
    qDebug() << "No ID Error";
    return nullptr;
}

// ClientTask 생성자 구현
ClientTask::ClientTask(QTcpSocket *clientSocket, const QString &userId)
    : clientSocket(clientSocket), userId(userId) {}

// ClientTask의 실행 함수 정의
void ClientTask::run()
{
    connect(clientSocket, &QTcpSocket::readyRead, this, [this]() {
        handleMessage(clientSocket);
    });
}

// 클라이언트 메시지 처리
void ClientTask::handleMessage(QTcpSocket *clientSocket)
{
    QByteArray data = clientSocket->readAll();
    QString message = QString::fromUtf8(data);

    if (message.startsWith("[") && message.contains("->")) {
        int senderEndIndex = message.indexOf("->");
        int receiverEndIndex = message.indexOf("]");

        QString senderId = message.mid(1, senderEndIndex - 1);
        QString receiverId = message.mid(senderEndIndex + 2, receiverEndIndex - senderEndIndex - 2);
        QString actualMessage = message.mid(receiverEndIndex + 1);

        forwardMessage(senderId, receiverId, actualMessage);
    } else {
        qDebug() << "Invalid message format received";
    }
}

// 메시지 전달
void ClientTask::forwardMessage(const QString &senderId, const QString &receiverId, const QString &message)
{
    QString formattedMessage = QString("[%1->%2]%3").arg(senderId).arg(receiverId).arg(message);

    QTcpSocket *receiverSock = STFTcpServer::getInstance()->getSockets(receiverId);

    if (receiverSock != nullptr) {
        receiverSock->write(formattedMessage.toUtf8());
    } else {
        qDebug() << "Receiver socket not found for ID:" << receiverId;
    }
}
