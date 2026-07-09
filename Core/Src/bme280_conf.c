//
// Created by user on 08.07.26.
//
#include "bme280_conf.h"

/** ALL CODE IS BLOCKING!!! **/

int8_t BME280_Fetch_Sensor_Data() {
  //    BME280_PRESS
  //*     1       | BME280_PRESS
 // *     2       | BME280_TEMP
 // *     4       | BME280_HUM
 // *     7       | BME280_ALL
 return bme280_get_sensor_data(BME280_TEMP, &sensor_data, &bme280_conf_dev);
}

struct bme280_data* BME280_Fetch_and_Get_Data() {
    if ( BME280_Fetch_Sensor_Data() == BME280_OK )
        return &sensor_data;

    else return NULL;
}

// Only for Temperature
int8_t BME280_Init_Config() {
    //Init sensor
    int8_t status = bme280_init(&bme280_conf_dev);

    // Set Sensor Setting
    if ( status == BME280_OK )
        status = bme280_set_sensor_settings(BME280_SEL_OSR_TEMP | BME280_SEL_STANDBY,
            &settings, &bme280_conf_dev);
    else
        return status;

    // Set sensor mode
    if ( status == BME280_OK )
        status = bme280_set_sensor_mode(BME280_POWERMODE_NORMAL, &bme280_conf_dev);
    else
        return status;
    return status;
}

// Blocking Code
BME280_INTF_RET_TYPE BME280_Read(uint8_t bme_reg_addr, uint8_t *store_buff, uint32_t len_to_read, void *intf_ptr_i2c_s) {
    I2C_HandleTypeDef *i2c_handle = (I2C_HandleTypeDef*)intf_ptr_i2c_s;
    if ( HAL_I2C_Mem_Read(i2c_handle, (BME280_I2C_ADDR_PRIM << 1), bme_reg_addr, I2C_MEMADD_SIZE_8BIT, store_buff, len_to_read,100) != HAL_OK )
        return HAL_ERROR;

    return HAL_OK;
}

// Blocking Code
BME280_INTF_RET_TYPE BME280_Write(uint8_t bme_reg_addr, const uint8_t *writing_buff, uint32_t len_to_write, void *intf_ptr_i2c_s) {
    I2C_HandleTypeDef *i2c_handle = (I2C_HandleTypeDef*)intf_ptr_i2c_s;
    if ( HAL_I2C_Mem_Write(i2c_handle, (BME280_I2C_ADDR_PRIM << 1), bme_reg_addr, I2C_MEMADD_SIZE_8BIT, writing_buff, len_to_write,100) != HAL_OK )
        return HAL_ERROR;

    return HAL_OK;
}

void BME280_Delay(uint32_t periodo, void *intf_ptr) {
    HAL_Delay((periodo / 1000) + 1);
}

struct bme280_dev* get_ptr_BME280_Dev_Struct() {
    return &bme280_conf_dev;
}

struct bme280_settings* get_ptr_BME280_Settings_Struct() {
    return &settings;
};

struct bme280_data* get_ptr_BME280_Data_Struct() {
    return &sensor_data;
}


