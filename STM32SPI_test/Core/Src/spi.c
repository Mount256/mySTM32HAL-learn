/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.c
  * @brief   This file provides code for the configuration
  *          of the SPI instances.
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
#include "spi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

SPI_HandleTypeDef hspi2;

/* SPI2 init function */
void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspInit 0 */

  /* USER CODE END SPI2_MspInit 0 */
    /* SPI2 clock enable */
    __HAL_RCC_SPI2_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI2 GPIO Configuration
    PB13     ------> SPI2_SCK
    PB14     ------> SPI2_MISO
    PB15     ------> SPI2_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI2_MspInit 1 */

  /* USER CODE END SPI2_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspDeInit 0 */

  /* USER CODE END SPI2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI2_CLK_DISABLE();

    /**SPI2 GPIO Configuration
    PB13     ------> SPI2_SCK
    PB14     ------> SPI2_MISO
    PB15     ------> SPI2_MOSI
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

  /* USER CODE BEGIN SPI2_MspDeInit 1 */

  /* USER CODE END SPI2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/*********** Basic Function ***********/
/* Send 1 Byte */
static HAL_StatusTypeDef SPI_Transmit(uint8_t* send_buf, uint16_t size)
{
    return HAL_SPI_Transmit(&hspi2, send_buf, size, TIMEOUT_VALUE);
}

/* Receive 1 Byte */
static HAL_StatusTypeDef SPI_Receive(uint8_t* recv_buf, uint16_t size)
{
   return HAL_SPI_Receive(&hspi2, recv_buf, size, TIMEOUT_VALUE);
}

/* Send 1 Byte and Receive Another 1 Byte */
static HAL_StatusTypeDef SPI_TransmitReceive(uint8_t* send_buf, uint8_t* recv_buf, uint16_t size)
{
   return HAL_SPI_TransmitReceive(&hspi2, send_buf, recv_buf, size, TIMEOUT_VALUE);
}


/*********** Flash's Function ***********/
/* Instrction: JEDEC ID */
uint32_t SPI_FLASH_JEDEC_ID(void)
{
	uint32_t FLASH_ID;
	uint8_t send_cmd[4] = {JEDEC_ID, DUMMY, DUMMY, DUMMY};
	uint8_t recv_buf[3] = {DUMMY, DUMMY, DUMMY};
	
	FLASH_SPI_CS_LOW; 
	
	if (SPI_Transmit(send_cmd, 4) != HAL_OK)
		return W25Qx_ERROR;
	
	if (SPI_Receive(recv_buf, 3) != HAL_OK)
		return W25Qx_ERROR;
	
	FLASH_ID = recv_buf[0];
	FLASH_ID <<= 8;
	FLASH_ID |= recv_buf[1];
	FLASH_ID <<= 8;
	FLASH_ID |= recv_buf[2];
	
	FLASH_SPI_CS_HIGH; 
	
	return FLASH_ID;
}

/* Read Status Register */
void SPI_FLASH_Wait(void)
{
	uint8_t reg = 0;
	uint8_t send_cmd_1 = READ_STATUS_1;
	//uint8_t send_cmd_2 = READ_STATUS_2;
	uint8_t send_dummy = DUMMY;
	
	FLASH_SPI_CS_LOW;
	
	SPI_Transmit(&send_cmd_1, 1);
	
	do {
		reg = SPI_Transmit(&send_dummy, 1);
	} while((reg & 0x01) == 1); // wait for BUSY bit: 1->0
	
	FLASH_SPI_CS_HIGH; 
}

/* Instrction: Write Enable */
void SPI_FLASH_Write_Enable(void)
{
	uint8_t send_cmd = WRITE_ENABLE;
	
	FLASH_SPI_CS_LOW; 
	SPI_Transmit(&send_cmd, 1);
	FLASH_SPI_CS_HIGH; 
}

/* Instrction: Sector Erase */
void SPI_FLASH_Sector_Erase(uint32_t addr)
{
	//sector_addr *= 4096;    //每个块有16个扇区，每个扇区的大小是4KB，需要换算为实际地址
    //sector_addr <<= 8;
	
	uint8_t send_cmd[4] = {SECTOR_ERASE, (addr<<16)&0xFF, (addr<<8)&0xFF, (addr)&0xFF};
	
	SPI_FLASH_Write_Enable();
	//SPI_FLASH_Wait();
	
	FLASH_SPI_CS_LOW;
	SPI_Transmit(send_cmd, 4);
	FLASH_SPI_CS_HIGH;
	
	SPI_FLASH_Wait();
}

/* Instrction: Page Program */
void SPI_FLASH_Page_Program(uint32_t addr, uint32_t num, uint8_t *data)
{
	uint8_t send_cmd[4] = {PAGE_PROGRAM, (addr<<16)&0xFF, (addr<<8)&0xFF, (addr)&0xFF};
	
	SPI_FLASH_Write_Enable();
	//SPI_FLASH_Wait();
	
	FLASH_SPI_CS_LOW;
	SPI_Transmit(send_cmd, 4);
	SPI_Transmit(data, num);
	FLASH_SPI_CS_HIGH;
	
	SPI_FLASH_Wait();
}

/* Instrction: Read Data */
void SPI_FLASH_Read_Data(uint32_t addr, uint32_t num, uint8_t *data)
{
	uint8_t send_cmd[4] = {READ_DATA, (addr<<16)&0xFF, (addr<<8)&0xFF, (addr)&0xFF};
	
	SPI_FLASH_Wait();
	
	FLASH_SPI_CS_LOW;
	SPI_Transmit(send_cmd, 4);
	SPI_Receive(data, num); 
	FLASH_SPI_CS_HIGH;
}

/* USER CODE END 1 */
