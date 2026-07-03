//
// Created by user on 01.07.26.
//

#include "adc1.h"

ADC_HandleTypeDef adc1_config = {0};
ADC_ChannelConfTypeDef adc1_channel_conf = {0};
volatile uint16_t adc_read_val;
volatile uint16_t adc_read_status = 0;

void ADC1_Config(void) {
    adc1_config.Instance = ADC1;
    adc1_config.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    adc1_config.Init.ScanConvMode = ADC_SCAN_DISABLE;
    adc1_config.Init.NbrOfConversion = 1;
    adc1_config.Init.ContinuousConvMode = DISABLE;
    adc1_config.Init.DiscontinuousConvMode = DISABLE;
    adc1_config.Init.ExternalTrigConv = ADC_SOFTWARE_START;

   if ( HAL_ADC_Init(&adc1_config) != HAL_OK )
       Error_Handler();

    adc1_channel_conf.Channel = ADC_CHANNEL_0;
    adc1_channel_conf.Rank = ADC_REGULAR_RANK_1;
    adc1_channel_conf.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;
    if ( HAL_ADC_ConfigChannel(&adc1_config, &adc1_channel_conf) != HAL_OK )
        Error_Handler();

    // TODO priotiry
    HAL_NVIC_SetPriority(ADC1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC1_IRQn);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
    if (hadc->Instance == ADC1) {
        // TODO логіка для EOC ADC
        adc_read_val = HAL_ADC_GetValue(hadc);
        adc_read_status = 1;
    }
}