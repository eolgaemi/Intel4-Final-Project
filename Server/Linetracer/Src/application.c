/*
 * application.c
 *
 *  Created on: Aug 31, 2024
 *      Author: IOT
 */

#include "wifiCom.h"
#include "uartIO.h"

void application_Init(void){
	uartIO_Init();
	wifiCom_Init();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART2) {
    	USART2_RxCpltHandler(huart);
    } else if (huart->Instance == USART6) {
        USART6_RxCpltHandler(huart);
    }
}
