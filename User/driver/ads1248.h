
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADS1248_H
#define __ADS1248_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"


/******************ads1248�Ĵ�����ַ*******************/
#define   ADS1248_CMD_WAKEUP    0x00
#define   ADS1248_CMD_SLEEP     0x02
#define   ADS1248_CMD_SYNC      0x04
#define   ADS1248_CMD_RESET     0x06
#define   ADS1248_CMD_NOP       0xff
#define   ADS1248_CMD_RDATA     0x12
#define   ADS1248_CMD_RDATAC    0x14
#define   ADS1248_CMD_SDATAC    0x16
#define   ADS1248_CMD_RREG      0x20
#define   ADS1248_CMD_WREG      0x40

#define   ADS1248_REG_MUX0    0x00
#define   ADS1248_REG_VBIAS   0x01
#define   ADS1248_REG_MUX1    0x02
#define   ADS1248_REG_SYS0    0x03
#define   ADS1248_REG_CFC0    0x04
#define   ADS1248_REG_CFC1    0x05
#define   ADS1248_REG_CFC2    0x06
#define   ADS1248_REG_FSC0    0x07
#define   ADS1248_REG_FSC1    0x08
#define   ADS1248_REG_FSC2    0x09
#define   ADS1248_REG_IDAC0   0x0a
#define   ADS1248_REG_IDAC1   0x0b
#define   ADS1248_REG_GPIOCFG  0x0c
#define   ADS1248_REG_GPIODIR  0x0d
#define   ADS1248_REG_GPIODAT  0x0e

#define Wash_Probe_Liquid_RTD   0x01 //ͨ��1��ϴ��Һ�¶�ͨ��
#define Trigger_Liquid_RTD      0x02 //ͨ��2������Һ�¶�ͨ��
#define Bead_Wash_Liquid_RTD    0x03 //ͨ��3��������ϴҺ�¶�ͨ��
#define Incubator_Tray_RTD1     0x04 //ͨ��4�������̼����¶�ͨ��1
#define Incubator_Tray_RTD2     0x05 //ͨ��5�������̼����¶�ͨ��2
#define Reagent_Tray            0x06 //ͨ��6���Լ��������¶�ͨ��
#define Machine_RTD             0x07 //ͨ��7�������¶�ͨ��
#define Prevent_Atomization_RTD 0x08 //ͨ��8����ֹ���¶�ͨ��



void Ads_Init(unsigned char ADSx);
float Ads_Read_Temp(unsigned char ADSx,unsigned char Channel);

#endif /* __USART_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
