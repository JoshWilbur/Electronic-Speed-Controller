// This file contains code to operate the feedback loop
// This link, along with ECE 271+314 notes, was referenced:
// https://deepbluembedded.com/stm32-external-interrupt-example-lab/

#include "main.h"

// Function prototypes
int hall_input(void);
void hall_rpm(int p_num);
float closed_loop_feedback(int exp_rpm, int act_rpm);

// Set global variables, more info in header file
volatile int real_rpm = 0;
volatile int pulse_num = 0;
volatile int rpm_flag = 0;

// This function takes an input from the hall-effect sensor connected to ADC2_CH6 (PA1)
// Effective output range: 0 to ~240, 115 is baseline
int hall_input(void){
	int adc_hall = 0;
	HAL_ADC_Start(&hadc2); // Begin ADC conversion
 	HAL_ADC_PollForConversion(&hadc2, 100);
 	adc_hall = HAL_ADC_GetValue(&hadc2); // Obtain raw ADC output
	HAL_ADC_Stop(&hadc2); // End ADC conversion
	return adc_hall; // Return raw hall effect sensor value
}

// This function calculates RPM based on the hall effect readings
void hall_rpm(int p_num){
	int magnet_num = 8;
	real_rpm = (p_num / (magnet_num/2)) * 60;
}

// This function operates the closed loop RPM feedback system
float closed_loop_feedback(int exp_rpm, int act_rpm){
	int error = exp_rpm - act_rpm;
	float duty_scale = 1;
	// TODO: flesh out more, look into proportional control
	return duty_scale; // Return scaling factor for duty
}

// ADC conversion complete callback to interpret pulse
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc){
    int hall_adc = HAL_ADC_GetValue(hadc); // Read ADC value

    // If the ADC value is near a peak or valley, count it as a "pulse"
    if (hall_adc > 200 || hall_adc < 40){
    	pulse_num++;
    }
}

// TIM2 callback, triggers every 1 second
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){ // Confirm htim2 is the interrupt clock
		rpm_flag = 1; // Set flag to calculate RPM
	}
}
