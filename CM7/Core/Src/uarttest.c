/*
 * uarttest.c
 *
 *  Created on: Feb 18, 2025
 *      Author: Huni
 */

#include "uarttest.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

extern UART_HandleTypeDef huart5;

static uint8_t rxData;

void UART_Test_Init(void) {
    HAL_UART_Receive_IT(&huart5, &rxData, 1);
}

void UART_Send_String(const char *str) {
    HAL_UART_Transmit(&huart5, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}

void UART_Send_Data(const char *format, ...) {
    char buffer[100];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    HAL_UART_Transmit(&huart5, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
}

void Send_IMU_Data(int16_t *gyro, int16_t *mag, int16_t *accel) {
    UART_Send_Data("\rIMU: G[%d, %d, %d] A[%d, %d, %d] M[%d, %d, %d]   ",
        gyro[0], gyro[1], gyro[2],
        accel[0], accel[1], accel[2],
        mag[0], mag[1], mag[2]);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == UART5) {
        HAL_UART_Transmit(&huart5, &rxData, 1, HAL_MAX_DELAY);
        HAL_UART_Receive_IT(&huart5, &rxData, 1);
    }
}


