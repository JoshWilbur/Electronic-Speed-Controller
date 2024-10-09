#ifndef INTERRUPT_CALLBACKS_H
#define INTERRUPT_CALLBACKS_H

#include "main.h"

// Function prototypes
int hall_input(void);
void hall_rpm(int p_num);
float closed_loop_feedback(int exp_rpm, int act_rpm);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

// Global variables. Some are volatile to prevent compiler optimization, need newest value at all times
extern volatile int real_rpm;
extern volatile int pulse_num;
extern volatile int rpm_flag;

#endif // INTERRUPT_CALLBACKS_H
