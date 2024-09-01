#ifndef IOT_CLIENT_CBF_H
#define IOT_CLIENT_CBF_H

#include <stdint.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUF_SIZE 100    // 메시지 버퍼의 크기
#define NAME_SIZE 20    // 사용자 이름의 최대 길이
#define MAX_CBF 10      // 최대 콜백 함수 수

typedef void (*callback_func_t)(void *arg);  // 콜백 함수의 타입 정의

typedef struct {
    char name[NAME_SIZE];               // 클라이언트의 이름
    char msg[BUF_SIZE];                 // 메시지를 저장할 버퍼
    int server_sock;                    // 서버의 소켓 저장용
    struct sockaddr_in serv_addr;       // 서버의 주소 정보를 담을 구조체
    pthread_t snd_thread, rcv_thread;   // 메시지 송신 및 수신 스레드를 위한 변수
    void *thread_return;                // 스레드 종료 시 반환 값을 받을 포인터
    uintptr_t client_cbf[MAX_CBF];      // 콜백 함수 포인터 배열
    uint8_t cbf_idx;                    // 등록된 콜백 함수의 개수
} iot_client;

void client_init(void);                       // 클라이언트 초기화 함수
void reg_client_cbf(callback_func_t cbf);     // 콜백 함수 등록 함수
void *send_msg(void *arg);                    // 메시지를 서버로 전송하는 스레드 함수
void *recv_msg(void *arg);                    // 서버에서 메시지를 수신하는 스레드 함수
void error_handling(const char *msg);         // 에러 발생 시 메시지를 출력하고 프로그램을 종료하는 함수

#endif // IOT_CLIENT_CBF_H

