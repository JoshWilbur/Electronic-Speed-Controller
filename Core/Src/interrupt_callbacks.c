// This file contains all of the interrupt callback functions
#include "main.h"

// This link along with ECE271 notes was used to help with setup:
// https://deepbluembedded.com/stm32-external-interrupt-example-lab/

// Set global variables, more info in header file
volatile int num_pulses = 0;
volatile int rpm = 0;
volatile int dir_flag = 1;
int disc_openings = 1;

// GPIO EXTI callback handler
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	// Pulse counting
    if(GPIO_Pin == GPIO_PIN_1){ // Confirm PC1 is the interrupt pin
    	num_pulses++;
    }

    // Direction switching
    if(GPIO_Pin == GPIO_PIN_2){ // Confirm PC2 is the interrupt pin
    	dir_flag = ~dir_flag; // Toggle dir_flag between 0 and 1
    }
}

// TIM2 callback for triggering interrupt to calculate pulses
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){ // Confirm htim2 is the interrupt clock
		rpm = (num_pulses / disc_openings) * 60;
		num_pulses = 0; // Clear pulses
	}
}
