
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H
#define __SPI_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"


typedef struct _SPI_Config{
	SPI_TypeDef* SPIx;				//SPI����
	GPIO_TypeDef* GPIO_CS;			//Ƭѡ�˿�
	uint32_t GPIO_Pin_CS;			//Ƭѡ����
	
	GPIO_TypeDef* GPIO_CLK;			//CLK �˿�
	uint32_t GPIO_Pin_CLK;			//CLK ����
	
	GPIO_TypeDef* GPIO_MSIO;		//MSIO �˿�
	uint32_t GPIO_Pin_MSIO;			//MSIO ����
	
	GPIO_TypeDef* GPIO_MOSI;		//MOSI �˿�
	uint32_t GPIO_Pin_MOSI;			//MOSI ����
	
	uint32_t AHB1Periph_GPIO_CS;	//CS����ʱ��
	uint32_t AHB1Periph_GPIO_CLK;	//CLK����ʱ��
	uint32_t AHB1Periph_GPIO_MSIO;	//MSIO����ʱ��
	uint32_t AHB1Periph_GPIO_MOSI;	//MOSI����ʱ��
	uint32_t AHB1Periph_SPIx;		//SPIʱ��

	SPI_InitTypeDef SPIx_InitStruct;	//��ʼ���ṹ	
}SPI_Config;


void SPI_Soft_Configuration(SPI_TypeDef* SPIx);
void SPI_Soft_CS_Enable(SPI_TypeDef* SPIx,u8 cs);
void SPI_Soft_CS_Disable(SPI_TypeDef* SPIx,u8 cs);
u8 SPI_transmit(SPI_TypeDef* SPIx,u8 byte);


#endif /* __USART_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
