// This file contains functions which take user input via an ADC and switch
// This link was referenced for help in setup
// https://deepbluembedded.com/stm32-adc-read-example-dma-interrupt-polling/
#include "main.h"

// Function prototypes
int user_input(int current_val);
int input_to_rpm(int u_input);

volatile int dir_flag = -1; // Start in OFF state by default

// This function takes an input from the potentiometer connected to ADC1_CH5 (PA0)
int user_input(int current_val) {
    int adc_pot = 0;
    int scaled_pot = 0;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	adc_pot = HAL_ADC_GetValue(&hadc1); // Obtain raw ADC output
	HAL_ADC_Stop(&hadc1);
	scaled_pot = adc_pot * 0.074; // Scale ADC value, see 9/25 & 11/13 notes
	scaled_pot += 100;

	// Adjust current value based on input value
	if(scaled_pot > current_val){
		current_val++; // Using previous value to avoid sharp jumps
	}else if(scaled_pot < current_val){
		current_val--;
	}

	// Turn off MOSFETs if physical input is 0
	if(adc_pot == 0){
		current_val -= 2;
	}

	// Ensure input value stays within bounds
	if(current_val > 380) return 380;
	if(current_val < 0) return 0;
	return current_val;
}


// Function to perform linear interpolation on input to find RPM (see 10/17 notes)
int input_to_rpm(int u_input){
	// Constants to hold min/max motor RPM (from spec) and inputs
	const int min_rpm = 0;
	const int max_rpm = 3000;
	const int min_input = 150; // Lowest input that the motor spins at
	const int max_input = 380;
	int expected_rpm = 0;

	if(u_input < min_input) return 0;

	// Translate input to RPM
	expected_rpm = min_rpm + ((float)(u_input - min_input) / (max_input - min_input)) * (max_rpm - min_rpm);
	return expected_rpm;
}

// GPIO EXTI callback handler for direction switching
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if(GPIO_Pin == GPIO_PIN_2){ // Check if PC2 is the interrupt pin
    	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 1){
    		dir_flag = 1; // Clockwise motor rotation
    	}else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 0){
    		dir_flag = 0; // Counterclockwise motor rotation
    	}
    }
}


