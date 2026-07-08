/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32f1xx_hal_msp.c
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{

  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_AFIO_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  /* System interrupt init*/

  /** NOJTAG: JTAG-DP Disabled and SW-DP Enabled
  */
  __HAL_AFIO_REMAP_SWJ_NOJTAG();

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}



void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c){
  GPIO_InitTypeDef GPIO_Initure = {0};
  GPIO_Initure.Pin = GPIO_PIN_10 | GPIO_PIN_11; // SDA = 11, SCL = 10
  GPIO_Initure.Mode = GPIO_MODE_AF_OD;
  GPIO_Initure.Pull = GPIO_PULLUP;
  // TODO не high швидкість
  GPIO_Initure.Speed = GPIO_SPEED_HIGH;

  HAL_GPIO_Init(GPIOB, &GPIO_Initure);

  // TODO change priority
  HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);

  HAL_NVIC_SetPriority(I2C1_ER_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c){
  if (hi2c->Instance == I2C1) {
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10 | GPIO_PIN_11);
    HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
    HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
  }
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef GPIO_Initure = {0};
  if (htim->Instance == TIM2) {
    GPIO_Initure.Pin = GPIO_PIN_1;
    GPIO_Initure.Mode = GPIO_MODE_AF_PP;
    GPIO_Initure.Pull = GPIO_NOPULL;
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);
  }
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim){
  if (htim->Instance == TIM2) {
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1);
  }

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  GPIO_InitTypeDef GPIO_Initure = {0};
  if (hadc->Instance == ADC1) {
    GPIO_Initure.Pin = GPIO_PIN_0;
    GPIO_Initure.Mode = GPIO_MODE_ANALOG;
    GPIO_Initure.Pull = GPIO_NOPULL;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc) {
  if (hadc->Instance == ADC1) {
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);
  }
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart) {
  // PA10 - RX
  // PA9 - TX
  GPIO_InitTypeDef GPIO_Initure = {0};
  if (huart->Instance == USART1) {
    GPIO_Initure.Pin =  GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_Initure.Mode = GPIO_MODE_AF_PP;
    GPIO_Initure.Pull = GPIO_NOPULL;
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart) {
  if (huart->Instance == USART1) {
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);
  }
}
