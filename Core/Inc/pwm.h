//
// Created by user on 29.06.26.
//

#ifndef PID_TEMPERATURE_PWM_H
#define PID_TEMPERATURE_PWM_H

#include "main.h"
#include "stm32f1xx_hal_tim.h"

// Servo - MG995 High Speed 360

// APB1
// PA0 - TIM2_CH1
// PA1 - TIM2_CH2 this
// PA2 - TIM2_CH3
// PA3 - TIM2_CH4


extern TIM_HandleTypeDef tim2_ch2;
extern TIM_OC_InitTypeDef tim_oc_2;

void pwm1_config();
TIM_HandleTypeDef* getPWM_HandleTypeDef();
uint32_t getPWM_Value();


#endif //PID_TEMPERATURE_PWM_H
