#include "main.h"

/* TO DO:
 * Generate PWM
 * User input program (read pot. with ADC)
 * Hall Effect sensor feedback
 */

EXTI_HandleTypeDef htim2;

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  while(1){
	  HBridge_Forward();
	  HAL_Delay(1000);
	  HBridge_Backward();
  }
}

// Toggle switches "1" and "4" to allow forward motor rotation
void HBridge_Forward(void){
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8); // SW1
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_5); // SW4
}

// Toggle switches "2" and "3" to allow backward motor rotation
void HBridge_Backward(void){
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9); // SW2
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6); // SW3
}

// Program to cycle through GPIO pins
void LED_test(int delay){
	while (1){
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8); // SW1
		HAL_Delay(delay);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9); // SW2
		HAL_Delay(delay);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6); // SW3
		HAL_Delay(delay);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_5); // SW4
		HAL_Delay(delay);
	}
}
