//
// Created by user on 25.06.26.
//

#include "main.h"
#include "i2c.h"

void i2c_config(void) {
    I2C_HandleTypeDef i2c_handle;
    i2c_handle.Instance = I2C2;
    i2c_handle.Init.ClockSpeed = 100000; // 100 000 hz standart mode
    // i2c_handle.Init.DutyCycle = I2C_DUTYCYCLE_2;
    i2c_handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    i2c_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    i2c_handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if ( HAL_I2C_Init(&i2c_handle) != HAL_OK )
        Error_Handler();
}

