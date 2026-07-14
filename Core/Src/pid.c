//
// Created by user on 13.07.26.
//

#include "pid.h"

void PID_Init(PID_Controller *pid, int32_t kp, int32_t ki, int32_t kd) {
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;
    pid->integralSum = 0;
    pid->prevError = 0;
    pid->outMax = 2000;
    pid->outMin = 0;
}

uint32_t PID_Compute(PID_Controller *pid, uint32_t setpoint, uint32_t input) {
    // Error
    int32_t error = (int32_t)setpoint - (int32_t)input;

    // P = (Kp * error)
    int32_t P = (pid->Kp * error);

    // I = (Ki * Sum)
    pid->integralSum += error;
    int32_t I = (pid->Ki * pid->integralSum);

    // D = (Kd * (error - prevError))
    int32_t D = (pid->Kd * (error - pid->prevError));

    pid->prevError = error;

    // No FPU
    int32_t output = (P + I + D) / 1024;

    // На випадок якщо вийде за межі
    if (output > pid->outMax) output = pid->outMax;
    if (output < pid->outMin) output = pid->outMin;
    return (uint32_t)output;
}