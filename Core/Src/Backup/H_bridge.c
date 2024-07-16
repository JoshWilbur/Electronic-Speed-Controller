// This file contains functions which govern the behavior of the H bridge circuit
#include "main.h"
// Function prototypes
void HBridge_State(int input, int Backward_LB, int Backward_UB, int Forward_LB, int Forward_UB);

// This function will use input from the potentiometer to determine the H-Bridge circuit state
// For now, lets say the input ranges from 0 to 65535
void HBridge_State(int input, int Backward_LB, int Backward_UB, int Forward_LB, int Forward_UB){
	// Within the "counterclockwise/backward" rotation region, switch transistors 1 and 4
	if(input >= Backward_LB && input <= Backward_UB){
		TIM3->CCR1 = 20000-input;
		TIM3->CCR2 = 0;
		TIM3->CCR3 = 0;
		TIM3->CCR4 = 20000-input;
	}

	// Within the "clockwise/forward" rotation region, switch transistors 2 and 3
	if(input >= Forward_LB && input <= Forward_UB){
		TIM3->CCR1 = 0;
		TIM3->CCR2 = input-20000;
		TIM3->CCR3 = input-20000;
		TIM3->CCR4 = 0;
	}
}
