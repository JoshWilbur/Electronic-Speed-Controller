// This file contains code to operate the feedback loop
// This link, along with ECE 271+314 notes, was referenced:
// https://deepbluembedded.com/stm32-external-interrupt-example-lab/

#include "main.h"

// Function prototypes
int hall_input(void);
int hall_rpm(int p_num);
int closed_loop_feedback(int exp_rpm, int act_rpm);

// Set global variable for RPM flag, more info in header file
volatile int rpm_flag = 0;

// This function takes an input from the hall-effect sensor connected to ADC2_CH6 (PA1)
// Effective output range: 0 to ~2400, 1150 is baseline
int hall_input(void){
	int adc_hall = 0;
	HAL_ADC_Start(&hadc2); // Begin ADC conversion
 	HAL_ADC_PollForConversion(&hadc2, 100);
 	adc_hall = HAL_ADC_GetValue(&hadc2); // Obtain raw ADC output
	HAL_ADC_Stop(&hadc2); // End ADC conversion
	return adc_hall; // Return raw hall effect sensor value
}

// This function calculates RPM based on the hall effect readings
int hall_rpm(int p_num){
	int magnet_num = 8.0;
	int rpm = (p_num / (magnet_num/2.0)) * 30.0;
	return rpm;
}

// This function operates the closed loop RPM feedback system
int closed_loop_feedback(int exp_rpm, int act_rpm){
	if(exp_rpm == 0 || act_rpm == 0) return 0; // Accounting for base case

	// variables to keep integral and last error states
	static float integral = 0.00;
	static int last_error = 0;

	signed int error = exp_rpm - act_rpm;
	float Kp = 0.02; // Prop. gain constant, higher value = harder correction
	float Ki = 0.001; // Integral Gain
	float Kd = 0.005; // Derivative Gain

	integral += error;
	float integral_term = Ki * integral;

	float derivative = error - last_error;
	float derivative_term = Kd * derivative;

	//int scale = 0;
	float scaled_error = Kp * error;

	float scale = scaled_error + integral_term + derivative_term;



	if(error != 0){
		scale += (int)scaled_error; // Set duty scale if error exists
	}else{
		return 0; // If error is 0, no feedback needed
	}

	if(scale > 120) return 120;
	if(scale < -120) return -120;

	last_error = error;

	return scale;
}

// TIM2 callback, triggers every 2 seconds
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){ // Confirm htim2 is the interrupt clock
		rpm_flag = 1; // Set flag to calculate RPM
	}
}
