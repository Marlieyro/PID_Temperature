//
// Created by user on 02.07.26.
//

#ifndef PID_TEMPERATURE_UART_H
#define PID_TEMPERATURE_UART_H

#include "stm32f1xx_hal_uart.h"

extern UART_HandleTypeDef huart1;
void UART1_Config(void);

#endif //PID_TEMPERATURE_UART_H
