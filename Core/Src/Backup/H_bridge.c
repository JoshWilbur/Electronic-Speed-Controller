// This file contains functions which govern the behavior of the H bridge circuit
#include "main.h"

/* TO DO LIST:
 * Set PWM frequency to 20kHz
 * Confirm ADC1 is set up correctly (Ts, calibration,
 * Look into making the input an interrupt
 */

// Function prototypes
void HBridge_State(int input, int Backward_LB, int Backward_UB, int Forward_LB, int Forward_UB);
int User_Input(void);

// This function uses input from the potentiometer to determine the H-Bridge circuit state
// For now, lets say the input ranges from 0 to 65535
void HBridge_State(int input, int Backward_LB, int Backward_UB, int Forward_LB, int Forward_UB){
	// Within the "counterclockwise/backward" rotation region, switch transistors 1 and 4
 	int scale = 20000;
	if(input >= Backward_LB && input <= Backward_UB){
		TIM3->CCR1 = scale-input;
		TIM3->CCR2 = 0;
		TIM3->CCR3 = 0;
		TIM3->CCR4 = scale-input;
	}

	// Within the "clockwise/forward" rotation region, switch transistors 2 and 3
	if(input >= Forward_LB && input <= Forward_UB){
		TIM3->CCR1 = 0;
		TIM3->CCR2 = input-scale;
		TIM3->CCR3 = input-scale;
		TIM3->CCR4 = 0;
	}
}

// This function takes an input from the potentiometer connected to ADC1_CH1
int User_Input(void){
	int input_adc = 0;
	HAL_ADC_Start(&hadc1); // Begin ADC conversion
 	HAL_ADC_PollForConversion(&hadc1, 100);
	input_adc = HAL_ADC_GetValue(&hadc1); // Obtain raw ADC output
	HAL_ADC_Stop(&hadc1); // End ADC conversion
	return input_adc*16; // Return ADC value times a scaling factor, more details in notebook
}
