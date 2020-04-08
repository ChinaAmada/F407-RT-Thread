
#include "config.h"


static __IO uint32_t uwTimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

void Nvic_Init(void);
static void uart6_tx_thread(void *parameter);

int main(void)
{
	CanRxMsg Can_Tmp_Rx_Msg;
	DATA_FRAME* p_Data;
	rt_thread_t thread;
 

	/* SysTick end of count event each 10ms */
	//RCC_GetClocksFreq(&RCC_Clocks);
	//Nvic_Init();
	//SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
  
	/* Add your application code here */
	/* Insert 50 ms delay */
	
	//Delay(5);
	
	//Nvic_Init();
	GPIO_Config();
	//USART_Config();
	CAN1_Config();
	FLASH_If_Init();
	
	
	/* ???????? */
    thread = rt_thread_create("uart6_tx", uart6_tx_thread, RT_NULL, 1024, 3, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create can_rx thread failed!\n");
    }
	
	
	/* Infinite loop */
	while (1)
	{
		//USART_SendData(USART6, 'A');//printf("bootloader\r\n");
		//while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET)
		//{}
		//printf("application %s %s\r\n",__DATE__,__TIME__);
		GPIO_ToggleBits(GPIOC,GPIO_Pin_3);
		rt_thread_mdelay(500);
		
		
		if(CAN1_Read_Packet(&Can_Tmp_Rx_Msg)==TRUE)
		{
			;
		}
	}
}




void Nvic_Init(void)
{
	//NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x4000);
}


/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  uwTimingDelay = nTime;

  while(uwTimingDelay != 0);
}



/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (uwTimingDelay != 0x00)
  { 
    uwTimingDelay--;
  }
}

struct rt_semaphore can_rx_sem; 

static void uart6_tx_thread(void *parameter)
{
	CanRxMsg Can_Tmp_Rx_Msg;
	/* ??? CAN ????? */
    rt_sem_init(&can_rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
	
	while(1)
	{
		//printf("application %s %s\r\n",__DATE__,__TIME__);
		//CAN1_Send_ERR(1,1);
		//rt_thread_mdelay(500);
		rt_sem_take(&can_rx_sem, RT_WAITING_FOREVER);
		
		if(CAN1_Read_Packet(&Can_Tmp_Rx_Msg)==TRUE)
		{
			rt_kprintf("CAN1 RECV:%02x-%02x %02x %02x %02x %02x %02x %02x %02x",Can_Tmp_Rx_Msg.StdId,Can_Tmp_Rx_Msg.Data[0],\
			Can_Tmp_Rx_Msg.Data[1],Can_Tmp_Rx_Msg.Data[2],Can_Tmp_Rx_Msg.Data[3],Can_Tmp_Rx_Msg.Data[4],Can_Tmp_Rx_Msg.Data[5],Can_Tmp_Rx_Msg.Data[6],Can_Tmp_Rx_Msg.Data[7]);
		}else{
			rt_kprintf("CAN1 RECV:no");
		}
		
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
