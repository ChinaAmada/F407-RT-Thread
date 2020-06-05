
#include "config.h"

//ads
#define RTD_ADSX_SYS_LIQUID   		1 //ads1£∫œ¥’Î“∫Œ¬∂»Õ®µ¿
#define RTD_ADSX_TRIG_LIQUID   		1 //ads1£∫º§∑¢“∫Œ¬∂»Õ®µ¿
#define RTD_ADSX_MAGCLEAN_LIQUID   	1 //ads1£∫¥≈÷È«Âœ¥“∫Œ¬∂»Õ®µ¿
#define RTD_ADSX_INCUBATE1   		1 //ads1£∫∑ı”˝≈Ãº”»»Œ¬∂»Õ®µ¿1
#define RTD_ADSX_INCUBATE2   		2 //ads2£∫∑ı”˝≈Ãº”»»Œ¬∂»Õ®µ¿2
#define RTD_ADSX_REAGENT   			2 //ads2£∫ ‘º¡≈Ã÷∆¿‰Œ¬∂»Õ®µ¿
#define RTD_ADSX_ENV   				2 //ads2£∫’˚ª˙Œ¬∂»Õ®µ¿
#define RTD_ADSX_SCAN_WINDOW   		2 //ads2£∫∑¿÷πŒÌªØŒ¬∂»Õ®µ¿

#define RTD_CHANNEL_SYS_LIQUID   		1 //ads1£∫œ¥’Î“∫Œ¬∂»Õ®µ¿
#define RTD_CHANNEL_TRIG_LIQUID   		2 //ads1£∫º§∑¢“∫Œ¬∂»Õ®µ¿
#define RTD_CHANNEL_MAGCLEAN_LIQUID   	3 //ads1£∫¥≈÷È«Âœ¥“∫Œ¬∂»Õ®µ¿
#define RTD_CHANNEL_INCUBATE1   		4 //ads1£∫∑ı”˝≈Ãº”»»Œ¬∂»Õ®µ¿1
#define RTD_CHANNEL_INCUBATE2   		1 //ads2£∫∑ı”˝≈Ãº”»»Œ¬∂»Õ®µ¿2
#define RTD_CHANNEL_REAGENT   			2 //ads2£∫ ‘º¡≈Ã÷∆¿‰Œ¬∂»Õ®µ¿
#define RTD_CHANNEL_ENV   				3 //ads2£∫’˚ª˙Œ¬∂»Õ®µ¿
#define RTD_CHANNEL_SCAN_WINDOW   		4 //ads2£∫∑¿÷πŒÌªØŒ¬∂»Õ®µ¿


#define TIM_NUM_REAGENT1   				TIM3 //TIMx£∫ ‘º¡≈ÃŒ¬∂»Õ®µ¿
#define TIM_NUM_REAGENT2   				TIM3 //TIMx£∫ ‘º¡≈ÃŒ¬∂»Õ®µ¿
#define TIM_NUM_REAGENT3   				TIM3 //TIMx£∫ ‘º¡≈ÃŒ¬∂»Õ®µ¿
#define TIM_NUM_SYS_LIQUID   			TIM4 //TIMx£∫œ¥’Î“∫Œ¬∂»Õ®µ¿
#define TIM_NUM_TRIG_LIQUID   			TIM4 //TIMx£∫º§∑¢“∫Œ¬∂»Õ®µ¿
#define TIM_NUM_MAGCLEAN_LIQUID   		TIM4 //TIMx£∫¥≈÷È«Âœ¥“∫Œ¬∂»Õ®µ¿
#define TIM_NUM_INCUBATE   				TIM4 //TIMx£∫∑ı”˝≈Ãº”»»Œ¬∂»Õ®µ

#define TIM_CHANNEL_INCUBATE     		1 //ads1£∫∑ı”˝≈Ãº”»»Œ¬∂»Õ®µ
#define TIM_CHANNEL_MAGCLEAN_LIQUID     2 //ads1£∫∑ı”˝≈Ãº”»»Œ¬∂»Õ®µ
#define TIM_CHANNEL_TRIG_LIQUID     	3 //ads1£∫∑ı”˝≈Ãº”»»Œ¬∂»Õ®µ
#define TIM_CHANNEL_SYS_LIQUID      	4 //ads1£∫∑ı”˝≈Ãº”»»Œ¬∂»Õ®µ
#define TIM_CHANNEL_REAGENT1     		1 //ads1£∫∑ı”˝≈Ãº”»»Œ¬∂»Õ®µ
#define TIM_CHANNEL_REAGENT2     		2 //ads1£∫∑ı”˝≈Ãº”»»Œ¬∂»Õ®µ
#define TIM_CHANNEL_REAGENT3     		3 //ads1£∫∑ı”˝≈Ãº”»»Œ¬∂»Õ®µ

#define TASK_STACKSIZE			512	//’ª¥Û–°
#define TASK_PRIORITY			3		//”≈œ»º∂
#define TASK_WAITTICK			10		//Õ¨”≈œ»º∂µ»¥˝ ±º‰ticks


typedef struct _PWM_PLUSE{
	uint32_t  Period;
	uint8_t   Duty;
}PWM_PLUSE;
static PWM_PLUSE Simulate_PWM_Cycle={100,50};


static __IO uint32_t uwTimingDelay;
RCC_ClocksTypeDef RCC_Clocks;
/* SPI ª•≥‚À¯ */
static struct rt_mutex SPI_Mutex;
struct rt_semaphore Can1_Rx_Sem; 
static ADC_VAL Adc_Vals;


void Nvic_Init(void);

static void task1_thread(void *parameter);		//∑ı”˝≈Ã
static void task2_thread(void *parameter);		//÷∆¿‰ ‘º¡≈Ã
static void task3_thread(void *parameter);		//œ¥’Î“∫º”»»
static void task4_thread(void *parameter);		//º§∑¢“∫º”»»
static void task5_thread(void *parameter);		//¥≈÷È«Âœ¥“∫º”»»
static void task6_thread(void *parameter);		//’˚ª˙°¢∑¿ŒÌ∆¯
static void task7_thread(void *parameter);		//CAN–≠“È¥¶¿Ì
static void task8_thread(void *parameter);		//ADC

//static rt_timer_t timer_PWM;	//soft pwm
	
void Creat_Task(void)
{
	rt_thread_t thread;
	
	thread = rt_thread_create("task1_thread", task1_thread, RT_NULL, TASK_STACKSIZE, TASK_PRIORITY, TASK_WAITTICK);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create task1_thread thread failed!\n");
    }
	
	thread = rt_thread_create("task2_thread", task2_thread, RT_NULL, TASK_STACKSIZE, TASK_PRIORITY, TASK_WAITTICK);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create task2_thread thread failed!\n");
    }
	
	thread = rt_thread_create("task3_thread", task3_thread, RT_NULL, TASK_STACKSIZE, TASK_PRIORITY, TASK_WAITTICK);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create task3_thread thread failed!\n");
    }
	
	thread = rt_thread_create("task4_thread", task4_thread, RT_NULL, TASK_STACKSIZE, TASK_PRIORITY, TASK_WAITTICK);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create task4_thread thread failed!\n");
    }
	
	thread = rt_thread_create("task5_thread", task5_thread, RT_NULL, TASK_STACKSIZE, TASK_PRIORITY, TASK_WAITTICK);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create task5_thread thread failed!\n");
    }
	
	thread = rt_thread_create("task6_thread", task6_thread, RT_NULL, TASK_STACKSIZE, TASK_PRIORITY, TASK_WAITTICK);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create task6_thread thread failed!\n");
    }
	
	thread = rt_thread_create("task7_thread", task7_thread, RT_NULL, TASK_STACKSIZE, TASK_PRIORITY, TASK_WAITTICK);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create task7_thread thread failed!\n");
    }
	
	thread = rt_thread_create("task8_thread", task8_thread, RT_NULL, 2*TASK_STACKSIZE, TASK_PRIORITY, TASK_WAITTICK);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create task8_thread thread failed!\n");
    }
	
//	
//	timer_PWM = rt_timer_create("timer1",timer_PWM_Handler,RT_NULL,RT_TICK_PER_SECOND/1000,RT_TIMER_FLAG_PERIODIC|RT_TIMER_FLAG_SOFT_TIMER);
//	if(timer_PWM != RT_NULL) 
//	{
//		rt_timer_start(timer_PWM);
//	}
}

int main(void)
{
	rt_err_t result;
	//char str[100];

	
	DO_Config();
	DO_Contrl(BUZZER_PORT,BUZZER_PIN,SET);
	rt_thread_mdelay(500);
	DO_Contrl(BUZZER_PORT,BUZZER_PIN,RESET);
	CAN1_Config();
	ADC_All_Config();
	
	TIM1_Config();
	TIM2_Config();
	TIM4_Config(TIME_1000HZ_PRESCALER,TIME_1000HZ_PERIOD);
	TIM_Set_Duty(TIM4,1,100);
	TIM_Set_Duty(TIM4,2,100);
	TIM_Set_Duty(TIM4,3,100);
	TIM_Set_Duty(TIM4,4,100);
	TIM3_Config(TIME_1000HZ_PRESCALER,TIME_1000HZ_PERIOD);
	TIM_Set_Duty(TIM3,1,100);
	TIM_Set_Duty(TIM3,2,100);
	TIM_Set_Duty(TIM3,3,100);
	
	
	SPI_Soft_Configuration(SPI3);
	Ads_Init(1);
	Ads_Init(2);
	PID_Init();
	 
    result = rt_mutex_init(&SPI_Mutex, "SPI_Mutex", RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        rt_kprintf("init SPI_Mutex mutex failed.\n");
        return -1;
	}
	result = rt_sem_init(&Can1_Rx_Sem, "Can1_Rx_Sem", 0, RT_IPC_FLAG_FIFO);
	if (result != RT_EOK)
    {
        rt_kprintf("init Can1_Rx_Sem  failed.\n");
        return -1;
	}
	
	Creat_Task();
	
	/* Infinite loop */
	while (1)
	{
		rt_thread_mdelay(500);
		LED_Flash();
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

/*
void Delay(__IO uint32_t nTime)
{ 
  uwTimingDelay = nTime;

  while(uwTimingDelay != 0);
}
*/


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


//∑ı”˝≈Ã
static void task1_thread(void *parameter)
{
	rt_err_t ret;
	float RTD1=0,RTD2=0;
//	char str[100];
	while(1)
	{
		rt_thread_mdelay(1000);
		ret = rt_mutex_take(&SPI_Mutex,1000);
		if(ret==-RT_ETIMEOUT){
			rt_kprintf("task1_thread take SPI_Mutex timeout\n");
			continue;
		}else if(ret!=RT_EOK){
			rt_kprintf("task1_thread take SPI_Mutex err,ret=%d\n",ret);
			continue;
		}
		
		RTD1=Ads_Read_Temp(RTD_ADSX_INCUBATE1,RTD_CHANNEL_INCUBATE1);
		RTD2=Ads_Read_Temp(RTD_ADSX_INCUBATE2,RTD_CHANNEL_INCUBATE2);
		RTD1=RTD1;
		rt_mutex_release(&SPI_Mutex);
		
		PID_Incubate.ActualVal=RTD2;//(RTD1+RTD2)/2;	
		
		//Œ¬∂»≤π≥•
		if(PID_Env.ActualVal<(float)20.0)
		{
			PID_Incubate.ActualVal -= (float)0.5;
		}else if(PID_Env.ActualVal<(float)23.0){
			PID_Incubate.ActualVal -= (float)0.2;
		}
		
		PostionPIDCalc(&PID_Incubate);
			
		TIM_Set_Duty(TIM_NUM_INCUBATE,TIM_CHANNEL_INCUBATE,100*(TIME_1000HZ_PERIOD-PID_Incubate.OutVal)/TIME_1000HZ_PERIOD);
		
		//Simulate_PWM_Cycle.Duty=100*(PID_Incubate.OutVal)/TIME_1000HZ_PERIOD;	//µ˜’˚∑Á…»◊™ÀŸ,≤‚ ‘”√
	
	}
}


//÷∆¿‰ ‘º¡≈Ã
static void task2_thread(void *parameter)
{
	rt_err_t ret;
//	char str[100];
	
	
	DO_Contrl(DO1_PORT,DO1_PIN,SET);//—≠ª∑±√
	DO_Contrl(DO2_PORT,DO2_PIN,SET);//…¢»»–°∑Á…»£¨ ‘º¡≈Ãµ◊œ¬µƒ∑Á…»
	DO_Contrl(DO3_PORT,DO3_PIN,SET);//¿‰»¥∑Á…»£¨¥Û∑Á…»
	DO_Contrl(DO4_PORT,DO4_PIN,SET);//’˚ª˙—≠ª∑∑Á…»
	while(1)
	{
		rt_thread_mdelay(1000);
		ret = rt_mutex_take(&SPI_Mutex,1000);
		if(ret==-RT_ETIMEOUT){
			rt_kprintf("task2_thread take SPI_Mutex timeout\n");
			continue;
		}else if(ret!=RT_EOK){
			rt_kprintf("task2_thread take SPI_Mutex err,ret=%d\n",ret);
			continue;
		}
		
		PID_Reagent.ActualVal=Ads_Read_Temp(RTD_ADSX_REAGENT,RTD_CHANNEL_REAGENT);
		rt_mutex_release(&SPI_Mutex);
		
		PostionPIDCalc(&PID_Reagent);

		//TIM_Set_Duty(TIM4,1,100*(TIME_1000HZ_PERIOD-PID_Reagent.OutVal)/TIME_1000HZ_PERIOD);
		TIM_Set_Duty(TIM_NUM_REAGENT1,TIM_CHANNEL_REAGENT1,100*(-PID_Reagent.OutVal)/TIME_1000HZ_PERIOD);
		TIM_Set_Duty(TIM_NUM_REAGENT2,TIM_CHANNEL_REAGENT2,100*(-PID_Reagent.OutVal)/TIME_1000HZ_PERIOD);
		TIM_Set_Duty(TIM_NUM_REAGENT3,TIM_CHANNEL_REAGENT3,100*(-PID_Reagent.OutVal)/TIME_1000HZ_PERIOD);
		
		Simulate_PWM_Cycle.Duty=100*(-PID_Reagent.OutVal)/TIME_1000HZ_PERIOD;	//µ˜’˚∑Á…»◊™ÀŸ
		
	}
}


//œ¥’Î“∫º”»»
static void task3_thread(void *parameter)
{
	rt_err_t ret;
//	char str[100];
	while(1)
	{
		rt_thread_mdelay(1000);
		ret = rt_mutex_take(&SPI_Mutex,1000);
		if(ret==-RT_ETIMEOUT){
			rt_kprintf("task3_thread take SPI_Mutex timeout\n");
			continue;
		}else if(ret!=RT_EOK){
			rt_kprintf("task3_thread take SPI_Mutex err,ret=%d\n",ret);
			continue;
		}
		
		PID_SysLiquid.ActualVal=Ads_Read_Temp(RTD_ADSX_SYS_LIQUID,RTD_CHANNEL_SYS_LIQUID);
		rt_mutex_release(&SPI_Mutex);
		
		PostionPIDCalc(&PID_SysLiquid);
		
		TIM_Set_Duty(TIM_NUM_SYS_LIQUID,TIM_CHANNEL_SYS_LIQUID,100*(TIME_1000HZ_PERIOD-PID_SysLiquid.OutVal)/TIME_1000HZ_PERIOD);
		
	}
}



//º§∑¢“∫º”»»
static void task4_thread(void *parameter)
{
	rt_err_t ret;
//	char str[100];
	while(1)
	{
		rt_thread_mdelay(1000);
		ret = rt_mutex_take(&SPI_Mutex,1000);
		if(ret==-RT_ETIMEOUT){
			rt_kprintf("task4_thread take SPI_Mutex timeout\n");
			continue;
		}else if(ret!=RT_EOK){
			rt_kprintf("task4_thread take SPI_Mutex err,ret=%d\n",ret);
			continue;
		}
		
		PID_TrigLiquid.ActualVal=Ads_Read_Temp(RTD_ADSX_TRIG_LIQUID,RTD_CHANNEL_TRIG_LIQUID);
		rt_mutex_release(&SPI_Mutex);

		PostionPIDCalc(&PID_TrigLiquid);
		
		TIM_Set_Duty(TIM_NUM_TRIG_LIQUID,TIM_CHANNEL_TRIG_LIQUID,100*(TIME_1000HZ_PERIOD-PID_TrigLiquid.OutVal)/TIME_1000HZ_PERIOD);
		
	}
}



//¥≈÷È«Âœ¥“∫º”»»
static void task5_thread(void *parameter)
{
	rt_err_t ret;
//	char str[100];
	while(1)
	{
		rt_thread_mdelay(1000);
		ret = rt_mutex_take(&SPI_Mutex,1000);
		if(ret==-RT_ETIMEOUT){
			rt_kprintf("task5_thread take SPI_Mutex timeout\n");
			continue;
		}else if(ret!=RT_EOK){
			rt_kprintf("task5_thread take SPI_Mutex err,ret=%d\n",ret);
			continue;
		}
		
		PID_MagClean.ActualVal=Ads_Read_Temp(RTD_ADSX_MAGCLEAN_LIQUID,RTD_CHANNEL_MAGCLEAN_LIQUID);
		rt_mutex_release(&SPI_Mutex);
		
		PostionPIDCalc(&PID_MagClean);
		
		TIM_Set_Duty(TIM_NUM_MAGCLEAN_LIQUID,TIM_CHANNEL_MAGCLEAN_LIQUID,100*(TIME_1000HZ_PERIOD-PID_MagClean.OutVal)/TIME_1000HZ_PERIOD);
		
	}
}


//’˚ª˙ ∑¿ŒÌ∆¯
static void task6_thread(void *parameter)
{
	rt_err_t ret;
//	char str[100];
	while(1)
	{
		rt_thread_mdelay(1000);
		ret = rt_mutex_take(&SPI_Mutex,1000);
		if(ret==-RT_ETIMEOUT){
			rt_kprintf("task6_thread take SPI_Mutex timeout\n");
			continue;
		}else if(ret!=RT_EOK){
			rt_kprintf("task6_thread take SPI_Mutex err,ret=%d\n",ret);
			continue;
		}
		
		PID_Env.ActualVal=Ads_Read_Temp(RTD_ADSX_ENV,RTD_CHANNEL_ENV);
		PID_Scan_Window.ActualVal=Ads_Read_Temp(RTD_ADSX_SCAN_WINDOW,RTD_CHANNEL_SCAN_WINDOW);
		
		rt_mutex_release(&SPI_Mutex);
	}
}

extern CAN_RX_BUF Can1_Rx_Buff;
static void task7_thread(void *parameter)
{
	rt_err_t ret;
	Ack_Data sdata;
	Ctrl_Data* p_Data;
	while(1)
	{
		//rt_thread_mdelay(1000);
		
		ret = rt_sem_take(&Can1_Rx_Sem,1000);
		if(ret==-RT_ETIMEOUT){
//			rt_kprintf("task7_thread take Can1_Rx_Sem timeout\n");
			continue;
		}else if(ret!=RT_EOK){
			rt_kprintf("task7_thread take Can1_Rx_Sem err,ret=%d\n",ret);
			continue;
		}
		

		if(Can1_Rx_Buff.len>=sizeof(Ctrl_Data))
		{
			if((ret=Check_Ack(Can1_Rx_Buff.buff,Can1_Rx_Buff.len))<0)
			{
				Can1_Rx_Buff.len = 0;
				continue;
			}
			p_Data = (Ctrl_Data*)(Can1_Rx_Buff.buff);
			if(p_Data->cmd == (char)CMD_COLD_HOT_GET_TMP)
			{
				Make_Ack_Data(&sdata,Get_CAN1_Addr(),CMD_COLD_HOT_GET_TMP,SLAVE_TYPE_ACK,0);
				CAN1_SendData_ID(0x100|Get_CAN1_Addr(),(char*)&sdata,sizeof(Ack_Data));
				
				Make_Ack_Data(&sdata,Get_CAN1_Addr(),CMD_COLD_HOT_GET_TMP,1,PID_SysLiquid.ActualVal);
				CAN1_SendData_ID(0x100|Get_CAN1_Addr(),(char*)&sdata,sizeof(Ack_Data));
				Make_Ack_Data(&sdata,Get_CAN1_Addr(),CMD_COLD_HOT_GET_TMP,2,PID_TrigLiquid.ActualVal);
				CAN1_SendData_ID(0x100|Get_CAN1_Addr(),(char*)&sdata,sizeof(Ack_Data));
				Make_Ack_Data(&sdata,Get_CAN1_Addr(),CMD_COLD_HOT_GET_TMP,3,PID_MagClean.ActualVal);
				CAN1_SendData_ID(0x100|Get_CAN1_Addr(),(char*)&sdata,sizeof(Ack_Data));
				Make_Ack_Data(&sdata,Get_CAN1_Addr(),CMD_COLD_HOT_GET_TMP,4,PID_Incubate.ActualVal);
				CAN1_SendData_ID(0x100|Get_CAN1_Addr(),(char*)&sdata,sizeof(Ack_Data));
				Make_Ack_Data(&sdata,Get_CAN1_Addr(),CMD_COLD_HOT_GET_TMP,5,PID_Incubate.ActualVal);
				CAN1_SendData_ID(0x100|Get_CAN1_Addr(),(char*)&sdata,sizeof(Ack_Data));
				Make_Ack_Data(&sdata,Get_CAN1_Addr(),CMD_COLD_HOT_GET_TMP,6,PID_Reagent.ActualVal);
				CAN1_SendData_ID(0x100|Get_CAN1_Addr(),(char*)&sdata,sizeof(Ack_Data));
				Make_Ack_Data(&sdata,Get_CAN1_Addr(),CMD_COLD_HOT_GET_TMP,7,PID_Env.ActualVal);
				CAN1_SendData_ID(0x100|Get_CAN1_Addr(),(char*)&sdata,sizeof(Ack_Data));
				Make_Ack_Data(&sdata,Get_CAN1_Addr(),CMD_COLD_HOT_GET_TMP,8,PID_Scan_Window.ActualVal);
				CAN1_SendData_ID(0x100|Get_CAN1_Addr(),(char*)&sdata,sizeof(Ack_Data));
				
				Make_Ack_Data(&sdata,Get_CAN1_Addr(),CMD_COLD_HOT_GET_TMP,SLAVE_TYPE_SUCCESS,0);
				CAN1_SendData_ID(0x100|Get_CAN1_Addr(),(char*)&sdata,sizeof(Ack_Data));
			}else if(p_Data->cmd == (char)CMD_COLD_HOT_SET_TMP){
				Make_Ack_Data(&sdata,Get_CAN1_Addr(),CMD_COLD_HOT_SET_TMP,SLAVE_TYPE_ACK,0);
				CAN1_SendData_ID(0x100|Get_CAN1_Addr(),(char*)&sdata,sizeof(Ack_Data));
				
				
				
				switch(*(uint32_t*)(p_Data->para1)){
					case SET_PID_CHANNEL_INCUBATE:
						PID_Incubate.SetVal=*(float*)(p_Data->para1);
						break;
					case SET_PID_CHANNEL_REAGENT:
						PID_Reagent.SetVal=*(float*)(p_Data->para1);
						break;
					case SET_PID_CHANNEL_SYSLIQUID:
						PID_TrigLiquid.SetVal=*(float*)(p_Data->para1);
						break;
					case SET_PID_CHANNEL_TRIGLIQUID:
						PID_SysLiquid.SetVal=*(float*)(p_Data->para1);
						break;
					case SET_PID_CHANNEL_MAGCLEAN:
						PID_MagClean.SetVal=*(float*)(p_Data->para1);
						break;
					default:
						
						break;
				}
				
				if((*(uint32_t*)(p_Data->para1))>=SET_PID_CHANNEL_INCUBATE&&(*(uint32_t*)(p_Data->para1))<=SET_PID_CHANNEL_MAGCLEAN)
				{
					Make_Ack_Data(&sdata,Get_CAN1_Addr(),CMD_COLD_HOT_SET_TMP,SLAVE_TYPE_SUCCESS,0);
					CAN1_SendData_ID(0x100|Get_CAN1_Addr(),(char*)&sdata,sizeof(Ack_Data));
				}else{
					Make_Ack_Data(&sdata,Get_CAN1_Addr(),CMD_COLD_HOT_SET_TMP,SLAVE_TYPE_FAIL,0);
					CAN1_SendData_ID(0x100|Get_CAN1_Addr(),(char*)&sdata,sizeof(Ack_Data));
				}
			}
		}	
	}
}


//ADC
static void task8_thread(void *parameter)
{
//	char str[100];
	float tmp_vol=0;
	uint8_t i=0;
//	uint8_t j=0,k=0;
	while(1)
	{
		rt_thread_mdelay(1);

//		DO_Toggle(DO1_2_DS_PORT,DO1_2_DS_PIN);
//		DO_Toggle(DO3_4_DS_PORT,DO3_4_DS_PIN);
//		DO_Toggle(DO5_6_DS_PORT,DO5_6_DS_PIN);
//		
		if(i<FILTER_NUM){
			DO_Contrl(DO1_2_DS_PORT,DO1_2_DS_PIN,RESET);
			DO_Contrl(DO3_4_DS_PORT,DO3_4_DS_PIN,RESET);
			DO_Contrl(DO5_6_DS_PORT,DO5_6_DS_PIN,RESET);
		}else{
			DO_Contrl(DO1_2_DS_PORT,DO1_2_DS_PIN,SET);
			DO_Contrl(DO3_4_DS_PORT,DO3_4_DS_PIN,SET);
			DO_Contrl(DO5_6_DS_PORT,DO5_6_DS_PIN,SET);
		}
		
		//rt_thread_mdelay(1);
		
		ADC_SoftwareStartConv(ADC1);	//ø™∆Ù“ª¥ŒADC

		while(DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0)!=RESET)
		{
			//sprintf(str,"ch[1]=%f,ch[2]=%f,ch[3]=%f,ch[4]=%f\r\n",(float)(ADC_Result[0]*2.5/4096),(float)(ADC_Result[1]*2.5/4096),(float)(ADC_Result[2]*2.5/4096),(float)(ADC_Result[3]*2.5/4096));
			//rt_kprintf("%s",str);

//			if(GPIO_ReadOutputDataBit(DO5_6_DS_PORT,DO5_6_DS_PIN)==RESET)
			if(i<FILTER_NUM)
			{
				tmp_vol	= (float)(ADC_Result[0]*REF_VOLTAGE/4096);
				Adc_Vals.Ch0_Valve5_IS[i]	= (tmp_vol>(float)REF_VOLTAGE)?Adc_Vals.Ch0_Valve5_IS[i]:tmp_vol;
			}else{
				tmp_vol	= (float)(ADC_Result[0]*REF_VOLTAGE/4096);
				Adc_Vals.Ch0_Valve6_IS[i-FILTER_NUM]	= (tmp_vol>(float)REF_VOLTAGE)?Adc_Vals.Ch0_Valve6_IS[i]:tmp_vol;
			}
			
			Adc_Vals.Ch1_3V3_ADC		= (float)(ADC_Result[1]*PRE_VOLTAGE*REF_VOLTAGE/4096);
			Adc_Vals.Ch2_24V_ADC		= (float)(ADC_Result[2]*PRE_VOLTAGE*REF_VOLTAGE/4096);
			Adc_Vals.Ch3_5V_ADC			= (float)(ADC_Result[3]*PRE_VOLTAGE*REF_VOLTAGE/4096);
			Adc_Vals.Ch4_Heat1_Iout		= (float)(ADC_Result[4]*REF_VOLTAGE/4096);
			Adc_Vals.Ch5_Heat2_Iout		= (float)(ADC_Result[5]*REF_VOLTAGE/4096);
			Adc_Vals.Ch6_Heat3_Iout		= (float)(ADC_Result[6]*REF_VOLTAGE/4096);
			Adc_Vals.Ch7_Heat4_Iout		= (float)(ADC_Result[7]*REF_VOLTAGE/4096);
			
//			if(GPIO_ReadOutputDataBit(DO1_2_DS_PORT,DO1_2_DS_PIN)==RESET)
			if(i<FILTER_NUM)
			{
				tmp_vol	= (float)(ADC_Result[8]*REF_VOLTAGE/4096);
				Adc_Vals.Ch8_Valve1_IS[i]	= (tmp_vol>(float)REF_VOLTAGE)?Adc_Vals.Ch8_Valve1_IS[i]:tmp_vol;
			}else{
				tmp_vol	= (float)(ADC_Result[8]*REF_VOLTAGE/4096);
				Adc_Vals.Ch8_Valve2_IS[i-FILTER_NUM]	= (tmp_vol>(float)REF_VOLTAGE)?Adc_Vals.Ch8_Valve2_IS[i]:tmp_vol;
			}
//			if(GPIO_ReadOutputDataBit(DO3_4_DS_PORT,DO3_4_DS_PIN)==RESET)
			if(i<FILTER_NUM)
			{
				tmp_vol	= (float)(ADC_Result[9]*REF_VOLTAGE/4096);
				Adc_Vals.Ch9_Valve3_IS[i]	= (tmp_vol>(float)REF_VOLTAGE)?Adc_Vals.Ch9_Valve3_IS[i]:tmp_vol;
			}else{
				tmp_vol	= (float)(ADC_Result[9]*REF_VOLTAGE/4096);
				Adc_Vals.Ch9_Valve4_IS[i-FILTER_NUM]	= (tmp_vol>(float)REF_VOLTAGE)?Adc_Vals.Ch9_Valve4_IS[i]:tmp_vol;
			}

			Adc_Vals.Ch10_TEC1_Iout		= (float)(ADC_Result[10]*REF_VOLTAGE/4096);
			Adc_Vals.Ch11_TEC2_Iout		= (float)(ADC_Result[11]*REF_VOLTAGE/4096);
			Adc_Vals.Ch12_TEC3_Iout		= (float)(ADC_Result[12]*REF_VOLTAGE/4096);
			
			
			i++;
			if(i>=2*FILTER_NUM)
			//if(i>=FILTER_NUM)
			{
				i=0;
				Adc_Vals.Ch8_Valve1_IS_Val=Average_Float(Adc_Vals.Ch8_Valve1_IS,FILTER_NUM);
				Adc_Vals.Ch8_Valve2_IS_Val=Average_Float(Adc_Vals.Ch8_Valve2_IS,FILTER_NUM);
				Adc_Vals.Ch9_Valve3_IS_Val=Average_Float(Adc_Vals.Ch9_Valve3_IS,FILTER_NUM);
				Adc_Vals.Ch9_Valve4_IS_Val=Average_Float(Adc_Vals.Ch9_Valve4_IS,FILTER_NUM);
				Adc_Vals.Ch0_Valve5_IS_Val=Average_Float(Adc_Vals.Ch0_Valve5_IS,FILTER_NUM);
				Adc_Vals.Ch0_Valve6_IS_Val=Average_Float(Adc_Vals.Ch0_Valve6_IS,FILTER_NUM);
				
			}			
			DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TCIF0);
		}	
		
		//rt_kprintf("freq1=%d,freq2=%d,freq3=%d\r\n",Freq_InputCapture[0],Freq_InputCapture[1],Freq_InputCapture[2]);
	}
}


static uint32_t cnt1=0;
//GPIO PWM,ª˘¥°∆µ¬ 10K
void TIM2_Update_Hook(void *parameter)
{

		cnt1++;
		if(cnt1<(Simulate_PWM_Cycle.Period*Simulate_PWM_Cycle.Duty/100)){
			DO_Contrl(DO3_PORT,DO3_PIN,SET);//¿‰»¥∑Á…»1
		}else if(cnt1>=(Simulate_PWM_Cycle.Period*Simulate_PWM_Cycle.Duty/100)&&cnt1<Simulate_PWM_Cycle.Period){
			DO_Contrl(DO3_PORT,DO3_PIN,RESET);//¿‰»¥∑Á…»1
		}else{
			cnt1=0;
		}
	
}

static void print_adc(void)
{
	char str[100];
	
	rt_kprintf("%-*.*s %10s\n", 2*RT_NAME_MAX, strlen("ADC CHANNEL"),"ADC CHANNEL","VAL");
	rt_kprintf("---------------- ----------\n");
	
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Ch0_Valve5_IS",Adc_Vals.Ch0_Valve5_IS_Val);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Ch0_Valve6_IS",Adc_Vals.Ch0_Valve6_IS_Val);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Ch1_3V3_ADC",Adc_Vals.Ch1_3V3_ADC);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Ch2_24V_ADC",Adc_Vals.Ch2_24V_ADC);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Ch3_5V_ADC",Adc_Vals.Ch3_5V_ADC);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Ch4_Heat1_Iout",Adc_Vals.Ch4_Heat1_Iout);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Ch5_Heat2_Iout",Adc_Vals.Ch5_Heat2_Iout);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Ch6_Heat3_Iout",Adc_Vals.Ch6_Heat3_Iout);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Ch7_Heat4_Iout",Adc_Vals.Ch7_Heat4_Iout);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Ch8_Valve1_IS",Adc_Vals.Ch8_Valve1_IS_Val);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Ch8_Valve2_IS",Adc_Vals.Ch8_Valve2_IS_Val);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Ch9_Valve3_IS",Adc_Vals.Ch9_Valve3_IS_Val);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Ch9_Valve4_IS",Adc_Vals.Ch9_Valve4_IS_Val);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Ch10_TEC1_Iout",Adc_Vals.Ch10_TEC1_Iout);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Ch11_TEC2_Iout",Adc_Vals.Ch11_TEC2_Iout);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Ch12_TEC3_Iout",Adc_Vals.Ch12_TEC3_Iout);
	rt_kprintf("%s",str);
	/*
	sprintf(str,"Ch0_Valve5_IS=%f\r\n",Adc_Vals.Ch0_Valve5_IS_Val);
	rt_kprintf("%s",str);
	sprintf(str,"Ch0_Valve6_IS=%f\r\n",Adc_Vals.Ch0_Valve6_IS_Val);
	rt_kprintf("%s",str);
	sprintf(str,"Ch1_3V3_ADC=%f\r\n",Adc_Vals.Ch1_3V3_ADC);
	rt_kprintf("%s",str);
	sprintf(str,"Ch2_24V_ADC=%f\r\n",Adc_Vals.Ch2_24V_ADC);
	rt_kprintf("%s",str);
	sprintf(str,"Ch3_5V_ADC=%f\r\n",Adc_Vals.Ch3_5V_ADC);
	rt_kprintf("%s",str);
	sprintf(str,"Ch4_Heat1_Iout=%f\r\n",Adc_Vals.Ch4_Heat1_Iout);
	rt_kprintf("%s",str);
	sprintf(str,"Ch5_Heat2_Iout=%f\r\n",Adc_Vals.Ch5_Heat2_Iout);
	rt_kprintf("%s",str);
	sprintf(str,"Ch6_Heat3_Iout=%f\r\n",Adc_Vals.Ch6_Heat3_Iout);
	rt_kprintf("%s",str);
	sprintf(str,"Ch7_Heat4_Iout=%f\r\n",Adc_Vals.Ch7_Heat4_Iout);
	rt_kprintf("%s",str);
	sprintf(str,"Ch8_Valve1_IS=%f\r\n",Adc_Vals.Ch8_Valve1_IS_Val);
	rt_kprintf("%s",str);
	sprintf(str,"Ch8_Valve2_IS=%f\r\n",Adc_Vals.Ch8_Valve2_IS_Val);
	rt_kprintf("%s",str);
	sprintf(str,"Ch9_Valve3_IS=%f\r\n",Adc_Vals.Ch9_Valve3_IS_Val);
	rt_kprintf("%s",str);
	sprintf(str,"Ch9_Valve4_IS=%f\r\n",Adc_Vals.Ch9_Valve4_IS_Val);
	rt_kprintf("%s",str);
	sprintf(str,"Ch10_TEC1_Iout=%f\r\n",Adc_Vals.Ch10_TEC1_Iout);
	rt_kprintf("%s",str);
	sprintf(str,"Ch11_TEC2_Iout=%f\r\n",Adc_Vals.Ch11_TEC2_Iout);
	rt_kprintf("%s",str);
	sprintf(str,"Ch12_TEC3_Iout=%f\r\n",Adc_Vals.Ch12_TEC3_Iout);
	rt_kprintf("%s",str);
	*/
}




static void print_temp(void)
{
	char str[100];
	
	
	rt_kprintf("%-*.*s %10s\n", 2*RT_NAME_MAX, strlen("CHANNEL NAME"),"CHANNEL NAME","VAL");
	rt_kprintf("---------------- ----------\n");
	
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Incubate",PID_Incubate.ActualVal);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Reagent",PID_Reagent.ActualVal);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Sys Liquid",PID_SysLiquid.ActualVal);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Trig Liquid",PID_TrigLiquid.ActualVal);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"MagClean",PID_MagClean.ActualVal);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Environment",PID_Env.ActualVal);
	rt_kprintf("%s",str);
	sprintf(str,"%-*.*s %10.5f\n",2*RT_NAME_MAX,strlen("CHANNEL NAME"),"Scan Window",PID_Scan_Window.ActualVal);
	rt_kprintf("%s",str);
	

}





static void set_softPWM_duty(int argc, char**argv)
{
//	rt_kprintf("argc=%d,argv=%s\r\n",argc,argv);
	if(argc>1)
		Simulate_PWM_Cycle.Duty=atoi(argv[1]);
}
 

static void print_freq(void)
{
	//rt_kprintf("freq1=%d,freq2=%d,freq3=%d\r\n",Freq_InputCapture[0],Freq_InputCapture[1],Freq_InputCapture[2]);
	rt_kprintf("%-*.*s %6s\n", 2*RT_NAME_MAX, strlen("FREQ NAME"),"FREQ NAME","VAL");
	rt_kprintf("---------------- ------\n");
	rt_kprintf("%-*.*s %6d\n", 2*RT_NAME_MAX, strlen("FREQ NAME"),"freq1",Freq_InputCapture[0]);
	rt_kprintf("%-*.*s %6d\n", 2*RT_NAME_MAX, strlen("FREQ NAME"),"freq2",Freq_InputCapture[1]);
	rt_kprintf("%-*.*s %6d\n", 2*RT_NAME_MAX, strlen("FREQ NAME"),"freq3",Freq_InputCapture[2]);
	
	//”√ÕÍ«Â0£¨÷ÿ–¬º∆À„
	Freq_InputCapture[0]=0;
	Freq_InputCapture[1]=0;
	Freq_InputCapture[2]=0;
}
MSH_CMD_EXPORT(print_adc , print_adc);
MSH_CMD_EXPORT(print_temp , print_temp);
MSH_CMD_EXPORT(print_freq , print_freq);
MSH_CMD_EXPORT(set_softPWM_duty, set_softPWM_duty sample: 0-100);

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
