// This file contains functions which govern the behavior of the H bridge circuit
#include "main.h"

// Function prototypes
void hbridge_state(int input, int Backward_LB, int Backward_UB, int Forward_LB, int Forward_UB);
int user_input(void);
void PWM_frequency(int freq);


// This function uses input from the potentiometer to determine the H-Bridge circuit state
// The input ranges from 0 to 2850
void hbridge_state(int input, int Backward_LB, int Backward_UB, int Forward_LB, int Forward_UB){
	// Within the "counterclockwise/backward" rotation region, switch transistors 1 and 4 on
	if(input >= Backward_LB && input <= Backward_UB){
		TIM3->CCR1 = Backward_UB - input;
		TIM3->CCR2 = 0;
		TIM3->CCR3 = 0;
		TIM3->CCR4 = Backward_UB - input;
	}

	// Within the "clockwise/forward" rotation region, switch transistors 2 and 3 on
	if(input >= Forward_LB && input <= Forward_UB){
		TIM3->CCR1 = 0;
		TIM3->CCR2 = input - Forward_LB;
		TIM3->CCR3 = input - Forward_LB;
		TIM3->CCR4 = 0;
	}
}

// This function takes an input from the potentiometer connected to ADC1_CH1
int user_input(void){
	int input_adc = 0;
	HAL_ADC_Start(&hadc1); // Begin ADC conversion
 	HAL_ADC_PollForConversion(&hadc1, 100);
	input_adc = HAL_ADC_GetValue(&hadc1); // Obtain raw ADC output
	HAL_ADC_Stop(&hadc1); // End ADC conversion
	return input_adc * 0.71; // Return ADC value times a scaling factor, more details in notebook
}

// This function can modify the TIM2 PWM frequency (range: 100Hz to 50kHz) with ease
// See 9/16/24 notebook entry for more details
void PWM_frequency(int freq){
	if(freq >= 100 && freq <= 50000){
		int psc = 0;
		int arr = 402;
		psc = (72000000/((arr+1)*(freq))) - 1;
		TIM3->ARR = arr;
		TIM3->PSC = psc;
		TIM3->EGR |= TIM_EGR_UG; // Update TIM3 with new values
	}
}
