/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    i2c.h
  * @brief   This file contains all the function prototypes for
  *          the i2c.c file
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
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN Private defines */
/* STM32�豸��ַ�����ⶨ�壬ֻҪ��EEPROM��ַ���غϼ��� */
#define STM32_ADDR 		0x5F
#define EEPROM_ADDR   	0xA0

/* USER CODE END Private defines */

void MX_I2C1_Init(void);

/* USER CODE BEGIN Prototypes */
uint8_t EEPROM_ByteWrite(uint8_t addr, uint8_t* data);
uint8_t EEPROM_RandomRead(uint8_t addr, uint8_t* data);
uint8_t EEPROM_PageWrite(uint8_t addr, uint8_t *data, uint8_t num);
uint8_t EEPROM_SeqRead(uint8_t addr, uint8_t* data, uint8_t num);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

