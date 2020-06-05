
/****************************
1.CS ʹ��GPIO
2.SPIx		--SPI������
3.GPIOx		--SPI CS���Ŷ˿�
4.GPIO_Pin	--SPI CS����
****************************/

/* Includes ------------------------------------------------------------------*/
#include "spi.h"
#include "config.h"

/************************************ ����SPI CS���� ************************************/

#define		SPI3_SOFT_CS1_ENABLE	1
#define		SPI3_SOFT_CS1_PORT		GPIOD
#define		SPI3_SOFT_CS1_PIN		GPIO_Pin_7
#define		SPI3_SOFT_CS1_AHB		RCC_AHB1Periph_GPIOD

#define		SPI3_SOFT_CS2_ENABLE	1
#define		SPI3_SOFT_CS2_PORT		GPIOD
#define		SPI3_SOFT_CS2_PIN		GPIO_Pin_1
#define		SPI3_SOFT_CS2_AHB		RCC_AHB1Periph_GPIOD
/************************************ ����SPI CS���� ************************************/


/****************************
SPI��ʼ�����ã���Ҫ�õ�ǰ���
CS���ź궨�塣
****************************/
void SPI_Soft_Configuration(SPI_TypeDef* SPIx)
{
	
	SPI_InitTypeDef SPI_InitStruct;	 
	GPIO_InitTypeDef GPIO_InitStructure;


	
	
	
	/*���� ��������*/
	if(SPIx==SPI1){
		;//
	}else if(SPIx==SPI2){
		;//
	}else if(SPIx==SPI3)
	{
		/*CS ��������*/
#if(SPI3_SOFT_CS1_ENABLE==1)
		RCC_AHB1PeriphClockCmd(SPI3_SOFT_CS1_AHB, ENABLE);	
		
		GPIO_InitStructure.GPIO_Pin = SPI3_SOFT_CS1_PIN; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(SPI3_SOFT_CS1_PORT, &GPIO_InitStructure);
		GPIO_SetBits(SPI3_SOFT_CS1_PORT,SPI3_SOFT_CS1_PIN);	//Ĭ�ϲ�ʹ��
#endif

#if(SPI3_SOFT_CS2_ENABLE==1)
		RCC_AHB1PeriphClockCmd(SPI3_SOFT_CS2_AHB, ENABLE);	
		
		GPIO_InitStructure.GPIO_Pin = SPI3_SOFT_CS2_PIN; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(SPI3_SOFT_CS2_PORT, &GPIO_InitStructure);
		GPIO_SetBits(SPI3_SOFT_CS2_PORT,SPI3_SOFT_CS2_PIN);//Ĭ�ϲ�ʹ��
#endif
		/*CS ��������*/
	
		/*���� ��������*/
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3,ENABLE);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_SPI3);//SPI3_SCK:PC10
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_SPI3);//SPI3_MISO:PC11
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_SPI3);//SPI3_MOSI:PC12
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;  
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		/*���� ��������*/
	}
	
	
	
	SPI_I2S_DeInit(SPIx);
	SPI_InitStruct.SPI_Direction= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; 
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;//SPI_CPOL_High;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;//APB1=168M/4=42M; 42M/128=328.125k
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_Init(SPIx, &SPI_InitStruct);
	SPI_Cmd(SPIx, ENABLE);

}


/****************************
1.SPI CSʹ�ܣ�
2.SPIx SPIָ�룻
3.cs ͨ����
****************************/
void SPI_Soft_CS_Enable(SPI_TypeDef* SPIx,u8 cs)
{
	if(SPIx==SPI1){
		;//
	}else if(SPIx==SPI2){
		;//
	}else if(SPIx==SPI3)
	{	
		if(cs==1)
		{
#if(SPI3_SOFT_CS1_ENABLE==1)
			GPIO_ResetBits(SPI3_SOFT_CS1_PORT,SPI3_SOFT_CS1_PIN);
			GPIO_SetBits(SPI3_SOFT_CS2_PORT,SPI3_SOFT_CS2_PIN);
#endif
		}else if(cs==2){
#if(SPI3_SOFT_CS2_ENABLE==1)
			GPIO_ResetBits(SPI3_SOFT_CS2_PORT,SPI3_SOFT_CS2_PIN);
			GPIO_SetBits(SPI3_SOFT_CS1_PORT,SPI3_SOFT_CS1_PIN);
#endif
		}
	}
}

/****************************
1.SPI CS��ʹ�ܣ�
2.SPIx SPIָ�룻
3.cs ͨ����
****************************/
void SPI_Soft_CS_Disable(SPI_TypeDef* SPIx,u8 cs)
{	
	if(SPIx==SPI1){
		;//
	}else if(SPIx==SPI2){
		;//
	}else if(SPIx==SPI3)
	{	
		if(cs==1)
		{
#if(SPI3_SOFT_CS1_ENABLE==1)
			GPIO_SetBits(SPI3_SOFT_CS1_PORT,SPI3_SOFT_CS1_PIN);
#endif
		}else if(cs==2){
#if(SPI3_SOFT_CS2_ENABLE==1)
			GPIO_SetBits(SPI3_SOFT_CS2_PORT,SPI3_SOFT_CS2_PIN);
#endif
		}
	}
}



/****************************
1.SPI ��д�ֽ� ��
2.SPIx SPIָ�룻
3.cs ͨ����
****************************/
u8 SPI_transmit(SPI_TypeDef* SPIx,u8 byte)
{
	u8 data;
	
	
	/* Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
	/* Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPIx, byte);
	/* Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
	/* Return the byte read from the SPI bus */
	data = SPI_I2S_ReceiveData(SPIx);
	
	
	return data;
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
