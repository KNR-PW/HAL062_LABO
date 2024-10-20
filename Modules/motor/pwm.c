/*
 ******************************************************************************
 * @file           : pwm.c
 * @author         : A. Rybojad
 * @brief          : Functions to manual set PWM
 ******************************************************************************
 */

#include <stm32f4xx_hal.h>
#include <motor/pwm.h>
#include "error_handler/error_handler.h"

TIM_HandleTypeDef htim2;
uint32_t AAR = 100-1;

HAL_StatusTypeDef PWM_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	__HAL_RCC_TIM2_CLK_ENABLE();

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 42-1;	// APB1 = 42Mhz
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = AAR; // reload every 1ms
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
	{
//		while(1);
//		Error_Handler();
		return HAL_ERROR;
	}

	/**TIM2 GPIO Configuration
	PA0-WKUP     ------> TIM2_CH1
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_0;
//	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;			// open-drain mode to set 5V max on output
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;			// temp
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
//		Error_Handler();
		return HAL_ERROR;
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
//	Error_Handler();
		return HAL_ERROR;
	}

	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);


	return HAL_OK;

}

HAL_StatusTypeDef PWM_SetDutyCycle(uint32_t duty) {
//	uint32_t duty = (uint32_t)((duty_percentage * AAR) / 100);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, duty);
	return HAL_OK;
}
