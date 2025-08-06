/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define LED0_GPIO        GPIOB, LL_GPIO_PIN_5
#define LED0_Toggle      LL_GPIO_TogglePin(LED0_GPIO)
#define LED0_OFF         LL_GPIO_SetOutputPin(LED0_GPIO)
#define LED0_ON          LL_GPIO_ResetOutputPin(LED0_GPIO)

#define LED1_GPIO        GPIOE, LL_GPIO_PIN_5
#define LED1_Toggle      LL_GPIO_TogglePin(LED1_GPIO)
#define LED1_OFF         LL_GPIO_SetOutputPin(LED1_GPIO)
#define LED1_ON          LL_GPIO_ResetOutputPin(LED1_GPIO)

#define BEEP_GPIO        GPIOB, LL_GPIO_PIN_8
#define BEEP_Toggle      LL_GPIO_TogglePin(BEEP_GPIO)
#define BEEP_OFF         LL_GPIO_SetOutputPin(BEEP_GPIO)
#define BEEP_ON          LL_GPIO_ResetOutputPin(BEEP_GPIO)

#define KEY0_GPIO        GPIOE, LL_GPIO_PIN_4
#define KEY0             LL_GPIO_IsInputPinSet(KEY0_GPIO)
#define KEY0_OFF         0U
#define KEY0_ON          1U

#define KEY1_GPIO        GPIOE, LL_GPIO_PIN_3
#define KEY1             LL_GPIO_IsInputPinSet(KEY1_GPIO)
#define KEY1_OFF         0U
#define KEY1_ON          1U

#define KEY_UP_GPIO      GPIOA, LL_GPIO_PIN_0
#define KEY_UP           LL_GPIO_IsInputPinSet(KEY_UP_GPIO)
#define KEY_UP_OFF       1U
#define KEY_UP_ON        0U

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

