//
// Created by user on 06.07.26.
//

#include "timer.h"

TIM_HandleTypeDef tim3 = {0};

void TIMER3_Config(void) {
    tim3.Instance = TIM3;
    tim3.Init.Prescaler = 15;
    tim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    tim3.Init.Period = 49999;
    tim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    tim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if (HAL_TIM_Base_Init(&tim3) != HAL_OK)
        Error_Handler();

    // TRGO output configuration
    // This feature can send signal directly to ADC1 witout touching the CPU
    // when timer update event happen
    TIM_MasterConfigTypeDef tim3_mstr = {0};
    tim3_mstr.MasterOutputTrigger = TIM_TRGO_UPDATE;
    tim3_mstr.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

    // Далі просто включаємо Start_IT і по перериванню таймера це буде працювати
    if (HAL_TIMEx_MasterConfigSynchronization(&tim3, &tim3_mstr) != HAL_OK)
        Error_Handler();
}
