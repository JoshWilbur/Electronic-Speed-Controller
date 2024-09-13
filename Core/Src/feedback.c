// This file contains code to input and interpret the RPM value supplied by the optical encoder
#include "main.h"

// This link along with ECE271 notes was used to help with setup:
// https://deepbluembedded.com/stm32-external-interrupt-example-lab/

// Global variables. Some are volatile to prevent compiler optimization, need newest value at all times
volatile int num_pulses = 0;
volatile int rpm = 0; // RPM calculated by triggering an interrupt every second to count+process pulses
int disc_openings = 6;

// EXTI callback for pulse counting
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if (GPIO_Pin == GPIO_PIN_1){ // Confirm PC1 is the interrupt pin
    	num_pulses++;
    }
}

// TIM2 callback for triggering interrupt to calculate pulses
void HAL_TIM2_Period_Callback(TIM_HandleTypeDef *htim){
	if (htim->Instance == TIM2){ // Confirm htim2 is the interrupt clock
		rpm = (num_pulses / disc_openings) / 60;
		num_pulses = 0; // Clear pulses
	}
}

// Basic function to get RPM
int get_rpm(){
	return rpm;
}
