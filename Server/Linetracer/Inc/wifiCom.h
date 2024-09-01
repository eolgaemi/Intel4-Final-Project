/*
 * wifiCom.h
 *
 *  Created on: Aug 31, 2024
 *      Author: IOT
 */

#ifndef INC_WIFICOM_H_
#define INC_WIFICOM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f4xx_hal.h"

#define MAX_ESP_RX_BUFFER      1024
#define MAX_ESP_COMMAND_LEN    64
#define MAX_ESP_CLIENT_NUM     10

#define SSID "iot0"
#define PASS "iot00000"
#define LOGID "JYJ_STM"
#define PASSWD "PASSWD"
#define SERVER_IP "10.10.141.52"
#define SERVER_PORT 5000
#define ARR_CNT 5

void wifiCom_Init(void);

typedef struct _cb_data_t
{
    uint8_t buf[MAX_ESP_RX_BUFFER];
    uint16_t length;
}cb_data_t;

int drv_esp_init(void);
int drv_esp_test_command(void);
void AiotClient_Init(void);
int esp_client_conn(void);
void esp_send_data(char *data);

//==================uart6=========================
#define MAX_UART_RX_BUFFER      1024
#define MAX_UART_COMMAND_LEN    64

int drv_uart_init(void);
int drv_uart_rx_buffer(uint8_t *buf, uint16_t size);
int drv_uart_tx_buffer(uint8_t *buf, uint16_t size);
void USART6_RxCpltHandler(UART_HandleTypeDef *huart);
void wifi_app(void);
void esp_event(char * recvBuf);
//==================uart6=========================


#endif /* INC_WIFICOM_H_ */
