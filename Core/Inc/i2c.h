//
// Created by user on 25.06.26.
//

#ifndef PID_TEMPERATURE_I2C_H
#define PID_TEMPERATURE_I2C_H

#include "main.h"
#include "stm32f1xx_hal.h"

// I2C2_SCL - PB10
// I2C2_SDA - PB11


void I2C_config(void);
I2C_HandleTypeDef* getI2C_Config();

#endif //PID_TEMPERATURE_I2C_H
