#include "iot_client_cbf.h"
#include "callback_example.h"  // 추가: 콜백 함수 헤더 파일 포함
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>

static iot_client *client;  // 전역 클라이언트 포인터

// 클라이언트 초기화 함수
void client_init(void)
{   
    static iot_client client_instance;
    snprintf(client_instance.name, NAME_SIZE, "[Default]");
    client_instance.cbf_idx = 0;
    client = &client_instance;
}

// 콜백 함수 등록 함수
void reg_client_cbf(callback_func_t cbf)
{
    if (client->cbf_idx < MAX_CBF) {  // 배열 범위 초과 방지
        client->client_cbf[client->cbf_idx++] = (uintptr_t)cbf;
    } else {
        error_handling("Callback function buffer overflow");
    }
}

// 메시지를 서버로 전송하는 함수
void *send_msg(void *arg)
{
    int *sock = (int *)arg;  // 서버와 통신할 소켓
    fd_set initset, newset;
    struct timeval tv;
    char name_msg[NAME_SIZE + BUF_SIZE + 2];

    FD_ZERO(&initset);
    FD_SET(STDIN_FILENO, &initset);

    fputs("Input a message! [ID]msg (Default ID:ALLMSG)\n", stdout);
    while(1) {
        memset(client->msg, 0, sizeof(client->msg));
        name_msg[0] = '\0';
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        newset = initset;
        int ret = select(STDIN_FILENO + 1, &newset, NULL, NULL, &tv);
        if(FD_ISSET(STDIN_FILENO, &newset)) {
            fgets(client->msg, BUF_SIZE, stdin);
            if(!strncmp(client->msg, "quit\n", 5)) {
                *sock = -1;
                return NULL;
            } else if(client->msg[0] != '[') {
                strcat(name_msg, "[ALLMSG]");
                strcat(name_msg, client->msg);
            } else {
                strcpy(name_msg, client->msg);
            }
            if(write(*sock, name_msg, strlen(name_msg)) <= 0) {
                *sock = -1;
                return NULL;
            }
        }
        if(ret == 0 && *sock == -1) {
            return NULL;
        }
    }
}

// 서버에서 메시지를 수신하는 함수
void *recv_msg(void *arg)
{
    int *sock = (int *)arg;
    char name_msg[NAME_SIZE + BUF_SIZE + 1];
    int str_len;

    while(1) {
        memset(name_msg, 0x0, sizeof(name_msg));
        str_len = read(*sock, name_msg, NAME_SIZE + BUF_SIZE);
        if(str_len <= 0) {
            *sock = -1;
            return NULL;
        }
        name_msg[str_len] = 0;
        fputs(name_msg, stdout);

        // 추가: 등록된 콜백 함수들을 실행
        for (int i = 0; i < client->cbf_idx; i++) {
            callback_func_t cbf = (callback_func_t)client->client_cbf[i];
            if (cbf) {
                cbf(name_msg);  // 콜백 함수 실행
            }
        }
    }
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void error_handling(const char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

// SIGINT 신호 처리기 함수
void handle_sigint(int sig) {
    if (client->server_sock != -1) {
        // 서버에 연결 종료 메시지를 보냄
        write(client->server_sock, "[ALLMSG]Client Disconnected\n", strlen("[ALLMSG]Client Disconnected\n"));
        close(client->server_sock);  // 소켓을 닫음
    }
    exit(0);  // 프로그램 종료
}

int main(int argc, char *argv[])
{   
    client_init();

    if(argc != 4) {
        printf("Usage: %s <IP> <port> <name>\n", argv[0]);
        exit(1);
    }

    // SIGINT 신호 처리기 설정
    signal(SIGINT, handle_sigint);

    // 이름을 클라이언트 구조체에 저장
    snprintf(client->name, NAME_SIZE, "%s", argv[3]);

    // 소켓 생성
    client->server_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(client->server_sock == -1)
        error_handling("socket() error");

    // 서버 주소 구조체 초기화
    memset(&client->serv_addr, 0, sizeof(client->serv_addr));
    client->serv_addr.sin_family = AF_INET;
    client->serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    client->serv_addr.sin_port = htons(atoi(argv[2]));

    // 서버에 연결 시도
    if(connect(client->server_sock, (struct sockaddr *)&client->serv_addr, sizeof(client->serv_addr)) == -1)
        error_handling("connect() error");

    // 서버에 사용자 이름과 'PASSWD' 메시지 전송
    snprintf(client->msg, BUF_SIZE, "[%s:PASSWD]", client->name);
    write(client->server_sock, client->msg, strlen(client->msg));

    // 추가: 콜백 함수 등록
    reg_client_cbf(example_callback1);
    reg_client_cbf(example_callback2);

    // 메시지 수신 및 송신을 위한 스레드 생성
    pthread_create(&client->rcv_thread, NULL, recv_msg, (void *)&client->server_sock);
    pthread_create(&client->snd_thread, NULL, send_msg, (void *)&client->server_sock);

    // 메시지 송신 스레드가 종료될 때까지 대기
    pthread_join(client->snd_thread, &client->thread_return);

    // 소켓을 닫고 프로그램 종료
    close(client->server_sock);
    return 0;
}

