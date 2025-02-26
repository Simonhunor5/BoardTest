/*
 * ledsbutton.c
 *
 *  Created on: Feb 6, 2025
 *      Author: Huni
 */

#include "ledsbutton.h"
#include "gpio.h"

void Process_LEDs_Buttons(void){

    if(HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin) == GPIO_PIN_RESET)
    {
        HAL_GPIO_WritePin(REDLED2_GPIO_Port, REDLED2_Pin, GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(REDLED1_GPIO_Port, REDLED1_Pin, GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(ORANGELED1_GPIO_Port, ORANGELED1_Pin, GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(ORANGELED2_GPIO_Port, ORANGELED2_Pin, GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(BLUELED1_GPIO_Port, BLUELED1_Pin, GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(BLUELED2_GPIO_Port, BLUELED2_Pin, GPIO_PIN_SET);
    }


    if(HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin) == GPIO_PIN_RESET)
    {
        HAL_GPIO_WritePin(REDLED2_GPIO_Port, REDLED2_Pin, GPIO_PIN_RESET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(REDLED1_GPIO_Port, REDLED1_Pin, GPIO_PIN_RESET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(ORANGELED1_GPIO_Port, ORANGELED1_Pin, GPIO_PIN_RESET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(ORANGELED2_GPIO_Port, ORANGELED2_Pin, GPIO_PIN_RESET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(BLUELED1_GPIO_Port, BLUELED1_Pin, GPIO_PIN_RESET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(BLUELED2_GPIO_Port, BLUELED2_Pin, GPIO_PIN_RESET);
    }
}


