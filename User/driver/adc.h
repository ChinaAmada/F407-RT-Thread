
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H
#define __ADC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

#define		PRE_VOLTAGE      			11		//分压系数
#define		REF_VOLTAGE					2.5		//参考电压

#define 	ADC1_CHANNEL_NUM    		13		 //ADC通道数


//#define		PER      12        //外设数量
//#define		NUM      10        //采集数量

#define		FILTER_NUM		100//10

typedef struct _adc_val{
	float Ch0_Valve5_IS[FILTER_NUM];
	float Ch0_Valve5_IS_Val;
	float Ch0_Valve6_IS[FILTER_NUM];
	float Ch0_Valve6_IS_Val;
	float Ch1_3V3_ADC;
	float Ch2_24V_ADC;
	float Ch3_5V_ADC;
	float Ch4_Heat1_Iout;
	float Ch5_Heat2_Iout;
	float Ch6_Heat3_Iout;
	float Ch7_Heat4_Iout;
	float Ch8_Valve1_IS[FILTER_NUM];
	float Ch8_Valve1_IS_Val;
	float Ch8_Valve2_IS[FILTER_NUM];
	float Ch8_Valve2_IS_Val;
	float Ch9_Valve3_IS[FILTER_NUM];
	float Ch9_Valve3_IS_Val;
	float Ch9_Valve4_IS[FILTER_NUM];
	float Ch9_Valve4_IS_Val;
	float Ch10_TEC1_Iout;
	float Ch11_TEC2_Iout;
	float Ch12_TEC3_Iout;
}ADC_VAL;


extern u16 ADC_Result[];

float Average_Float(float* arr,uint32_t len);
void ADC_GPIO_config(void);
void ADC_Common_config(void);
void ADC_DMA_config(void);
void ADC_All_Config(void);

#endif /* __ADC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
