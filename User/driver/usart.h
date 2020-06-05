
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H
#define __USART_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"


#define	USART_BUFF_SIZE		512
#define	USART_MASK				(USART_BUFF_SIZE-1)


void USART6_Config(u32 bound);
void USART6_IT_Config(void);
void USART_Config(void);

int Usart_Send_Data(USART_TypeDef* USARTx,char* data,int len);

//int Usart6_Push_Data(void);
//int Usart6_Read_Data(char* data,int* len);
int Usart6_Set_RecPack_Flag(void);
int Usart6_Clear_RecPack_Flag(void);
int Usart6_Read_RecPack_Flag(void);


int Usart2_Push_Char(void);
int Usart6_Push_Char(void);

void rt_hw_console_output(const char *str);


#endif /* __USART_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
