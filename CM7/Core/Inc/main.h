/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ADC_IN_Pin GPIO_PIN_11
#define ADC_IN_GPIO_Port GPIOF
#define GP1_Pin GPIO_PIN_8
#define GP1_GPIO_Port GPIOE
#define GP2_Pin GPIO_PIN_9
#define GP2_GPIO_Port GPIOE
#define GP3_Pin GPIO_PIN_10
#define GP3_GPIO_Port GPIOE
#define GP4_Pin GPIO_PIN_11
#define GP4_GPIO_Port GPIOE
#define GP5_Pin GPIO_PIN_12
#define GP5_GPIO_Port GPIOE
#define GP6_Pin GPIO_PIN_13
#define GP6_GPIO_Port GPIOE
#define GP7_Pin GPIO_PIN_14
#define GP7_GPIO_Port GPIOE
#define GP8_Pin GPIO_PIN_15
#define GP8_GPIO_Port GPIOE
#define MIC_EN_Pin GPIO_PIN_8
#define MIC_EN_GPIO_Port GPIOD
#define REDLED1_Pin GPIO_PIN_0
#define REDLED1_GPIO_Port GPIOK
#define REDLED2_Pin GPIO_PIN_1
#define REDLED2_GPIO_Port GPIOK
#define ORANGELED1_Pin GPIO_PIN_2
#define ORANGELED1_GPIO_Port GPIOK
#define ORANGELED2_Pin GPIO_PIN_2
#define ORANGELED2_GPIO_Port GPIOG
#define BLUELED1_Pin GPIO_PIN_3
#define BLUELED1_GPIO_Port GPIOG
#define BLUELED2_Pin GPIO_PIN_4
#define BLUELED2_GPIO_Port GPIOG
#define BUTTON1_Pin GPIO_PIN_7
#define BUTTON1_GPIO_Port GPIOG
#define BUTTON2_Pin GPIO_PIN_8
#define BUTTON2_GPIO_Port GPIOG
#define SERVO_V_Pin GPIO_PIN_6
#define SERVO_V_GPIO_Port GPIOC
#define SERVO_X_Pin GPIO_PIN_7
#define SERVO_X_GPIO_Port GPIOC
#define SERVO_Y_Pin GPIO_PIN_8
#define SERVO_Y_GPIO_Port GPIOC
#define SERVO_Z_Pin GPIO_PIN_9
#define SERVO_Z_GPIO_Port GPIOC
#define SDCARD_DETECT_Pin GPIO_PIN_15
#define SDCARD_DETECT_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
