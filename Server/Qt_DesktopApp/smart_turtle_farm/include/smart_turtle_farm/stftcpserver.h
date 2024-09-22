#ifndef STFTCPSERVER_H
#define STFTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QThreadPool>
#include <QObject>
#include <QHash>
#include <QDebug>
#include <QRunnable>
#include <functional>
#include "stftcpclienthandler.h"
#include "stftcpsqlclienthandler.h"

// 1. Client 인증용 TCP 서버 클래스
// 2. 정확한 메시지 전달을 위한 Client 간 통신 중계기

class STFTcpServer : public QTcpServer {
    Q_OBJECT

public:
    // 싱글톤 인스턴스 생성 및 반환
    static STFTcpServer* getInstance();

    // 서버 시작
    void startServer();

    // 인증 처리
    void authentication(QTcpSocket* clientSocket);

    // 자격 증명 반환 (예: 패스워드)
    QString getCredentials(QString);

    // 연결된 클라이언트 소켓 반환
    QTcpSocket* getSockets(const QString &ID);

    // 메시지에서 클라이언트 ID를 추출하는 함수
    QString parseClientId(const QString &message);

    // 메시지에서 비밀번호를 추출하는 함수
    QString parsePassword(const QString &message);

protected:
    // 클라이언트의 새 연결을 처리
    void incomingConnection(qintptr socketDescriptor) override;

private:
    // 외부에서 생성 불가한 생성자 (싱글톤 패턴)
    explicit STFTcpServer(QObject *parent = nullptr);

    // 소멸자
    ~STFTcpServer();

    // 싱글톤 인스턴스
    static STFTcpServer* pTcpServer;

    // ID와 패스워드 저장 (간단한 예시)
    QHash<QString, QString> clientCredentials = {
        {"STF_SQL" , "PASSWD"},
        {"STF_BOT1", "PASSWD"},
        {"STF_POT1", "PASSWD"},
        {"STF_POT2", "PASSWD"},
        {"STF_POT3", "PASSWD"},
        {"POT_SELECTOR", "PASSWD"},
        {"STF_ARD", "PASSWD"}
    };

    // ID와 소켓 포인터 저장 (간단한 예시)
    QHash<QString, QTcpSocket*> clientSockets = {
        {"STF_SQL" , nullptr},
        {"STF_ADM" , nullptr},
        {"STF_BOT1", nullptr},
        {"STF_POT1", nullptr},
        {"STF_POT2", nullptr},
        {"STF_POT3", nullptr},
        {"POT_SELECTOR", nullptr}
    };

signals:
    // 인증 성공 시그널
    void authenticationSuccess(const QString &userId, QTcpSocket *pTcpSocket);

public slots:
    // 인증 성공 처리
    void onAuthenticationSuccess(const QString &userId, QTcpSocket *pTcpSocket);

    // 메시지를 수신자에게 전달
    void forwardMessage(const QString &myid, const QString &receiverId, const QString &message);
};

// 클라이언트별 작업을 처리하는 클래스 (스레드 풀 사용)
class ClientTask :  public QObject, public QRunnable {
    Q_OBJECT
public:
    ClientTask(QTcpSocket *clientSocket, const QString &userId);

    void run() override;

private:
    QTcpSocket *clientSocket;
    QString userId;

    // 클라이언트가 보낸 메시지 처리
    void handleMessage(QTcpSocket *clientSocket);

    // 메시지 전달
    void forwardMessage(const QString &senderId, const QString &receiverId, const QString &message);
};

#endif // STFTCPSERVER_H
