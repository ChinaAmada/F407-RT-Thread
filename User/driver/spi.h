
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H
#define __SPI_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"


typedef struct _SPI_Config{
	SPI_TypeDef* SPIx;				//SPI索引
	GPIO_TypeDef* GPIO_CS;			//片选端口
	uint32_t GPIO_Pin_CS;			//片选引脚
	
	GPIO_TypeDef* GPIO_CLK;			//CLK 端口
	uint32_t GPIO_Pin_CLK;			//CLK 引脚
	
	GPIO_TypeDef* GPIO_MSIO;		//MSIO 端口
	uint32_t GPIO_Pin_MSIO;			//MSIO 引脚
	
	GPIO_TypeDef* GPIO_MOSI;		//MOSI 端口
	uint32_t GPIO_Pin_MOSI;			//MOSI 引脚
	
	uint32_t AHB1Periph_GPIO_CS;	//CS引脚时钟
	uint32_t AHB1Periph_GPIO_CLK;	//CLK引脚时钟
	uint32_t AHB1Periph_GPIO_MSIO;	//MSIO引脚时钟
	uint32_t AHB1Periph_GPIO_MOSI;	//MOSI引脚时钟
	uint32_t AHB1Periph_SPIx;		//SPI时钟

	SPI_InitTypeDef SPIx_InitStruct;	//初始化结构	
}SPI_Config;


void SPI_Soft_Configuration(SPI_TypeDef* SPIx);
void SPI_Soft_CS_Enable(SPI_TypeDef* SPIx,u8 cs);
void SPI_Soft_CS_Disable(SPI_TypeDef* SPIx,u8 cs);
u8 SPI_transmit(SPI_TypeDef* SPIx,u8 byte);


#endif /* __USART_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
