//
// Created by user on 09.07.26.
//

#ifndef PID_TEMPERATURE_BME280_CONF_H
#define PID_TEMPERATURE_BME280_CONF_H

#include "main.h"

extern I2C_HandleTypeDef i2c_handle;
/** ALL CODE IS BLOCKING!!! **/

int8_t BME280_Init_Config();
BME280_INTF_RET_TYPE BME280_Read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);
BME280_INTF_RET_TYPE BME280_Write(uint8_t bme_reg_addr, const uint8_t *writing_buff, uint32_t len_to_write, void *intf_ptr);
void BME280_Delay(uint32_t periodo, void *intf_ptr);
struct bme280_dev* get_ptr_BME280_Dev_Struct();
struct bme280_settings* get_ptr_BME280_Settings_Struct();
struct bme280_data* get_ptr_BME280_Data_Struct();
int8_t BME280_Fetch_Sensor_Data();
struct bme280_data* BME280_Fetch_and_Get_Data();

static struct bme280_data sensor_data = {0};

static struct bme280_dev bme280_conf_dev = {
    .chip_id = BME280_CHIP_ID,
    .intf = BME280_I2C_INTF,
    .intf_ptr = &i2c_handle,
    .read = BME280_Read,
    .write = BME280_Write,
    .delay_us = BME280_Delay,
    // Ignore this field
    // This f is calib f which was conf in factory, th lib on thy own set val
    //bme280.calib_data
};

static struct bme280_settings settings = {
    // Not need cause only temp is needed
    .osr_h = BME280_NO_OVERSAMPLING,
    // Not need cause only temp is needed
    .osr_p = BME280_NO_OVERSAMPLING,
    // No noise environment
    .osr_t = BME280_OVERSAMPLING_1X,
    // Not need, cause data spikes also informative
    .filter = 0,
    // Need in Normal mode
    // gap between mes is 1000ms
    .standby_time = BME280_STANDBY_TIME_1000_MS
};

#endif //PID_TEMPERATURE_BME280_CONF_H
