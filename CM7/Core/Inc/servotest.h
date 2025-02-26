/*
 * servotest.h
 *
 *  Created on: Feb 15, 2025
 *      Author: Huni
 */

#ifndef INC_SERVOTEST_H_
#define INC_SERVOTEST_H_

#include "main.h"

void Servo_Init(TIM_HandleTypeDef *htim);
void Servo_TestFixedPositions(TIM_HandleTypeDef *htim);


#endif /* INC_SERVOTEST_H_ */
