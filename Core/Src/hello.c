/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : hello.c
  * @brief          : Hello World task implementation
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "hello.h"
#include <stdio.h>
#include <string.h>
#include "fire_image.h"
#include "stm32f429i_discovery_lcd.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
osThreadId helloWorldTaskHandle;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void plot_animation(void) {
  uint16_t *const fb = (uint16_t *)LCD_FRAME_BUFFER;
  memcpy(fb, fire_image, sizeof(uint16_t) * FIRE_IMAGE_SIZE);
}

/* USER CODE END 0 */

/**
  * @brief  Initialize Hello World module
  * @retval None
  */
void hello_init(void)
{
  /* USER CODE BEGIN hello_init */
  
  /* Create Hello World task */
  osThreadDef(helloWorldTask, StartHelloWorldTask, osPriorityNormal, 0, 512);
  helloWorldTaskHandle = osThreadCreate(osThread(helloWorldTask), NULL);
  
  /* USER CODE END hello_init */
}

/* USER CODE BEGIN Header_StartHelloWorldTask */
/**
  * @brief  Function implementing the helloWorldTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartHelloWorldTask */
void StartHelloWorldTask(void const * argument)
{
  /* USER CODE BEGIN StartHelloWorldTask */
  uint32_t counter = 0;
  
  plot_animation();
  
  /* Infinite loop */
  for(;;)
  {
    printf("Hello World from STM32! Counter: %lu\r\n", counter++);
    osDelay(1000); /* Delay for 1 second */
  }
  /* USER CODE END StartHelloWorldTask */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */
