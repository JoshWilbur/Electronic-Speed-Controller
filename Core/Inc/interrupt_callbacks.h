#ifndef INTERRUPT_CALLBACKS_H
#define INTERRUPT_CALLBACKS_H

#include "main.h"

// Global variables. Some are volatile to prevent compiler optimization, need newest value at all times
extern volatile int num_pulses; // pulse counting variable
extern volatile int rpm;
extern volatile int dir_flag; // motor direction flag
extern int disc_openings; // number of openings in measurement disk

// Function prototypes
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif // INTERRUPT_CALLBACKS_H
