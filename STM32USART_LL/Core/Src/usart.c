/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
/**
  * @brief 重定向c库函数printf到USARTx
  * @retval None
  */
int fputc(int ch, FILE *f)
{
    LL_USART_TransmitData8(USART1, (uint8_t)ch);
	while(LL_USART_IsActiveFlag_TXE(USART1) != SET);  // 等待发送数据寄存器为空
	
    return ch;
}
 
/**
  * @brief 重定向c库函数getchar, scanf到USARTx
  * @retval None
  */
int fgetc(FILE *f)
{	
	uint8_t ch;
	
	while(LL_USART_IsActiveFlag_RXNE(USART1) != SET);  // 等待接收数据寄存器为空
	ch = (int)LL_USART_ReceiveData8(USART1);
	while(LL_USART_IsActiveFlag_TXE(USART1) != SET);  // 等待发送数据寄存器为空
    
	return (int)ch;
}

/* USER CODE END 0 */

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
  /**USART1 GPIO Configuration
  PA9   ------> USART1_TX
  PA10   ------> USART1_RX
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USART1 interrupt Init */
  // NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1, 0));
  // NVIC_EnableIRQ(USART1_IRQn);

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART1, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART1);
  LL_USART_Enable(USART1);
  /* USER CODE BEGIN USART1_Init 2 */
  LL_USART_EnableIT_IDLE(USART1);
  LL_USART_EnableIT_RXNE(USART1);

  /* USER CODE END USART1_Init 2 */

}

/* USER CODE BEGIN 1 */
void USART_SendByte(USART_TypeDef *USARTx, uint8_t data)
{
	LL_USART_TransmitData8(USARTx, data); //发送数据
	while(LL_USART_IsActiveFlag_TXE(USARTx) != SET); //等待发送完成
}

void USART_SendHalfWord(USART_TypeDef* USARTx, uint16_t data)
{
	uint8_t temp_h, temp_l;
	temp_h = (data & 0xFF00) >> 8; //截取高4位
	temp_l = data & 0x00FF; //截取低4位
	
	LL_USART_TransmitData8(USARTx, temp_h); 
	while(LL_USART_IsActiveFlag_TXE(USARTx) != SET); 
	
	LL_USART_TransmitData8(USARTx, temp_l);
	while(LL_USART_IsActiveFlag_TXE(USARTx) != SET);
}

void USART_SendArray(USART_TypeDef* USARTx, uint8_t* Array, uint8_t num)
{
	uint8_t i;
	for( i = 0; i < num; i++)
	{
		LL_USART_TransmitData8(USARTx, Array[i]);
		while(LL_USART_IsActiveFlag_TXE(USARTx) != SET);
	}
}

void USART_SendStr(USART_TypeDef* USARTx, uint8_t* str)
{
	while( *(str) != '\0')
	{
		LL_USART_TransmitData8(USARTx, *(str++));
		while(LL_USART_IsActiveFlag_TXE(USARTx) != SET); 
	}
}

/* USER CODE END 1 */
