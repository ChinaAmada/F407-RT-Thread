

/* Includes ------------------------------------------------------------------*/
#include "config.h"


//static int Usart6_Index=0;
static int Usart6_Index_Head=0,Usart6_Index_Tail=0;
//static int Usart6_Buff_len=0;
static char Usart6_Buff[USART_BUFF_SIZE];
static FlagStatus Usart6_RecPack_Flag=RESET;


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/*
int Usart6_Push_Data(void)
{
	Usart6_Buff[Usart6_Index++]=USART_ReceiveData(USART6);
	Usart6_Index = Usart6_Index&USART_MASK;
	return SUCCESS;
}*/
  
int Usart6_Push_Char(void)
{
	Usart6_Buff[Usart6_Index_Head++]=USART_ReceiveData(USART6);
	Usart6_Index_Head = Usart6_Index_Head&USART_MASK;
	
	return SUCCESS;
}
int Usart6_Get_Char(char* ch)
{	
	if(Usart6_Index_Tail==Usart6_Index_Head)
		return ERROR;
	*ch = Usart6_Buff[Usart6_Index_Tail++];
	Usart6_Index_Tail = Usart6_Index_Tail&USART_MASK;
	return SUCCESS;
}

/*
int Usart6_Read_Data(char* data,int* len)
{
	int i;
	
	for(i=0;i<Usart6_Buff_len;i++)
	{
			data[i]=Usart6_Buff[i];
	}
	
	*len = Usart6_Buff_len;
	return SUCCESS;
}
*/
/*
int Usart6_Set_RecPack_Flag(void)
{
	Usart6_RecPack_Flag=SET;
	Usart6_Buff_len=Usart6_Index;
	Usart6_Index=0;

	return SUCCESS;
}
*/
int Usart6_Clear_RecPack_Flag(void)
{
	Usart6_RecPack_Flag=RESET;
	
	return SUCCESS;
}
	
int Usart6_Read_RecPack_Flag(void)
{
	return Usart6_RecPack_Flag;
}

/**
  * @brief  Configures the USART Peripheral.
  * @param  None
  * @retval None
  */
void USART_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);
	/*
	*  USART2_TX -> PD5 , USART2_RX -PD6
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/*
	USARTx configured as follow:
	- BaudRate = 115200 baud  
	- Word Length = 8 Bits
	- One Stop Bit
	- No parity
	- Hardware flow control disabled (RTS and CTS signals)
	- Receive and transmit    
	*/

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART6, &USART_InitStructure);
	/* Enable the Open_USART Transmit interrupt: this interrupt is generated when the 
	Open_USART transmit data register is empty */
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//USART_ITConfig(USART6,USART_IT_RXNE,DISABLE);
	USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART6, ENABLE);
}








/********** ??????? **********/
#pragma import(__use_no_semihosting)
 
struct __FILE
{
	int a;
};
 
FILE __stdout;
 
void _sys_exit(int x)
{
	
}


/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
//???fputc??
int fputc(int ch, FILE *f)
{        
		char c=(u8)ch;
        //while((USART6->SR&0X40)==0);//????,??????   
        //USART6->DR = (u8) ch;      

		Usart_Send_Data(USART6,&c,1);
        return ch;
}




void USART6_Config(u32 bound){
  //GPIO????
				GPIO_InitTypeDef GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;
        NVIC_InitTypeDef NVIC_InitStructure;
       
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //??GPIOA??
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//??USART1??

        //??1????????
        GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6); //GPIOA9???USART1
        GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6); //GPIOA10???USART1
       
        //USART1????
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //GPIOA9?GPIOA10
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//????
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //??50MHz
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //??????
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //??
        GPIO_Init(GPIOC,&GPIO_InitStructure); //???PA9,PA10

   //USART1 ?????
        USART_InitStructure.USART_BaudRate = bound;//?????
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;//???8?????
        USART_InitStructure.USART_StopBits = USART_StopBits_1;//?????
        USART_InitStructure.USART_Parity = USART_Parity_No;//??????
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//????????
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;        //????
				USART_Init(USART6, &USART_InitStructure); //?????1
       
				USART_Cmd(USART6, ENABLE);  //????1
       
        USART_ClearFlag(USART6, USART_FLAG_TC);
          
				USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);
        USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);//??????

        //Usart1 NVIC ??
				NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;//??1????
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//?????3
        NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;                //????3
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                        //IRQ????
        NVIC_Init(&NVIC_InitStructure);        //??????????VIC????
}



int Usart_Send_Data(USART_TypeDef* USARTx,char* data,int len)
{
	int i;
	
	for(i=0;i<len;i++)
	{
		while(USART_GetFlagStatus(USART6, USART_FLAG_TC)== RESET)
			;
		USART_SendData(USARTx,(uint16_t)data[i]);
	}
	return SUCCESS;
}


/*
void USART6_IRQHandler(void)                        //??1??????
{
        u8 Res;

        if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)  //????(?????????0x0d 0x0a??)
        {
                Res =USART_ReceiveData(USART6);//(USART1->DR);        //????????
                USART_SendData(USART6, Res);//(Res);
                   
  }

}
*/


void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;
    char a = '\r';

    size = rt_strlen(str);
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
			Usart_Send_Data(USART6,(uint8_t *)&a,1);
            //HAL_UART_Transmit(&UartHandle, (uint8_t *)&a, 1, 1);
        }
		Usart_Send_Data(USART6,(uint8_t *)(str + i),1);
        //HAL_UART_Transmit(&UartHandle, (uint8_t *)(str + i), 1, 1);
    }
}

int rt_hw_console_getchar(void)
{
	/*
    int ch = -1;

    if (__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_RXNE) != RESET)
    {
        ch = UartHandle.Instance->DR & 0xff;
    }
    else
    {
        if(__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_ORE) != RESET)
        {
            __HAL_UART_CLEAR_OREFLAG(&UartHandle);
        }
        rt_thread_mdelay(10);
    }
    return ch;
	*/
	char ch;
	if(Usart6_Get_Char(&ch)==SUCCESS)
	{
		return ch;
	}
	
	return -1;
}

/********************************  RT-THREAD  console  **************************************/

static int uart_init(void)
{
	USART_Config();
	return 1;
}


INIT_BOARD_EXPORT(uart_init);












/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
