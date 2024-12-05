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
	const float magnet_num = 8.0;
	const float gear_ratio = 4.5;
	float precise_rpm = (p_num / ((magnet_num) * gear_ratio)) * 20.0;
	int rpm = (int)precise_rpm;
	return rpm;
}

// This function operates the closed loop RPM feedback system
int closed_loop_feedback(int exp_rpm, int act_rpm){
	if(exp_rpm == 0 || act_rpm == 0) return 0; // Accounting for base case

	// variables to keep integral and last error states, static to persist
	static float integral = 0.00;
	static int last_error = 0;

	float Kp = 0.05; // Prop. gain constant, higher value = harder correction
	float Ki = 0.012; // Integral Gain
	float Kd = 0.025; // Derivative Gain

	signed int error = exp_rpm - act_rpm;
	float scaled_error = Kp * error;


	// Conditional to prevent integral windup
	// Good article on that here: https://control.com/technical-articles/intergral-windup-method-in-pid-control/
	if(integral > 100){
		integral = 100;
	}else if(integral < -100){
		integral = -100;
	}
	integral += error;
	float integral_term = Ki * integral;

	// Handle derivative term
	float derivative = error - last_error;
	float derivative_term = Kd * derivative;
	last_error = error;

	// Output scale to adjust PWM input to H-Bridge
	int scale = scaled_error + integral_term + derivative_term;
	if(scale > 120) return 120;
	if(scale < -120) return -120;
	return scale;
}

// TIM2 callback, triggers every 3 seconds
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){ // Confirm htim2 is the interrupt clock
		rpm_flag = 1; // Set flag to calculate RPM
	}
}
