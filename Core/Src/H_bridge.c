// This file contains functions which govern the behavior of the H-bridge circuit
#include "main.h"

// Function prototypes
void hbridge_state(int input, int d_flag);
void PWM_frequency(int freq);

// This function uses input from the potentiometer to determine the H-Bridge circuit state
// A direction flag, controlled via a switch, controls the direction of the motor
void hbridge_state(int input, int d_flag){
	int max_input = 382;

	// Conditional to determine H-Bridge state
	if (d_flag == -1){
		// Dead time if state is switching
		TIM3->CCR1 = 0;
		TIM3->CCR2 = 0;
		TIM3->CCR3 = 0;
		TIM3->CCR4 = 0;
	}else if(d_flag == 0 && input < max_input){
		// Backward motion, Q1/Q4 on
		TIM3->CCR1 = input;
		TIM3->CCR2 = 0;
		TIM3->CCR3 = 0;
		TIM3->CCR4 = input;
	}else if(d_flag == 1 && input < max_input){
		// Forward motion, Q2/Q3 on
		TIM3->CCR1 = 0;
		TIM3->CCR2 = input;
		TIM3->CCR3 = input;
		TIM3->CCR4 = 0;
	}
}

// This function can modify the TIM3 PWM frequency (effective range: 100Hz to 30kHz) with ease
// See 9/16/24 notebook entry for more details
void PWM_frequency(int freq){
	if(freq >= 100 && freq <= 30000){
		TIM3->CR1 &= ~TIM_CR1_CEN; // Disable timer to allow updating
		int arr = 402;
		int psc = (72000000/((arr+1)*(freq))) - 1;
		TIM3->ARR = arr;
		TIM3->PSC = psc;
		TIM3->EGR |= TIM_EGR_UG; // Update TIM3 with new values
		TIM3->CR1 |= TIM_CR1_CEN; // Toggle timer back on
	}
}
