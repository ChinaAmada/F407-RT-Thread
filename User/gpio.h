
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H
#define __GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "config.h"

#include <stdio.h>


#define	LED_FLASH_TICKS			10

void GPIO_Config(void);
u32 Get_Self_Addr(void);
void LED_Flash(void);

#endif /* __GPIO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
