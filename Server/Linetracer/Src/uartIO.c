/*
 * uartIO.c
 *
 *  Created on: Aug 31, 2024
 *      Author: IOT
 */
#include "uartIO.h"

volatile unsigned char rx2Flag = 0;
volatile char rx2Data[50];
uint8_t cdata;
extern UART_HandleTypeDef huart2;

int __io_putchar(int ch){
    if(HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xffff) == HAL_OK)
    {
        return ch;
    }
    else
    	return -1;
}

void uartIO_Init(void){
	HAL_UART_Receive_IT(&huart2, &cdata,1);
	printf("UART2 Initialized...\n");
}

void USART2_RxCpltHandler(UART_HandleTypeDef *huart)
{
    static int i = 0;

    if (huart->Instance == USART2) // Check if the interrupt is from USART2
    {
        if (cdata != '\n' && cdata != '\r') // Ignore newline and carriage return
        {
            rx2Data[i++] = cdata; // Store received character
        }

        if (cdata == '\n' || cdata == '\r' || i >= sizeof(rx2Data) - 1) // End of message or buffer full
        {
            rx2Data[i] = '\0'; // Null-terminate the string
            rx2Flag = 1; // Set the flag to indicate data is ready
            i = 0; // Reset the index for the next message
        }

        // Re-enable UART receive interrupt to prepare for the next character
        HAL_UART_Receive_IT(huart, &cdata, 1);
    }
}
