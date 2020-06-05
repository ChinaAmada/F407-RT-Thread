
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UPDATE_H
#define __UPDATE_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

#define		CAN_MASTER_ADDR						1
#define		CAN_MESSAGE_MAX_SIZE			8


/* 协议控制字 */
#define		IAP_KEY_START					0x0001
#define		IAP_KEY_STOP					0x0002
#define		IAP_KEY_DATA					0x0003
#define		IAP_KEY_OVER					0x0004

#define		IAP_KEY_ACK						0x1001
#define		IAP_KEY_ERR						0x1002



/* 错误类型 */
#define 	ERR_FLASH_ERASE				0x0001
#define 	ERR_KEY_ERROR				0x0002
#define 	ERR_STATUS_ERROR			0x0003

typedef struct _data_frame
{
	u16 ctrl_key;
	u16 ctrl_para;
	u32 data;
}DATA_FRAME;
	

u32 htonl(u32 x);

int CAN1_Send_ACK(u16 para,u32 data);
int CAN1_Send_ERR(u16 para,u32 data);
int Update_App_Task(void);

#endif /* __UPDATE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
