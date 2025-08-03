/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.h
  * @brief   This file contains all the function prototypes for
  *          the spi.c file
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
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN Private defines */
/*********** Definition ***********/
	
#define FLASH_SPI_CS_PORT 		GPIOB
#define FLASH_SPI_CS_PIN 		GPIO_PIN_12

#define FLASH_SPI_SCK_PORT 		GPIOB
#define FLASH_SPI_SCK_PIN 		GPIO_PIN_13

#define FLASH_SPI_MISO_PORT 	GPIOB
#define FLASH_SPI_MISO_PIN 		GPIO_PIN_14

#define FLASH_SPI_MOSI_PORT 	GPIOB
#define FLASH_SPI_MOSI_PIN 		GPIO_PIN_15

#define FLASH_SPI_CS_HIGH  		HAL_GPIO_WritePin(FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN, GPIO_PIN_SET)
#define FLASH_SPI_CS_LOW 		HAL_GPIO_WritePin(FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN, GPIO_PIN_RESET)
	
/************** Instructions (W25Q128) ****************/

#define DUMMY 			0x00
#define JEDEC_ID 		0x9F
#define WRITE_ENABLE	0x06
#define READ_STATUS_1	0x05
#define READ_STATUS_2	0x35
#define SECTOR_ERASE 	0x20
#define PAGE_PROGRAM 	0x02
#define READ_DATA		0x03

#define TIMEOUT_VALUE   1000

/************** Status (W25Q128) ****************/

#define  W25Qx_OK        0x00U
#define  W25Qx_ERROR     0x01U
#define  W25Qx_BUSY      0x02U
#define  W25Qx_TIMEOUT   0x03U


/* USER CODE END Private defines */

void MX_SPI2_Init(void);

/* USER CODE BEGIN Prototypes */
/*********** Basic Function ***********/
static HAL_StatusTypeDef SPI_Transmit(uint8_t* send_buf, uint16_t size);
static HAL_StatusTypeDef SPI_Receive(uint8_t* recv_buf, uint16_t size);
static HAL_StatusTypeDef SPI_TransmitReceive(uint8_t* send_buf, uint8_t* recv_buf, uint16_t size);

/*********** Flash's Function ***********/
uint32_t SPI_FLASH_JEDEC_ID(void);          /* JEDEC ID */
void SPI_FLASH_Wait(void);                  /* Read Status Register */
void SPI_FLASH_Write_Enable(void);          /* Write Enable */
void SPI_FLASH_Sector_Erase(uint32_t addr); /* Sector Erase */
void SPI_FLASH_Page_Program(uint32_t addr, uint32_t num, uint8_t *data); /* Page Program */
void SPI_FLASH_Read_Data(uint32_t addr, uint32_t num, uint8_t *data);    /* Read Data */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

