// Header file for the adc_functions.c program
#ifndef INC_ADC_FUNCTIONS_H_
#define INC_ADC_FUNCTIONS_H_

// Global buffer to store DMA output
extern volatile uint32_t adc_output[2];
extern int DMA_flag;

// Function prototypes
int user_input(int input_adc);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

#endif /* INC_ADC_FUNCTIONS_H_ */
