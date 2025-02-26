/*
 * uarttest.h
 *
 *  Created on: Feb 18, 2025
 *      Author: Huni
 */

#ifndef INC_UARTTEST_H_
#define INC_UARTTEST_H_

#include "main.h"

void UART_Test_Init(void);
void UART_Send_String(const char *str);
void UART_Send_Data(const char *format, ...);
void Send_IMU_Data(int16_t *gyro, int16_t *mag, int16_t *accel);

#endif /* INC_UARTTEST_H_ */
