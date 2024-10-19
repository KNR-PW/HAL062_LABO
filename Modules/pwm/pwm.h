/*
 ******************************************************************************
 * @file           : pwm.h
 * @author         : A. Rybojad
 * @brief          : Functions to manual set PWM
 ******************************************************************************
 */

#ifndef PWM_PWM_H_
#define PWM_PWM_H_

extern TIM_HandleTypeDef htim2;

HAL_StatusTypeDef PWM_Init();

HAL_StatusTypeDef PWM_SetDutyCycle(uint16_t duty);


#endif //PWM_PWM_H_
