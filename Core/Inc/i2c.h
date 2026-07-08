//
// Created by user on 25.06.26.
//

#ifndef PID_TEMPERATURE_I2C_H
#define PID_TEMPERATURE_I2C_H

#include "main.h"
#include "stm32f1xx_hal.h"

// I2C2_SCL - PB10
// I2C2_SDA - PB11
extern I2C_HandleTypeDef i2c_handle;

void i2c_config(void);

#endif //PID_TEMPERATURE_I2C_H
