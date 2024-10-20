/**
 ******************************************************************************

 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "motor/motor.h"
#include "motor/pwm.h"
#include "error_handler/error_handler.h"


/* Functions ------------------------------------------------------------------*/

/*
 * ***************************************************
 * @ details	:	Initialization of GPIO pins
 * ***************************************************
 */
void MainBoxMotor_Init(void) {
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  __HAL_RCC_GPIOA_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);



	  /* Configure GPIO pins : PA2 PA3 -  BROKEN  */
	  /* Configure GPIO pins : PA8 PA9 - motor rotation direction */
	  GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  if(PWM_Init() != HAL_OK){
	  		Error_Handler();
	  	}
}

void liftMainBox(uint8_t ifFast){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
	if(!ifFast)
		PWM_SetDutyCycle(80);
	else
		PWM_SetDutyCycle(100);
}

void lowerMainBox(uint8_t ifFast){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
	if(!ifFast)
		PWM_SetDutyCycle(80);
	else
		PWM_SetDutyCycle(100);
}

void stopMainBox(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
}
