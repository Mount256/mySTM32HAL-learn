/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    i2c.c
  * @brief   This file provides code for the configuration
  *          of the I2C instances.
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
#include "i2c.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

I2C_HandleTypeDef hi2c1;

/* I2C1 init function */
void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();

    /* I2C1 interrupt Init */
    HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
    HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

    /* I2C1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
    HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
  /* USER CODE BEGIN I2C1_MspDeInit 1 */

  /* USER CODE END I2C1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**
  * @brief  EEPROM字节写入
  * @param  addr:要写入数据的地址
			*data:数组的首地址
  * @retval	HAL_OK
  */
uint8_t EEPROM_ByteWrite(uint8_t addr, uint8_t* data)
{
	return HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, addr, I2C_MEMADD_SIZE_8BIT, data, 1, 0xFFFF);
} 

/**
  * @brief  EEPROM字节读出
  * @param  addr:要写入数据的地址
			*data:数组的首地址
  * @retval	HAL_OK
  */
uint8_t EEPROM_RandomRead(uint8_t addr, uint8_t* data)
{
	return HAL_I2C_Mem_Read(&hi2c1, EEPROM_ADDR, addr, I2C_MEMADD_SIZE_8BIT, data, 1, 0xFFFF);
}

/**
  * @brief  EEPROM页写入
  * @param  addr:要写入数据的地址
			*data:数组的首地址
			num:数据个数
  * @retval	HAL_OK
  */
uint8_t EEPROM_PageWrite(uint8_t addr, uint8_t *data, uint8_t num)
{
	uint8_t i = 0;
    uint16_t cnt = 0;		//写入字节计数
    
    /* 对于起始地址，有两种情况，分别判断 */
    if(0 == addr % 8 )
    {
        /* 1. 起始地址刚好是页开始地址 */
        /* 对于写入的字节数，有两种情况，分别判断 */
        if(num <= 8)
        {
            // 1.1 写入的字节数不大于一页，直接写入
            return HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, addr, I2C_MEMADD_SIZE_8BIT, data, num, 0xFFFF);
        }
        else
        {
            // 1.2 写入的字节数大于一页，先将整页循环写入
            for(i = 0;i < num/8; i++)
            {
                HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, addr, I2C_MEMADD_SIZE_8BIT, &data[cnt], 8, 0xFFFF);
                addr += 8;
                cnt += 8;
            }
            // 1.2 将剩余的字节写入
            return HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, addr, I2C_MEMADD_SIZE_8BIT, &data[cnt], num - cnt, 0xFFFF);
        }
    }
    else
    {
        /* 2. 起始地址偏离页开始地址 */
        /* 对于写入的字节数，有两种情况，分别判断 */
        if(num <= (8 - addr%8))
        {
            /* 2.1 在该页可以写完 */
            return HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, addr, I2C_MEMADD_SIZE_8BIT, data, num, 0xFFFF);
        }
        else
        {
            /* 2.2 该页写不完 */
            // 先将该页写完
            cnt += 8 - addr%8;
            HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, addr, I2C_MEMADD_SIZE_8BIT, data, cnt, 0xFFFF);
            addr += cnt;
            
            // 循环写整页数据
            for(i = 0;i < (num - cnt)/8; i++)
            {
                HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, addr, I2C_MEMADD_SIZE_8BIT, &data[cnt], 8, 0xFFFF);
                addr += 8;
                cnt += 8;
            }
            
            // 将剩下的字节写入
            return HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, addr, I2C_MEMADD_SIZE_8BIT, &data[cnt], num - cnt, 0xFFFF);
        }			
    }
}

/**
  * @brief  EEPROM连续读取
  * @param  addr:要读取数据的地址
			*data:要接收数据的容器
			num:数据个数
  * @retval	HAL_OK
  */
uint8_t EEPROM_SeqRead(uint8_t addr, uint8_t* data, uint8_t num)
{
	return HAL_I2C_Mem_Read(&hi2c1, EEPROM_ADDR, addr, I2C_MEMADD_SIZE_8BIT, data, num, 0xFFFF);
}

/* USER CODE END 1 */
