/*
 * application.h
 *
 *  Created on: Aug 31, 2024
 *      Author: IOT
 */

#ifndef INC_APPLICATION_H_
#define INC_APPLICATION_H_

void application_Init(void);
#ifdef __cplusplus
extern "C"
{
#endif

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif

#endif /* INC_APPLICATION_H_ */
