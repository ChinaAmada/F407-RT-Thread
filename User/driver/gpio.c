#include "stm32f4xx.h"
#include "config.h"



void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	/* Configure  pin(PE2) for LED */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_Init(GPIOE, &GPIO_InitStructure);

}


u32 Get_Self_Addr(void)
{
	u32 addr=0;

	/*
	addr +=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15)<<3;
	addr +=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)<<2;
	addr +=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)<<1;
	addr +=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)<<0;
	*/
	addr = 7;
	
	return addr;
	//return (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)<<3+GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)<<2+GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)<<1+GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)<<0);
}


void LED_Flash(void)
{
	//GPIO_ToggleBits(GPIOC,GPIO_Pin_3);
	GPIO_ToggleBits(LED_PORT,LED_PIN);
}

/*
DO×¢²áº¯Êý
*/
void DO_Regist(GPIO_TypeDef* GPIOx, uint16_t Pin)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	uint32_t RCC_AHB1Periph;
	
	RCC_AHB1Periph = (1<<((GPIOx-GPIOA)/(GPIOB-GPIOA)));
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph,ENABLE);
	/* Configure  pin(PE2) for LED */
	GPIO_InitStructure.GPIO_Pin = Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

/*
para1:port
para2:pin

*/
void DO_Toggle(GPIO_TypeDef* GPIOx, uint16_t Pin)
{
	GPIO_ToggleBits(GPIOx,Pin);
}

/*
para1:port
para2:pin
para3:set or reset
*/
void DO_Contrl(GPIO_TypeDef* GPIOx, uint16_t Pin,uint8_t val)
{
	if(val==RESET){
		GPIO_ResetBits(GPIOx,Pin);
	}else{
		GPIO_SetBits(GPIOx,Pin);
	}
}

/*
ÓÃ»§DOÅäÖÃ
*/
void DO_Config(void)
{
	DO_Regist(LED_PORT,LED_PIN);
	DO_Regist(BUZZER_PORT,BUZZER_PIN);
	
	DO_Regist(DO1_PORT,DO1_PIN);
	DO_Regist(DO2_PORT,DO2_PIN);
	DO_Regist(DO3_PORT,DO3_PIN);
	DO_Regist(DO4_PORT,DO4_PIN);
	DO_Regist(DO5_PORT,DO5_PIN);
	DO_Regist(DO6_PORT,DO6_PIN);
	DO_Regist(DO1_2_DS_PORT,DO1_2_DS_PIN);
	DO_Regist(DO3_4_DS_PORT,DO3_4_DS_PIN);
	DO_Regist(DO5_6_DS_PORT,DO5_6_DS_PIN);

}


