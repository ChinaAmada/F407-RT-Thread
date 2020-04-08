
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H
#define __CAN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define 	CAN1_BUFF_SIZE			32
#define 	CAN1_BUFF_MASK			(CAN1_BUFF_SIZE-1)

u32 Get_CAN1_Addr(void);
void CAN1_Config(void);
int CAN1_SendData(char* data,int len);
int CAN1_SendData_ID(unsigned int id,char* data,int len);
int CAN1_Push_Packet(CanRxMsg* rx);
int CAN1_Read_Packet(CanRxMsg* rx);

#endif /* __CAN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
