/**
  ******************************************************************************
  * @file           : pwm_dac.h
  * @brief          : PWM-based DAC implementation header
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

#ifndef __PWM_DAC_H
#define __PWM_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

/* Function prototypes */
void pwm_dac_init(void);
void pwm_write(uint8_t value);

#ifdef __cplusplus
}
#endif

#endif /* __PWM_DAC_H */
