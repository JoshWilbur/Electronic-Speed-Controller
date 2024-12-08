#ifndef INTERRUPT_CALLBACKS_H
#define INTERRUPT_CALLBACKS_H

#include "main.h"

// Function prototypes
int hall_input(void);
int hall_rpm(int p_num);
int closed_loop_feedback(int exp_rpm, int act_rpm);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
extern volatile int rpm_flag;

#endif // INTERRUPT_CALLBACKS_H
