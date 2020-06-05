
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H
#define __GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "config.h"

#include <stdio.h>


#define	LED_FLASH_TICKS			10


#define	LED_AHB				RCC_AHB1Periph_GPIOE
#define	DO1_AHB				RCC_AHB1Periph_GPIOB
#define	DO2_AHB				RCC_AHB1Periph_GPIOE
#define	DO3_AHB				RCC_AHB1Periph_GPIOE
#define	DO4_AHB				RCC_AHB1Periph_GPIOE
#define	DO5_AHB				RCC_AHB1Periph_GPIOE
#define	DO6_AHB				RCC_AHB1Periph_GPIOE
#define	DO1_2_DS_AHB		RCC_AHB1Periph_GPIOB	//电流检测片选
#define	DO3_4_DS_AHB		RCC_AHB1Periph_GPIOD	//电流检测片选
#define	DO5_6_DS_AHB		RCC_AHB1Periph_GPIOC	//电流检测片选

#define	BUZZER_PORT			GPIOB
#define	LED_PORT			GPIOE
#define	DO1_PORT			GPIOB	//循环泵
#define	DO2_PORT			GPIOE	//散热小风扇，试剂盘底下的风扇
#define	DO3_PORT			GPIOE	//冷却风扇
#define	DO4_PORT			GPIOE	//循环风扇
#define	DO5_PORT			GPIOE
#define	DO6_PORT			GPIOE
#define	DO1_2_DS_PORT		GPIOB	//电流检测片选
#define	DO3_4_DS_PORT		GPIOD	//电流检测片选
#define	DO5_6_DS_PORT		GPIOC	//电流检测片选

#define	BUZZER_PIN			GPIO_Pin_8
#define	LED_PIN				GPIO_Pin_2
#define	DO1_PIN				GPIO_Pin_11	//循环泵
#define	DO2_PIN				GPIO_Pin_15	//散热小风扇，试剂盘底下的风扇
#define	DO3_PIN				GPIO_Pin_14	//冷却风扇
#define	DO4_PIN				GPIO_Pin_12	//循环风扇
#define	DO5_PIN				GPIO_Pin_5
#define	DO6_PIN				GPIO_Pin_6	//扫码窗加热
#define	DO1_2_DS_PIN		GPIO_Pin_10	//电流检测片选
#define	DO3_4_DS_PIN		GPIO_Pin_10	//电流检测片选
#define	DO5_6_DS_PIN		GPIO_Pin_5	//电流检测片选



void GPIO_Config(void);
u32 Get_Self_Addr(void);
void LED_Flash(void);
void DO_Regist(GPIO_TypeDef* GPIOx, uint16_t Pin);
void DO_Contrl(GPIO_TypeDef* GPIOx, uint16_t Pin,uint8_t val);
void DO_Config(void);
void DO_Toggle(GPIO_TypeDef* GPIOx, uint16_t Pin);
#endif /* __GPIO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
