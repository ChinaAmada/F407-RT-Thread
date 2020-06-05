
  
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
#define	DO1_2_DS_AHB		RCC_AHB1Periph_GPIOB	//�������Ƭѡ
#define	DO3_4_DS_AHB		RCC_AHB1Periph_GPIOD	//�������Ƭѡ
#define	DO5_6_DS_AHB		RCC_AHB1Periph_GPIOC	//�������Ƭѡ

#define	BUZZER_PORT			GPIOB
#define	LED_PORT			GPIOE
#define	DO1_PORT			GPIOB	//ѭ����
#define	DO2_PORT			GPIOE	//ɢ��С���ȣ��Լ��̵��µķ���
#define	DO3_PORT			GPIOE	//��ȴ����
#define	DO4_PORT			GPIOE	//ѭ������
#define	DO5_PORT			GPIOE
#define	DO6_PORT			GPIOE
#define	DO1_2_DS_PORT		GPIOB	//�������Ƭѡ
#define	DO3_4_DS_PORT		GPIOD	//�������Ƭѡ
#define	DO5_6_DS_PORT		GPIOC	//�������Ƭѡ

#define	BUZZER_PIN			GPIO_Pin_8
#define	LED_PIN				GPIO_Pin_2
#define	DO1_PIN				GPIO_Pin_11	//ѭ����
#define	DO2_PIN				GPIO_Pin_15	//ɢ��С���ȣ��Լ��̵��µķ���
#define	DO3_PIN				GPIO_Pin_14	//��ȴ����
#define	DO4_PIN				GPIO_Pin_12	//ѭ������
#define	DO5_PIN				GPIO_Pin_5
#define	DO6_PIN				GPIO_Pin_6	//ɨ�봰����
#define	DO1_2_DS_PIN		GPIO_Pin_10	//�������Ƭѡ
#define	DO3_4_DS_PIN		GPIO_Pin_10	//�������Ƭѡ
#define	DO5_6_DS_PIN		GPIO_Pin_5	//�������Ƭѡ



void GPIO_Config(void);
u32 Get_Self_Addr(void);
void LED_Flash(void);
void DO_Regist(GPIO_TypeDef* GPIOx, uint16_t Pin);
void DO_Contrl(GPIO_TypeDef* GPIOx, uint16_t Pin,uint8_t val);
void DO_Config(void);
void DO_Toggle(GPIO_TypeDef* GPIOx, uint16_t Pin);
#endif /* __GPIO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
