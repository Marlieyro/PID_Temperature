//
// Created by user on 06.07.26.
//

#ifndef PID_TEMPERATURE_TIMER_H
#define PID_TEMPERATURE_TIMER_H

#include "main.h"
#include "stm32f1xx_hal.h"


extern TIM_HandleTypeDef htim3;
void TIMER3_Config();
TIM_HandleTypeDef* getTIMER3_HandleTypeDef();

#endif //PID_TEMPERATURE_TIMER_H
