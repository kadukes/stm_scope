/**
  ******************************************************************************
  * @file           : pwm_dac.c
  * @brief          : PWM-based DAC implementation
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

#include "pwm_dac.h"
#include "stm32f4xx_hal.h"

/* Private variables */
static TIM_HandleTypeDef htim4;

/* Private function prototypes */
static void pwm_gpio_init(void);
static void pwm_timer_init(void);

/**
  * @brief  Initialize PWM DAC on PD13
  * @retval None
  */
void pwm_dac_init(void)
{
  /* Initialize GPIO and Timer */
  pwm_gpio_init();
  pwm_timer_init();
  
  /* Start PWM generation */
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
}

/**
  * @brief  Write PWM value (0-255 maps to 0-100% duty cycle)
  * @param  value: 8-bit value (0-255)
  * @retval None
  */
void pwm_write(uint8_t value)
{
  /* Convert 8-bit value to timer compare value
   * Timer period is 255, so direct mapping works */
  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, value);
}

/**
  * @brief  Initialize GPIO for PWM output on PD13
  * @retval None
  */
static void pwm_gpio_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  /* Enable GPIOD clock */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  
  /* Configure PD13 as alternate function for TIM4_CH2 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

/**
  * @brief  Initialize Timer 4 for PWM generation
  * @retval None
  */
static void pwm_timer_init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  
  /* Enable TIM4 clock */
  __HAL_RCC_TIM4_CLK_ENABLE();
  
  /* Configure Timer 4 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 655;  /* Prescaler for ~1kHz PWM frequency */
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 255;     /* 8-bit resolution (0-255) */
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
  
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
  
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
  
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
  
  /* Configure PWM channel 2 (PD13) */
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;         /* Initial duty cycle = 0% */
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    /* Configuration Error */
    while(1);
  }
}
