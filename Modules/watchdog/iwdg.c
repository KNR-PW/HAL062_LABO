///**
// ******************************************************************************
// * @file           : iwdg.c
// * @author         : A. Rybojad
// * @brief          : Watchdog configuration file
// ******************************************************************************
// */
//
//
//#include "watchdog/iwdg.h"
//
//IWDG_HandleTypeDef hiwdg;
//
//void MX_IWDG_Init(void) // set timeout to 1 second
//{
//  hiwdg.Instance = IWDG;
//  hiwdg.Init.Prescaler = IWDG_PRESCALER_8;
//  hiwdg.Init.Reload = 4000-1;
//  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
//  {
//    Error_Handler();
//  }
//}
