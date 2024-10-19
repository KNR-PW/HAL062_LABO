/**
 ******************************************************************************
 * @file           : error_handler.c
 * @author         : A. Rybojad
 * @brief          : Error handling file
 ******************************************************************************
 */

#include "error_handler/error_handler.h"

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
