/**
 ******************************************************************************
 * @file           : main.c
 * @author         : A. Rybojad
 * @brief          : Main program body
 ******************************************************************************
 */


/* Includes ------------------------------------------------------------------- */

#include <stm32f4xx_hal.h>
#include <stdint.h>
#include "can/can.h"
#include "watchdog/iwdg.h"
#include "pwm/pwm.h"


/* Global variables ----------------------------------------------------------- */

/* Functions declaration ------------------------------------------------------ */

void SystemClock_Config(void);
void Error_Handler(void);

uint32_t duty;


/* Functions ------------------------------------------------------------------ */


/**
 ******************************************************************************
 * @brief          :	Main function initialize all required components
 ******************************************************************************
 */
int main(void) {

	HAL_Init(); 			//< Initialization of HAL Library
	SystemClock_Config(); 	//<Configuration of system clock
	SysTick_Config(80000); 	//<Setting SysTick Time

//	MX_IWDG_Init();

	CAN_Init(); 			//< CAN initialization
	if(PWM_Init() != HAL_OK){
		Error_Handler();
	}

	duty = 100;


	// Infinity loop
	  while (1)
	  {
		  PWM_SetDutyCycle(100);	// sets 10% (count is up to 1000)
		  HAL_Delay(500);
		  PWM_SetDutyCycle(1000);
		  HAL_Delay(500);
	    /* USER CODE END WHILE */

	    /* USER CODE BEGIN 3 */
	  }
}



/**
 ******************************************************************************
 * @brief          :	Function to configure system clock
 ******************************************************************************
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}
