/*
 * uartIO.h
 *
 *  Created on: Aug 31, 2024
 *      Author: IOT
 */

#ifndef INC_UARTIO_H_
#define INC_UARTIO_H_
#include <stdio.h>
#include "stm32f4xx_hal.h"
#ifdef __cplusplus
extern "C"
{
#endif
int __io_putchar(int ch);
#ifdef __cplusplus
}
#endif
void uartIO_Init(void);
void USART2_RxCpltHandler(UART_HandleTypeDef *huart);
#endif /* INC_UARTIO_H_ */
