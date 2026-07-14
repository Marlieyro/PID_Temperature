//
// Created by user on 01.07.26.
//

#ifndef PID_TEMPERATURE_ADC1_H
#define PID_TEMPERATURE_ADC1_H

#include "main.h"
#include "stm32f1xx_hal.h"

#define ADC1_MAX_RAW_VAL (4096)
#define ADC1_MIN_TEMP_POSSIBLE (1500)
#define ADC1_MAX_TEMP_POSSIBLE (3000)

volatile extern uint8_t irq_flag;
void ADC1_Config();
uint32_t getADC1_Desire_Temp();
ADC_HandleTypeDef* getADC1_HandleTypeDef();
uint32_t ADC1_Calculate_Desire_Temp(uint32_t raw_value);

#endif //PID_TEMPERATURE_ADC1_H
