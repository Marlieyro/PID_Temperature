/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

#include <stdint.h>
#include <stdio.h>
#include <string.h>

PID_Controller pid = {0};
char msg[64];
char eow[] = "\r\n";
volatile uint32_t pwm_val;
volatile uint32_t temperature;

int main(void) {

  /** Program SetUp **/
  Config_System_And_Periphery();
  PWM_Start();
  ADC_Start_IT();
  HAL_Delay(100);

  while (1) {
    // HAL_Delay(100);
    //snprintf(msg, sizeof(msg), "ADC is: %d%s", (int)getADC1_HandleTypeDef()->Instance->DR, eow);
    // HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 1000);

    /** Program LOOP **/
    HAL_Delay(200);
    System_Flow();
  }
}

void App_RCC_Configuration() {
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_ADC1_CLK_ENABLE();
  __HAL_RCC_USART1_CLK_ENABLE();
  __HAL_RCC_I2C2_CLK_ENABLE();
  __HAL_RCC_TIM3_CLK_ENABLE();
  __HAL_RCC_TIM2_CLK_ENABLE();

  // Div clock for adc 16 / 8 = 2Mhz
  __HAL_RCC_ADC_CONFIG(RCC_ADCPCLK2_DIV8);
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
    HAL_UART_Transmit(&huart1, (uint8_t*)"Error\r\n", strlen("Error\r\n"), 100);
  }

}

void Config_System_And_Periphery(){
  // Hal Init
  HAL_Init();

  // RCC Config
  SystemClock_Config();

  // Enable all clocks for periphery
  App_RCC_Configuration();

  // UART Config
  UART1_Config();

  // I2C Config
  I2C_config();

  // BME280 Config
  BME280_Init_Config();

  // TIM3 Config for ADC1
  TIMER3_Config();

  // ADC1 Config
  ADC1_Config();

  // PWM1 Config
  pwm1_config();

  // PID Config
  PID_Init(&pid, 2048, 5, 0);
}

void PWM_Start() {
  HAL_TIM_PWM_Start(getPWM_HandleTypeDef(), TIM_CHANNEL_2);
}

void ADC_Start_IT() {
  HAL_ADC_Start_IT(getADC1_HandleTypeDef());
}

void System_Flow() {
  temperature = BME280_Fetch_and_Get_Data()->temperature;

  // HIL CODE
  /** static int32_t virtual_temp = 2500;
  virtual_temp += (pwm_val / 50);
  if (virtual_temp > 2500) {
    virtual_temp -= ((virtual_temp - 2500) / 20);
  }
  temperature = virtual_temp;
  **/

  /** Main LOOP **/
  pwm_val = PID_Compute(&pid, getADC1_Desire_Temp(), temperature);
  __HAL_TIM_SET_COMPARE(getPWM_HandleTypeDef(), TIM_CHANNEL_2, pwm_val);
  snprintf(msg, sizeof(msg), "PWM is: %d Temp is: %d CCR is: %d ADC is: %d%s", (int)pwm_val, (int)temperature,(int)__HAL_TIM_GET_COMPARE(getPWM_HandleTypeDef(), TIM_CHANNEL_2), (int)getADC1_Desire_Temp(), eow);
  HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 1000);
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */



// 1. Конфіг системи
// 2. Запуск ШІМ
// 3. Запуск BME
// 4. Запуск PID


// State Machine
/**
 * Запустити вентилятор
 * Зібрати температуру
 * Зібрати значення регулювальника
 * Порахувати PWM
 * Запустити вентилятор
 * **/