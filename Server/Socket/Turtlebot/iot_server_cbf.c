#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <errno.h>

#define BUF_SIZE 100    // 메시지 버퍼의 크기
#define MAX_CLNT 32     // 최대 클라이언트 수
#define ID_SIZE 10      // 사용자 ID의 최대 길이
#define ARR_CNT 5       // 토큰화된 문자열 배열의 최대 크기
#define SERVER_BACKLOG_Q 5

typedef struct {
    int index;               // 클라이언트 인덱스
    int fd;                  // 클라이언트와의 연결 소켓
    char ip[20];             // 클라이언트 IP 주소
    char id[ID_SIZE];        // 클라이언트 ID
    char pw[ID_SIZE];        // 클라이언트 비밀번호
} CLIENT_INFO;

typedef struct {
    char fd;                 // 메시지의 송신자 소켓
    char *from;              // 메시지 송신자 ID
    char *to;                // 메시지 수신자 ID (ALLMSG, IDLIST 포함)
    char *msg;               // 전송할 메시지
    int len;                 // 메시지 길이
} MSG_INFO;

void * clnt_connection(void * arg);      // 클라이언트와의 연결을 처리하는 함수
void send_msg(MSG_INFO * msg_info, CLIENT_INFO * first_client_info);  // 메시지를 클라이언트로 전송하는 함수
void error_handling(char * msg);         // 에러 메시지를 출력하고 프로그램을 종료하는 함수
void log_file(char * msgstr);            // 로그 메시지를 출력하는 함수

int clnt_cnt = 0;  // 현재 연결된 클라이언트 수
long str_len;
pthread_mutex_t mutx;  // 클라이언트 수 관리를 위한 뮤텍스

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;                    // 서버 소켓 및 클라이언트 소켓
    struct sockaddr_in serv_adr, clnt_adr;       // 서버 및 클라이언트 주소 구조체
    int clnt_adr_sz;
    int sock_option  = 1;
    pthread_t t_id[MAX_CLNT] = {0};              // 클라이언트 처리를 위한 스레드 ID 배열
    char idpasswd[(ID_SIZE*2) + 3];              // ID와 비밀번호를 저장할 버퍼
    char *pToken;                                // 문자열 토큰화에 사용할 포인터
    char *pArray[ARR_CNT] = {0};                 // 토큰화된 문자열 배열
    char msg[BUF_SIZE];                          // 메시지 버퍼

    CLIENT_INFO client_info[MAX_CLNT] = {        // 클라이언트 정보를 저장할 배열
        {0,-1,"","JYJ_STM","PASSWD"},
        {0,-1,"","JYJ_UBT","PASSWD"}, 
        // (추가 클라이언트 정보)
    };

    if(argc != 2) {  // 프로그램 사용법 출력 및 종료
        printf("Usage : %s <port>\n",argv[0]);
        exit(1);
    }
    fputs("IoT Server Start!!\n",stdout);  // 서버 시작 메시지 출력

    if(pthread_mutex_init(&mutx, NULL))  // 뮤텍스 초기화
        error_handling("mutex init error");

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);  // 서버 소켓 생성

    memset(&serv_adr, 0, sizeof(serv_adr));  // 서버 주소 구조체 초기화
    serv_adr.sin_family = AF_INET;           // 주소 체계 설정 (IPv4)
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);  // 모든 IP로부터의 연결 허용
    serv_adr.sin_port = htons(atoi(argv[1]));  // 포트 번호 설정

    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (void*)&sock_option, sizeof(sock_option));  // 주소 재사용 옵션 설정
    if(bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)  // 소켓 바인딩
        error_handling("bind() error");

    if(listen(serv_sock, SERVER_BACKLOG_Q) == -1)  // 연결 요청 대기 상태로 변경
        error_handling("listen() error");

    while(1) {
        clnt_adr_sz = sizeof(clnt_adr);  // 클라이언트 주소 크기 설정
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);  // 클라이언트 연결 수락
        if(clnt_cnt >= MAX_CLNT)  // 최대 클라이언트 수 초과 시 처리
        {
            printf("socket full\n");
            shutdown(clnt_sock, SHUT_WR);  // 쓰기 스트림 닫기
            continue;
        }
        else if(clnt_sock < 0)  // 연결 수락 실패 시 오류 출력
        {
            perror("accept()");
            continue;
        }

        str_len = read(clnt_sock, idpasswd, sizeof(idpasswd));  // 클라이언트로부터 ID와 비밀번호 수신
        idpasswd[str_len] = '\0';  // 문자열 종료 처리

        if(str_len > 0)
        {
            int i = 0;
            pToken = strtok(idpasswd,"[:]");  // ID와 비밀번호를 ':'으로 구분하여 토큰화

            while(pToken != NULL)
            {
                pArray[i] = pToken;  // 토큰화된 문자열 배열에 저장
                if(i++ >= ARR_CNT)
                    break;
                pToken = strtok(NULL,"[:]");
            }

            for(i = 0; i < MAX_CLNT; i++)
            {
                if(!strcmp(client_info[i].id, pArray[0]))  // ID 일치 여부 확인
                {
                    if(client_info[i].fd != -1)  // 이미 로그인된 상태인지 확인
                    {
                        sprintf(msg,"[%s] Already logged!\n", pArray[0]);
                        write(clnt_sock, msg, strlen(msg));  // 이미 로그인된 경우 메시지 전송
                        log_file(msg);
                        shutdown(clnt_sock, SHUT_WR);  // 쓰기 스트림 닫기
                        break;
                    }
                    if(!strcmp(client_info[i].pw, pArray[1]))  // 비밀번호 일치 여부 확인
                    {
                        strcpy(client_info[i].ip, inet_ntoa(clnt_adr.sin_addr));  // 클라이언트 IP 주소 저장
                        pthread_mutex_lock(&mutx);  // 클라이언트 수 증가를 위한 뮤텍스 잠금
                        client_info[i].index = i; 
                        client_info[i].fd = clnt_sock; 
                        clnt_cnt++;
                        pthread_mutex_unlock(&mutx);  // 뮤텍스 잠금 해제
                        sprintf(msg,"[%s] New connected! (ip:%s,fd:%d,sockcnt:%d)\n", pArray[0], inet_ntoa(clnt_adr.sin_addr), clnt_sock, clnt_cnt);
                        log_file(msg);
                        write(clnt_sock, msg, strlen(msg));  // 연결 성공 메시지 전송

                        pthread_create(t_id+i, NULL, clnt_connection, (void *)(client_info + i));  // 클라이언트와의 통신을 위한 스레드 생성
                        pthread_detach(t_id[i]);  // 스레드를 분리하여 종료 후 자동으로 자원 회수
                        break;
                    }
                }
            }
            if(i == MAX_CLNT)  // 인증 실패 시 처리
            {
                sprintf(msg,"[%s] Authentication Error!\n", pArray[0]);
                write(clnt_sock, msg, strlen(msg));  // 인증 오류 메시지 전송
                log_file(msg);
                shutdown(clnt_sock, SHUT_WR);  // 쓰기 스트림 닫기
            }
        }
        else 
            shutdown(clnt_sock, SHUT_WR);  // 연결 수락 실패 시 소켓 종료
    }
    return 0;
}

void * clnt_connection(void *arg)
{
    CLIENT_INFO *client_info = (CLIENT_INFO *)arg;  // 클라이언트 정보 구조체 포인터
    int str_len = 0;
    char msg[BUF_SIZE];  // 클라이언트로부터 수신한 메시지를 저장할 버퍼
    char to_msg[MAX_CLNT*ID_SIZE + 1];  // 전송할 메시지를 저장할 버퍼
    int i = 0;
    char *pToken;
    char *pArray[ARR_CNT] = {0};  // 토큰화된 문자열 배열
    char strBuff[130] = {0};  // 로그 메시지 저장용 버퍼

    MSG_INFO msg_info;  // 메시지 정보를 저장할 구조체
    CLIENT_INFO *first_client_info;  // 첫 번째 클라이언트의 정보를 가리키는 포인터

    first_client_info = (CLIENT_INFO *)((void *)client_info - (void *)(sizeof(CLIENT_INFO) * client_info->index));  // 첫 번째 클라이언트 정보 설정

    while(1)
    {
        memset(msg, 0x0, sizeof(msg));  // 메시지 버퍼 초기화
        str_len = read(client_info->fd, msg, sizeof(msg) - 1);  // 클라이언트로부터 메시지 수신
        if(str_len <= 0)  // 클라이언트가 연결을 끊었거나 오류 발생
        {
            if (str_len == 0) {
                sprintf(strBuff, "Disconnect ID:%s (ip:%s,fd:%d,sockcnt:%d)\n", client_info->id, client_info->ip, client_info->fd, clnt_cnt - 1);  // 로그 메시지 설정
                log_file(strBuff);  // 로그 기록
            }
            break;
        }

        msg[str_len] = '\0';  // 문자열 종료 처리
        pToken = strtok(msg, "[:]");  // 수신된 메시지 토큰화
        i = 0; 
        while(pToken != NULL)
        {
            pArray[i] = pToken;  // 토큰화된 문자열 배열에 저장
            if(i++ >= ARR_CNT)
                break; 
            pToken = strtok(NULL, "[:]");
        }

        msg_info.fd = client_info->fd;  // 송신자 소켓 설정
        msg_info.from = client_info->id;  // 송신자 ID 설정
        msg_info.to = pArray[0];  // 수신자 ID 설정
        sprintf(to_msg, "[%s]%s", msg_info.from, pArray[1]);  // 메시지 형식 설정
        msg_info.msg = to_msg;  // 메시지 설정
        msg_info.len = strlen(to_msg);  // 메시지 길이 설정

        sprintf(strBuff, "msg : [%s->%s] %s", msg_info.from, msg_info.to, pArray[1]);  // 로그 메시지 설정
        log_file(strBuff);  // 로그 기록
        send_msg(&msg_info, first_client_info);  // 메시지 전송
    }

    // 클라이언트가 연결을 끊었을 때 처리
    close(client_info->fd);  // 클라이언트 소켓 닫기
    pthread_mutex_lock(&mutx);  // 클라이언트 수 감소를 위한 뮤텍스 잠금
    clnt_cnt--;
    client_info->fd = -1;  // 클라이언트의 fd를 무효화
    pthread_mutex_unlock(&mutx);  // 뮤텍스 잠금 해제

    return 0;
}

// 메시지를 클라이언트로 전송하는 함수
void send_msg(MSG_INFO *msg_info, CLIENT_INFO *first_client_info)
{
    int i = 0;

    if(!strcmp(msg_info->to, "ALLMSG"))  // 모든 클라이언트에게 메시지 전송
    {
        for(i = 0; i < MAX_CLNT; i++)
            if((first_client_info + i)->fd != -1)  // 유효한 소켓이 있는 클라이언트에게만 전송
                write((first_client_info + i)->fd, msg_info->msg, msg_info->len);
    }
    else if(!strcmp(msg_info->to, "IDLIST"))  // 클라이언트의 ID 리스트 요청 처리
    {
        char *idlist = (char *)malloc(ID_SIZE * MAX_CLNT);  // ID 리스트 저장용 버퍼 할당
        msg_info->msg[strlen(msg_info->msg) - 1] = '\0';  // 메시지의 끝에 있는 newline을 제거
        strcpy(idlist, msg_info->msg);  // 메시지를 ID 리스트로 복사

        for(i = 0; i < MAX_CLNT; i++)
        {
            if((first_client_info + i)->fd != -1)  // 유효한 클라이언트 소켓이 있는 경우
            {
                strcat(idlist, (first_client_info + i)->id);  // 클라이언트 ID 추가
                strcat(idlist, " ");
            }
        }
        strcat(idlist, "\n");  // ID 리스트의 끝에 newline 추가
        write(msg_info->fd, idlist, strlen(idlist));  // 요청한 클라이언트에게 ID 리스트 전송
        free(idlist);  // 할당한 버퍼 해제
    }
    else  // 특정 클라이언트에게만 메시지 전송
    {
        for(i = 0; i < MAX_CLNT; i++)
            if((first_client_info + i)->fd != -1)  // 유효한 소켓이 있는 클라이언트에게만 전송
                if(!strcmp(msg_info->to, (first_client_info + i)->id))  // 메시지의 대상이 해당 클라이언트인지 확인
                    write((first_client_info + i)->fd, msg_info->msg, msg_info->len);  // 메시지 전송
    }
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void error_handling(char *msg)
{
    fputs(msg, stderr);  // 에러 메시지를 표준 에러 출력에 출력
    fputc('\n', stderr);
    exit(1);  // 프로그램 종료
}

// 로그 메시지를 출력하는 함수
void log_file(char *msgstr)
{
    fputs(msgstr, stdout);  // 로그 메시지를 표준 출력에 출력
}
