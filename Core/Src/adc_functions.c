// This file contains functions which utilize the on-board ADC
// This link was referenced for help in setup
// https://deepbluembedded.com/stm32-adc-read-example-dma-interrupt-polling/
#include "main.h"

// Function prototypes
int user_input(void);
int hall_input(void);

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

// This function takes an input from the hall-effect sensor connected to ADC2_CH6 (PA1)
int hall_input(void){
	int adc_hall = 0;
	HAL_ADC_Start(&hadc2); // Begin ADC conversion
 	HAL_ADC_PollForConversion(&hadc2, 100);
 	adc_hall = HAL_ADC_GetValue(&hadc2); // Obtain raw ADC output
	HAL_ADC_Stop(&hadc2); // End ADC conversion
	return adc_hall;
}


