

/* Includes ------------------------------------------------------------------*/
#include "config.h"


/* 8个字节数据，
	前4个字节：前两个字节控制字，后两个字节控制参数。
	后4个字节：数据。
*/



//const char  UPDATE_START[8]	={0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05};
//const char  UPDATE_STOP[8]	={0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03};

const char  UPDATE_ACK[8]		={0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06};
const char  UPDATE_ERR[8]		={0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08};


static vu32 Frame_Index=0;
static FlagStatus Update_Start_Flag=RESET;


int Update_App_Task(void) 
{
	int ret;
	CanRxMsg Can_Tmp_Rx_Msg;
	DATA_FRAME* p_Data;
	vu32  Tmp_Addr;
	u32 wdata;
	
	if(CAN1_Read_Packet(&Can_Tmp_Rx_Msg)==TRUE)
	{
		p_Data=(DATA_FRAME*)Can_Tmp_Rx_Msg.Data;
		if(Can_Tmp_Rx_Msg.DLC==CAN_MESSAGE_MAX_SIZE)
		{
			if(p_Data->ctrl_key==IAP_KEY_START)	//开始
			{
				printf("Update Start!\r\n");
				Frame_Index=0;
				Update_Start_Flag=SET;
				
				if(FLASH_If_Erase()==0)
				{	
					CAN1_Send_ACK(0,Frame_Index);
				}else{
					CAN1_Send_ERR(ERR_FLASH_ERASE,(__LINE__));
				}
				return SET;
			}else if(p_Data->ctrl_key==IAP_KEY_STOP)	//停止
			{
				printf("Update Stop!Frame_Index=%d\r\n",Frame_Index);
				Update_Start_Flag=RESET;
				CAN1_Send_ACK(Frame_Index,0);
				return SET;
			}else if(p_Data->ctrl_key==IAP_KEY_DATA){	//数据
				if(Update_Start_Flag==SET)	//正确
				{
					Tmp_Addr=APPLICATION_ADDRESS+4*Frame_Index;
					//write flash
					wdata=p_Data->data;
					if((ret=FLASH_If_Write((__IO uint32_t*)&Tmp_Addr, &wdata, 1))!=0)
					{
						printf("FLASH_If_Write err :%d!\r\n",ret);
						CAN1_Send_ERR(ERR_STATUS_ERROR,(__LINE__));
					}
					CAN1_Send_ACK(Frame_Index,0);
					//printf("Frame_Index %d!,data=%02x %02x %02x %02x\r\n",Frame_Index,Can_Tmp_Rx_Msg.Data[4],Can_Tmp_Rx_Msg.Data[5],Can_Tmp_Rx_Msg.Data[6],Can_Tmp_Rx_Msg.Data[7]);
					Frame_Index++;
					
					return SET;
				}else{		//错误
					printf("err packet!\r\n");
					CAN1_Send_ERR(ERR_STATUS_ERROR,(__LINE__));
					return RESET;
				}
			}else{			
				printf("err packet!\r\n");
				CAN1_Send_ERR(ERR_KEY_ERROR,(__LINE__));
				return RESET;
			}
		}
	}
	
	return RESET;
	
}


int CAN1_Send_ACK(u16 para,u32 data)
{
	char Can_Tmp_Tx_Msg[8];
	DATA_FRAME* p_Data=(DATA_FRAME*)Can_Tmp_Tx_Msg;
	
	p_Data->ctrl_key=IAP_KEY_ACK;
	p_Data->ctrl_para=para;
	p_Data->data=data;
	
	CAN1_SendData((char*)Can_Tmp_Tx_Msg,CAN_MESSAGE_MAX_SIZE);
	return SUCCESS;
}

int CAN1_Send_ERR(u16 para,u32 data)
{
	char Can_Tmp_Tx_Msg[8];
	DATA_FRAME* p_Data=(DATA_FRAME*)Can_Tmp_Tx_Msg;
	
	p_Data->ctrl_key=IAP_KEY_ERR;
	p_Data->ctrl_para=para;
	p_Data->data=data;
	
	CAN1_SendData((char*)Can_Tmp_Tx_Msg,CAN_MESSAGE_MAX_SIZE);
	
	return SUCCESS;
}




u32 htonl(u32 x)
{
        u8 *s = (u8 *)&x;
        return (u32)(s[0] << 24 | s[1] << 16 | s[2] << 8 | s[3]);

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
