//
// Created by user on 29.06.26.
//

#include "pwm.h"


TIM_HandleTypeDef tim2_ch2;
TIM_OC_InitTypeDef tim_oc_2;

void pwm1_config() {
    tim2_ch2.Instance = TIM2;
    tim2_ch2.Channel = TIM_CHANNEL_2;
    // need 50 hz
    tim2_ch2.Init.Prescaler = 8-1;
    tim2_ch2.Init.Period = 20000 - 1; // medium cycle freq
    tim2_ch2.Init.CounterMode = TIM_COUNTERMODE_UP;
    tim2_ch2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    tim2_ch2.Init.AutoReloadPreload = DISABLE;
    if (HAL_TIM_PWM_Init(&tim2_ch2) != HAL_OK)
        Error_Handler();

    tim_oc_2.OCMode = TIM_OCMODE_PWM1;
    tim_oc_2.Pulse = 1500; // duty cycle
    tim_oc_2.OCPolarity = TIM_OCPOLARITY_HIGH;
    tim_oc_2.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&tim2_ch2, &tim_oc_2, TIM_CHANNEL_2) != HAL_OK)
        Error_Handler();

    // TODO prio
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);

    // TODO
    //HAL_TIM_PWM_Start_IT();
}

// TODO колбеки, треба понять який виокристовувати
//HAL_TIM_PeriodElapsedCallback(htim);
// HAL_TIM_OC_DelayElapsedCallback(htim);
// HAL_TIM_PWM_PulseFinishedCallback(htim);


