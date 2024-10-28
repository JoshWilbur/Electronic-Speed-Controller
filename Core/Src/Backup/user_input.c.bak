// This file contains functions which take user input via an ADC and switch
// This link was referenced for help in setup
// https://deepbluembedded.com/stm32-adc-read-example-dma-interrupt-polling/
#include "main.h"

// Function prototypes
int user_input(void);
int input_to_rpm(int u_input);

volatile int dir_flag = 1; // Start in FWD direction by default

// This function takes an input from the potentiometer connected to ADC1_CH5 (PA0)
int user_input(void){
	int adc_pot = 0;
	HAL_ADC_Start(&hadc1); // Begin ADC conversion
 	HAL_ADC_PollForConversion(&hadc1, 100);
 	adc_pot = HAL_ADC_GetValue(&hadc1); // Obtain raw ADC output
	HAL_ADC_Stop(&hadc1); // End ADC conversion
	adc_pot *= 0.099; // ADC value times a scaling factor, more details in notebook
	return adc_pot; // Return scaled ADC value
}

// Function to perform linear interpolation on input to find RPM (see 10/17 notes)
int input_to_rpm(int u_input){
	// Constants to hold min/max motor RPM (from spec) and inputs
	const int min_rpm = 60;
	const int max_rpm = 200;
	const int min_input = 0;
	const int max_input = 400;

	// Translate input to RPM
	int expected_rpm = min_rpm + ((u_input - min_input) / (max_input - min_input)) * (max_rpm - min_rpm);
	return expected_rpm;
}

// GPIO EXTI callback handler for direction switching
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if(GPIO_Pin == GPIO_PIN_2){ // Check if PC2 is the interrupt pin
    	dir_flag = !dir_flag; // Toggle dir_flag between BWD and FWD (0/1)
    }
}


