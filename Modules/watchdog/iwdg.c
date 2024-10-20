/**
 ******************************************************************************
 * @file           : iwdg.c
 * @author         : A. Rybojad
 * @brief          : Watchdog configuration file
 ******************************************************************************
 */


#include "watchdog/iwdg.h"
#include "error_handler/error_handler.h"

IWDG_HandleTypeDef hiwdg;

void MX_IWDG_Init(void) // set timeout to 10 second
{
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_8;
  hiwdg.Init.Reload = 40000-1;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
}
