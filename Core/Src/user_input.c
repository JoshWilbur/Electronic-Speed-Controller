// This file contains functions which take user input via an ADC and switch
// This link was referenced for help in setup
// https://deepbluembedded.com/stm32-adc-read-example-dma-interrupt-polling/
#include "main.h"

#define MIN_INPUT 180 // Lowest input that the motor spins at
#define MAX_INPUT 217 // Maximum input to stay in spec

// Function prototypes
int user_input();
int update_input(int current_val, int prior_val, int feedback);
int input_to_rpm(int u_input);


volatile int dir_flag = -1; // Start in OFF state by default

// This function takes an input from the potentiometer connected to ADC1_CH5 (PA0)
int user_input(){
    int adc_pot = 0;
    int scaled_pot = 0;
    float INPUT_SCALE = ((MAX_INPUT-MIN_INPUT)/380.0) * 0.099; // See 9/25 & 11/22 notes
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	adc_pot = HAL_ADC_GetValue(&hadc1); // Obtain raw ADC output
	HAL_ADC_Stop(&hadc1);
	if(adc_pot == 0) return 0;
	scaled_pot = (adc_pot * INPUT_SCALE) + MIN_INPUT; // Scale ADC value
	if(scaled_pot > MAX_INPUT) return MAX_INPUT;
	return scaled_pot;
}

int update_input(int input, int prior_val, int feedback){
	input += feedback;

	// Adjust output value based on prior value to avoid sharp jumps
	if(prior_val < input){
		prior_val++;
	}else if(prior_val > input){
		prior_val--;
	}

	// Turn off MOSFETs if physical input is 0
	if(input == 0){
		prior_val -= 2;
	}

	// Ensure input value stays within bounds
	if(prior_val > MAX_INPUT+160) return MAX_INPUT+160;
	if(prior_val < 0) return 0;
	return prior_val;
}


// Function to perform linear interpolation on input to find RPM (see 10/17 notes)
int input_to_rpm(int u_input){
	// Constants to hold min/max motor RPM (from spec) and inputs
	const int min_rpm = 60;
	const int max_rpm = 200;
	const int min_input = MIN_INPUT;
	const int max_input = MAX_INPUT;
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


