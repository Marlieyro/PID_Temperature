//
// Created by user on 01.07.26.
//

#include "adc1.h"

ADC_HandleTypeDef adc1_config = {0};
ADC_ChannelConfTypeDef adc1_channel_conf = {0};

volatile static uint32_t desire_tem_from_adc;
volatile uint8_t irq_flag = 0;

void ADC1_Config(void) {
    adc1_config.Instance = ADC1;
    adc1_config.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    adc1_config.Init.ScanConvMode = ADC_SCAN_DISABLE;
    adc1_config.Init.NbrOfConversion = 1;
    adc1_config.Init.ContinuousConvMode = DISABLE;
    adc1_config.Init.DiscontinuousConvMode = DISABLE;
    // Включаємо ADC раз на 100мс через TIMER event
    adc1_config.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_TRGO;

   if ( HAL_ADC_Init(&adc1_config) != HAL_OK )
       Error_Handler();

    adc1_channel_conf.Channel = ADC_CHANNEL_0;
    adc1_channel_conf.Rank = ADC_REGULAR_RANK_1;
    adc1_channel_conf.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;
    if ( HAL_ADC_ConfigChannel(&adc1_config, &adc1_channel_conf) != HAL_OK )
        Error_Handler();

    HAL_NVIC_SetPriority(ADC1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC1_IRQn);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
    if (hadc->Instance == ADC1) {
        desire_tem_from_adc = ADC1_Calculate_Desire_Temp(HAL_ADC_GetValue(hadc));
        irq_flag = 1;
        // Маємо знову викликати, щоб ADC статус був BUSY
        HAL_ADC_Start_IT(&adc1_config);
    }
}

uint32_t ADC1_Calculate_Desire_Temp(uint32_t raw_value) {

    int16_t temp_diff = ADC1_MAX_TEMP_POSSIBLE - ADC1_MIN_TEMP_POSSIBLE;

    desire_tem_from_adc = ADC1_MIN_TEMP_POSSIBLE + ((raw_value * temp_diff) / ADC1_MAX_RAW_VAL);
    return desire_tem_from_adc;
}
uint32_t getADC1_Desire_Temp() {
    irq_flag = 0;
    return desire_tem_from_adc;
}
ADC_HandleTypeDef* getADC1_HandleTypeDef() {
    return &adc1_config;
}


