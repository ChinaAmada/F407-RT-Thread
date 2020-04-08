


#include "config.h"


static u32 Self_Can_Addr=0;
static int Can1_Index_Head=0,Can1_Index_Tail=0;
CanRxMsg  Can1_Buff[CAN1_BUFF_SIZE];


u32 Get_CAN1_Addr(void)
{
	return Self_Can_Addr;
}

int CAN1_Read_Packet(CanRxMsg* rx)
{
	if(Can1_Index_Head==Can1_Index_Tail)
	{
		return FALSE;
	}else{
		memcpy((char*)rx,(char*)(Can1_Buff+Can1_Index_Tail),sizeof(CanRxMsg));
		Can1_Index_Tail++;
		Can1_Index_Tail=Can1_Index_Tail&CAN1_BUFF_MASK;
		return TRUE;
	}
	
}

int CAN1_Push_Packet(CanRxMsg* rx)
{
		memcpy((char*)(Can1_Buff+Can1_Index_Head),(char*)rx,sizeof(CanRxMsg));
		Can1_Index_Head++;
		Can1_Index_Head=Can1_Index_Head&CAN1_BUFF_MASK;
		return TRUE;
}

void CAN1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	
	Self_Can_Addr=Get_Self_Addr();
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	

	/* Connect CAN pins to AF9 */
  	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);
  	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1); 
	/* Configure  pin(Pa) in alternate function */
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  	GPIO_Init(GPIOA, &GPIO_InitStructure);


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	/* CAN register init */
  	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);
	
	/* CAN cell init */
	 CAN_InitStructure.CAN_TTCM = DISABLE;
	 CAN_InitStructure.CAN_ABOM = DISABLE;
	 CAN_InitStructure.CAN_AWUM = DISABLE;
	 CAN_InitStructure.CAN_NART = DISABLE;
	 CAN_InitStructure.CAN_RFLM = DISABLE;
	 CAN_InitStructure.CAN_TXFP = DISABLE;
	 CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	 CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	    
	 /* CAN Baudrate = 500KBps (CAN clocked at 30 MHz) */
	 CAN_InitStructure.CAN_BS1 = CAN_BS1_12tq;
	 CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
	 CAN_InitStructure.CAN_Prescaler = 4;
	 CAN_Init(CAN1, &CAN_InitStructure);

	

	  /* CAN filter init */
  	CAN_FilterInitStructure.CAN_FilterNumber = 0;
  	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;//CAN_FilterMode_IdMask;
  	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = (Self_Can_Addr&0x07)<<5;//0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
 	CAN_FilterInit(&CAN_FilterInitStructure);
  	
	  /* Enable FIFO 0 message pending Interrupt */
  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	
}


#if 0
void CAN1_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  /* CAN GPIOs configuration **************************************************/

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  /* Connect CAN pins */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1); 
  
  /* Configure CAN RX and TX pins */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);



  /* CAN configuration ********************************************************/  
  /* Enable CAN clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
  
  /* CAN register init */
  CAN_DeInit(CAN1);
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;//CAN_Mode_LoopBack;//CAN_Mode_Normal;

 // ***************************************************************
//       BaudRate = 1 / NominalBitTime
//       NominalBitTime = 1tq + tBS1 + tBS2
//       tq = (BRP[9:0] + 1) x tPCLK
//       tPCLK = CAN's clock = APB1's clock
//   1Mbps ???,???????6tq???,BS1=5, BS2=2
//   500kbps ???,???????8tq???,BS1=7, BS2=3
//   250kbps ???,???????14tq???,BS1=13, BS2=2
//   125k, 100k, 50k, 20k, 10k ??????? 250K ??
// ****************************************************************      
  /* CAN Baudrate = 500KBps (CAN clocked at 42 MHz)  42M/(1+12+8)/4=500k  CAN clocked= APB1's clock/CAN_Prescaler*/ 
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_12tq;//CAN_BS1_6tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
  CAN_InitStructure.CAN_Prescaler = 4;//2;
  CAN_Init(CAN1, &CAN_InitStructure);

//  /* CAN filter init */
//  CAN_FilterInitStructure.CAN_FilterNumber = 0;
//  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
//  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
//  CAN_FilterInitStructure.CAN_FilterIdHigh = std_id<<5;//0x0000;
//  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000 ;
//  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
//  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
//  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
//  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
//  CAN_FilterInit(&CAN_FilterInitStructure);

  /* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber = 0; //??????0,???0~13  
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList; //??????0????????  
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;//??????0???32?  
	
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000; //std_id<<5;  //?????CAN ID???
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;//
	
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;//0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;//0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
    
  /* Transmit Structure preparation */
//  TxMessage.StdId = CAN1_ID;//std_id;
//  TxMessage.RTR = CAN_RTR_DATA;
//  TxMessage.IDE = CAN_ID_STD;
//  TxMessage.DLC = 1;
//  
  /* Enable FIFO 0 message pending Interrupt */
  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}
#endif


int CAN1_SendData_ID(unsigned int id,char* data,int len)
{
	int i,num;
	CanTxMsg TxMessage;

	num=len/8+(((len%8)==0)?0:1);
	
 
   /* Transmit Structure preparation */
  TxMessage.StdId = id;
  TxMessage.ExtId = 0x01;
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.IDE = CAN_ID_STD;

	for(i=0;i<num;i++)
	{
		memcpy(TxMessage.Data,(char *)data+i*8,((len-i*8)>8)?8:(len-i*8));
		TxMessage.DLC = ((len-i*8)>8)?8:(len-i*8);
		while(CAN_Transmit(CAN1, &TxMessage)==CAN_TxStatus_NoMailBox)
		{
			Delay(1);
		}
	}
	
	return SUCCESS;
}

int CAN1_SendData(char* data,int len)
{
	int i,num;
	CanTxMsg TxMessage;

	num=len/8+(((len%8)==0)?0:1);
	
 
   /* Transmit Structure preparation */
  TxMessage.StdId = ((CAN_MASTER_ADDR+1)<<8)|(Self_Can_Addr&0x07);
  TxMessage.ExtId = 0x01;
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.IDE = CAN_ID_STD;

	for(i=0;i<num;i++)
	{
		memcpy(TxMessage.Data,(char *)data+i*8,((len-i*8)>8)?8:(len-i*8));
		TxMessage.DLC = ((len-i*8)>8)?8:(len-i*8);
		while(CAN_Transmit(CAN1, &TxMessage)==CAN_TxStatus_NoMailBox)
		{
			Delay(1);
		}
	}
	
	return SUCCESS;
}



