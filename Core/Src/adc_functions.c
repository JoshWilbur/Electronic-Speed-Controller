// This file contains functions which utilize the on-board ADC
// DMA was covered briefly in ECE 271+471, this link was referenced for help in setup
// https://embeddedthere.com/stm32-adc-tutorial-using-dma-with-hal-code-example/
#include "main.h"

// Function prototypes
int user_input(void);

volatile uint16_t adc_output[2]; // Global buffer to store DMA results

// This function initializes DMA and sets the output buffer to the one defined above
void ADC_DMA_Init(void) {
    HAL_ADC_Start_DMA(&hadc1, (uint16_t*)adc_output, 2);
}

// This function takes an input from the potentiometer connected to ADC1_CH1 (PC0)
int user_input(void){
	int input_adc = 0;
	HAL_ADC_Start(&hadc1); // Begin ADC conversion
 	HAL_ADC_PollForConversion(&hadc1, 100);
	input_adc = HAL_ADC_GetValue(&hadc1); // Obtain raw ADC output
	HAL_ADC_Stop(&hadc1); // End ADC conversion
	return input_adc * 0.095; // Return ADC value times a scaling factor, more details in notebook
}
