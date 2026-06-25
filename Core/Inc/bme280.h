//
// Created by user on 25.06.26.
//

#ifndef PID_TEMPERATURE_BME280_H
#define PID_TEMPERATURE_BME280_H

// ------------- Slave adrr -------------
#define BME280_VAL_SLAVE_ADRR (0x76)
#define BME280_VAL_SLAVE_ADRR_ALTERNATIVE (0x77)

// -------------- Register Map -----------------
#define BME280_REG_ID_RO (0xD0)
#define BME280_REG_RESET_WR (0xE0)
// Вологість, перед тим треба записати у регістр ctrl_meas
// Контролює надмірну вибірку даних про вологість
// TODO Тут використовуються лише біти 2 1 0 всі інші reserved
// Ці біти налаштовують oversampling
#define BME280_REG_CTRL_HUM_RW (0xF2)
// Зберігає статус датчика
// bit 3 - Автоматично встановлюється на «1» кожного разу, коли виконується перетворення, і повертається на «0», коли результати передаються в регістри даних.
// bit 0 - Автоматично встановлюється на «1», коли дані NVM копіюються в регістри зображень, і повертається на «0», коли копіювання завершено. Дані копіюються під час скидання та перед кожним перетворенням.
#define BME280_REG_STATUS_RO (0xF3)
// Регістр для налаштування збору даних
#define BME280_REG_CTRL_MEAS_RW (0xF4)
// Регістр «config» встановлює швидкість, параметри фільтра та інтерфейсу пристрою.
#define BME280_REG_CONFIG_RW (0xF5)

// регістри тиску
#define BME280_REG_PRESS_MSB_RO (0xF7)
#define BME280_REG_PRESS_LSB_RO (0xF8)
#define BME280_REG_PRESS_XLSB_RO (0xF9)

// Регістри температури
#define BME280_REG_TEMP_MSB_RO (0xFA)
#define BME280_REG_TEMP_LSB_RO (0xFB)
#define BME280_REG_TEMP_XLSB_RO (0xFC)

// Регістри вологості
#define BME280_REG_HUM_MSB_RO (0xFD)
#define BME280_REG_HUM_LSB_RO (0xFE)

// ------------- Register value ------------
#define BME280_VAL_SOFT_RESET (0xB6)


// TODO додати зсуви
// -------------- CTRL ----------------
enum bme280_ctrl_meas_mode {
    SLEEP_MODE = 0x0,
    FORCED_MODE = 0x1,
    NORMAL_MODE = 0x3,
};

enum bme280_ctrl_meas_osrs_p {
    OSRS_P_SKIPPED = (0x0 << 2),
    OSRS_P_OVERSAMPLING_1 = (0x1 << 2),
    OSRS_P_OVERSAMPLING_2 = (0x2 << 2),
    OSRS_P_OVERSAMPLING_4 = (0x3 << 2),
    OSRS_P_OVERSAMPLING_8 = (0x4 << 2),
    OSRS_P_OVERSAMPLING_16 = (0x5 << 2),
};

enum bme280_ctrl_meas_osrs_t {
    OSRS_T_SKIPPED = (0x0 << 5),
    OSRS_T_OVERSAMPLING_1 = (0x1 << 5),
    OSRS_T_OVERSAMPLING_2 = (0x2 << 5),
    OSRS_T_OVERSAMPLING_4 = (0x3 << 5),
    OSRS_T_OVERSAMPLING_8 = (0x4 << 5),
    OSRS_T_OVERSAMPLING_16 = (0x5 << 5),
};

// ---------- CONFIG ----------------
enum bme280_config_t_sb {
    T_SB_CONFIG_0_5 = (0x0 << 5),
    T_SB_CONFIG_62_5 = (0x1 << 5),
    T_SB_CONFIG_125 = (0x2 << 5),
    T_SB_CONFIG_250 = (0x3 << 5),
    T_SB_CONFIG_500 = (0x4 << 5),
    T_SB_CONFIG_1000 = (0x5 << 5),
    T_SB_CONFIG_10 = (0x6 << 5),
    T_SB_CONFIG_20 = (0x7 << 5),
};

enum bme280_config_filter {
    FILTER_CONFIG_OFF = (0x00 << 2),
    FILTER_CONFIG_COEFFICIENT_2 = (0x1 << 2),
    FILTER_CONFIG_COEFFICIENT_4 = (0x2 << 2),
    FILTER_CONFIG_COEFFICIENT_8 = (0x3 << 2),
    FILTER_CONFIG_COEFFICIENT_16 = (0x4 << 2),
};

enum bme280_config_spi3w_enable {
    SPI3W_ENABLE = 0x1,
};

#endif //PID_TEMPERATURE_BME280_H
