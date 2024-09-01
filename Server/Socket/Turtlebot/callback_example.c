#include "callback_example.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
// 콜백 함수 1: 메시지의 길이를 출력
void example_callback1(void *arg) {
    char *msg = (char *)arg;
    printf("Callback 1: Message length = %ld\n", strlen(msg));
}

// 콜백 함수 2: 메시지를 대문자로 변환하여 출력
void example_callback2(void *arg) {
    char *msg = (char *)arg;
    printf("Callback 2: Uppercased message = ");
    for (int i = 0; msg[i]; i++) {
        printf("%c", toupper(msg[i]));
    }
    printf("\n");
}

