/*
 * servotest.c
 *
 *  Created on: Feb 15, 2025
 *      Author: Huni
 */

#include "servotest.h"

void Servo_Init(TIM_HandleTypeDef *htim) {
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_4);
}

void Servo_TestFixedPositions(TIM_HandleTypeDef *htim) {

	__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, 500);
    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_2, 1500);
    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_3, 2000);
    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_4, 2500);

}

