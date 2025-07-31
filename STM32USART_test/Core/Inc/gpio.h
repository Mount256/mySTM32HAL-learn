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
#define LED0_GPIO        GPIOB, GPIO_PIN_5
#define LED0_Toggle      HAL_GPIO_TogglePin(LED0_GPIO)
#define LED0_OFF         HAL_GPIO_WritePin(LED0_GPIO, GPIO_PIN_SET)
#define LED0_ON          HAL_GPIO_WritePin(LED0_GPIO, GPIO_PIN_RESET)

#define LED1_GPIO        GPIOE, GPIO_PIN_5
#define LED1_Toggle      HAL_GPIO_TogglePin(LED1_GPIO)
#define LED1_OFF         HAL_GPIO_WritePin(LED1_GPIO, GPIO_PIN_SET)
#define LED1_ON          HAL_GPIO_WritePin(LED1_GPIO, GPIO_PIN_RESET)

#define BEEP_GPIO        GPIOB, GPIO_PIN_8
#define BEEP_Toggle      HAL_GPIO_TogglePin(BEEP_GPIO)
#define BEEP_OFF         HAL_GPIO_WritePin(BEEP_GPIO, GPIO_PIN_RESET)
#define BEEP_ON          HAL_GPIO_WritePin(BEEP_GPIO, GPIO_PIN_SET)

#define KEY0_GPIO_PIN    GPIO_PIN_4
#define KEY0             HAL_GPIO_ReadPin(GPIOE, KEY0_GPIO_PIN)
#define KEY0_OFF         GPIO_PIN_RESET
#define KEY0_ON          GPIO_PIN_SET

#define KEY1_GPIO_PIN    GPIO_PIN_3
#define KEY1             HAL_GPIO_ReadPin(GPIOE, KEY1_GPIO_PIN)
#define KEY1_OFF         GPIO_PIN_RESET
#define KEY1_ON          GPIO_PIN_SET

#define KEY_UP_GPIO_PIN    GPIO_PIN_0
#define KEY_UP             HAL_GPIO_ReadPin(GPIOA, KEY_UP_GPIO_PIN)
#define KEY_UP_OFF         GPIO_PIN_SET
#define KEY_UP_ON          GPIO_PIN_RESET

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

