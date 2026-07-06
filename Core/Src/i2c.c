//
// Created by user on 25.06.26.
//

#include "main.h"
#include "i2c.h"

I2C_HandleTypeDef i2c_handle;

void i2c_config(void) {
    i2c_handle.Instance = I2C1;
    i2c_handle.Init.ClockSpeed = 100000; // 100 000 hz standart mode
    // i2c_handle.Init.DutyCycle = I2C_DUTYCYCLE_2;
    i2c_handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    i2c_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    i2c_handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if ( HAL_I2C_Init(&i2c_handle) != HAL_OK )
        Error_Handler();
}

// TODO краще обрати MemTx/RxCallback

// Master Tx Transfer completed callback.
__weak void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    // Коли буфер empty то викликається цей callback
}

// Master Rx Transfer completed callback.
__weak void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    // Коли буфер empty для Recive
}
