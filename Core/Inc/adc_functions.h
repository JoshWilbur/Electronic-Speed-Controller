// Header file for the adc_functions.c program
#ifndef INC_ADC_FUNCTIONS_H_
#define INC_ADC_FUNCTIONS_H_

// Global flag for DMA conversions
extern int DMA1_flag;
extern int DMA2_flag;

// Function prototypes
int user_input(int input_adc);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

#endif /* INC_ADC_FUNCTIONS_H_ */
