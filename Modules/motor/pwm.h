/*
 ******************************************************************************
 * @file           : pwm.h
 * @author         : A. Rybojad
 * @brief          : Functions to manual set PWM
 ******************************************************************************
 */

#ifndef MOTOR_PWM_H_
#define MOTOR_PWM_H_

#include <stdint.h>
#include <stm32f4xx_hal.h>

extern TIM_HandleTypeDef htim2;

HAL_StatusTypeDef PWM_Init();

HAL_StatusTypeDef PWM_SetDutyCycle(uint32_t duty);


#endif //MOTOR_PWM_H_
