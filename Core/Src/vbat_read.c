// Authored by Amir
/* --------------------NOTE--------------------
	This code hasn't been implemented into the main function. This is due to time constraints and the minor role it would play

   --------------------------------------------*/
#include "adc_reader.h"
#include "main.h"

uint32_t adc_value = 0;   // Initialize global variable for ADC value
float v_bat = 0.0f; // Initialize global variable for battery voltage


extern ADC_HandleTypeDef hadc1;  // Use the ADC handle defined in main.c

// Function to read raw ADC value
uint32_t Read_ADC_Value(void) {
    HAL_ADC_Start(&hadc1);  // Start the ADC conversion
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);  // Wait until conversion completes
    uint32_t adcValue = HAL_ADC_GetValue(&hadc1);  // Get ADC value
    HAL_ADC_Stop(&hadc1);  // Stop the ADC
    return adcValue;
}

// Function to convert ADC value to voltage (with scaling factor if needed)
float Scale_ADC_to_Voltage(uint32_t adc_value) {
    float battery_voltage = (adc_value / 4095.0) * 42;  // Convert to voltage
    return battery_voltage;  // Apply additional scaling if needed
}
// Using pin PC0
/*
GPIO_InitStruct.Pin = B1_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

Configure GPIO pin : LD2_Pin
GPIO_InitStruct.Pin = LD2_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);




///////////Main code////////////////
   while (1)
  {
	  adc_value = Read_ADC_Value();          // Read ADC
	  v_bat = Scale_ADC_to_Voltage(adc_value);  // Convert to voltage
	  HAL_Delay(100);  // Delay between reads
  }
*/
