
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_H
#define __TIMER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#define		TIME_PRESCALER(x)			(x-1)

#define		TIME_100HZ_PRESCALER		(100-1)
#define		TIME_100HZ_PERIOD			(8400)

#define		TIME_1000HZ_PRESCALER		(10-1)
#define		TIME_1000HZ_PERIOD			(8400)

#define		TIME_10KHZ_PRESCALER		(10-1)
#define		TIME_10KHZ_PERIOD			(840)

#define		TIME_PRESCALER_8			(8-1)
#define		TIME_PRESCALER_10			(10-1)
#define		TIME_PRESCALER_100			(100-1)
#define		TIME_PRESCALER_84			(84-1)

extern uint32_t Freq_InputCapture[];


void TIM3_Config(uint16_t Prescaler,uint16_t Period);
void TIM4_Config(uint16_t Prescaler,uint16_t Period);
void TIM1_Config(void);
void TIM2_Config(void);

void TIM_Set_Duty(TIM_TypeDef* TIMx, uint32_t CHx,uint8_t Duty);




#endif /* __TIMER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
