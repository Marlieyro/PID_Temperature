//
// Created by user on 10.07.26.
//

#ifndef PID_TEMPERATURE_PID_H
#define PID_TEMPERATURE_PID_H

#include "main.h"

typedef struct {
    int Kp;
    int Ki;
    int Kd;

    // Значення ШІМ курючого сигналу
    // 0 - не крутимся
    // 1000 - крутимся повільно
    // 2500 - крутимся в іншу сторону
    int outMin;
    int outMax;

    int integralSum;
    int prevError;
} PID_Controller;


void PID_Init(PID_Controller *pid, int32_t kp, int32_t ki, int32_t kd);
uint32_t PID_Compute(PID_Controller *pid, uint32_t setpoint, uint32_t input);

#endif //PID_TEMPERATURE_PID_H
