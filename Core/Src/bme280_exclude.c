//
// Created by user on 07.07.26.
//

#include "bme280_exclude.h"

    static uint8_t id_bme = 0;

HAL_StatusTypeDef BME280_Init() {
    if ( BME280_SoftReset() != HAL_OK )
        return HAL_ERROR;

    HAL_Delay(3);

   if ( BME280_GetChipID(&id_bme) != HAL_OK )
       return HAL_ERROR;

    if (id_bme == BME280_VAL_CHIP_ID)
        return HAL_OK;
    else
        return HAL_ERROR;
}

HAL_StatusTypeDef BME280_SoftReset() {
    uint8_t softReset = BME280_VAL_SOFT_RESET;
    if ( HAL_I2C_Mem_Write(&i2c_handle,
        BME280_VAL_SLAVE_ADRR, BME280_REG_RESET_WR,
        I2C_MEMADD_SIZE_8BIT, &softReset, 1, 100) != HAL_OK)
        Error_Handler();
    else
        return HAL_OK;
    return HAL_TIMEOUT;
}

HAL_StatusTypeDef BME280_GetChipID( uint8_t *pRecBuffer) {
    if ( HAL_I2C_Mem_Read(&i2c_handle,
        BME280_VAL_SLAVE_ADRR, BME280_REG_ID_RO,
        I2C_MEMADD_SIZE_8BIT, pRecBuffer, 1, 100) != HAL_OK )
        Error_Handler();
    else
        return HAL_OK;

    return HAL_TIMEOUT;
}

uint8_t BME280_GetID() {
    return id_bme;
}
