//
// Created by user on 01.07.26.
//

#ifndef PID_TEMPERATURE_ADC1_H
#define PID_TEMPERATURE_ADC1_H

#include "main.h"
#include "stm32f1xx_hal.h"

extern ADC_HandleTypeDef adc1_config;
extern volatile uint16_t adc_read_val;
extern volatile uint16_t adc_read_status;

#endif //PID_TEMPERATURE_ADC1_H
