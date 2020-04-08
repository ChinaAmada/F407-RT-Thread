


#include "config.h"

void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

	/* Configure  pin(PC3) in alternate function */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_Init(GPIOC, &GPIO_InitStructure);


  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);

	/* Configure  pin(PC3) in alternate function */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
}


u32 Get_Self_Addr(void)
{
	u32 addr=0;

	addr +=GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)<<3;
	addr +=GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)<<2;
	addr +=GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)<<1;
	addr +=GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)<<0;

	return addr;
	//return (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)<<3+GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)<<2+GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)<<1+GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)<<0);
}


void LED_Flash(void)
{
	GPIO_ToggleBits(GPIOC,GPIO_Pin_3);
}
