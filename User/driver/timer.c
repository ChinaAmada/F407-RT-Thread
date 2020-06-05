

/* Includes ------------------------------------------------------------------*/
#include "config.h"

#define		TIM4_PORT		GPIOD
#define		TIM4_PINS		(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)

#define		INPUT_CAPTUR_CHANNLE_NUM		3
uint32_t Freq_InputCapture[INPUT_CAPTUR_CHANNLE_NUM]={0};


static TIM_TimeBaseInitTypeDef  TIM1_TimeBaseStructure;
static TIM_TimeBaseInitTypeDef  TIM2_TimeBaseStructure;
static TIM_TimeBaseInitTypeDef  TIM3_TimeBaseStructure;
static TIM_TimeBaseInitTypeDef  TIM4_TimeBaseStructure;

static TIM_OCInitTypeDef  TIM3_OCInitStructure;
static TIM_OCInitTypeDef  TIM4_OCInitStructure;

static TIM_ICInitTypeDef  TIM1_ICInitStructure;

/*
主频			：168MHZ
APB1分频系数	：4，42MHZ
TIM4的频率		：APB主频 *2 /(Prescaler+1)=84MHZ
Period			：定时器计数的数量

Prescaler		(100-1)		(100-1)		(10-1)		
Period			8400		840			8400
PWM clk			100			1000		1000
*/
void TIM3_Config(uint16_t Prescaler,uint16_t Period)
{
	//TIM_OCInitTypeDef  TIM3_OCInitStructure;
	//TIM_TimeBaseInitTypeDef  TIM3_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
		
	
	/* TIM4 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	
	/* GPIOC and GPIOB clock enable */	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 
	/* GPIOC Configuration: */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 	
	
	/* Connect TIM3 pins to AF2 */  
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);	
	
	
	
	//  uint16_t PrescalerValue = 0;
	/* Compute the prescaler value */
	//PrescalerValue = (uint16_t) ((SystemCoreClock/2) / TIM4_Freq) - 1;
	
	/* Time base configuration */
	TIM3_TimeBaseStructure.TIM_Period = Period;//Frequent3_Out;// TIM4->ARR寄存器确定输出频率 
	TIM3_TimeBaseStructure.TIM_Prescaler = Prescaler;
	TIM3_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM3_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM3_TimeBaseStructure);

	
	//   /* PWM1 Mode configuration: Channel1 */
	TIM3_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM3_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM3_OCInitStructure.TIM_Pulse = Period/2;  //0;//HEAT1_PWM_Duty;//占空比TIM4->CCR1寄存器确定输出占空比

	TIM_OC1Init(TIM3, &TIM3_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	//   /* PWM1 Mode configuration: Channel2 */
	TIM3_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM3_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM3_OCInitStructure.TIM_Pulse = Period/2;  //0;//HEAT2_PWM_Duty;//占空比TIM4->CCR2寄存器确定输出占空比

	TIM_OC2Init(TIM3, &TIM3_OCInitStructure);

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
//   /* PWM1 Mode configuration: Channel3 */
	TIM3_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM3_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM3_OCInitStructure.TIM_Pulse = Period/2;  //0;//HEAT3_PWM_Duty;//Frequent3_Out/2;//Frequent1_Out/2;//占空比TIM4->CCR4寄存器确定输出占空比

	TIM_OC3Init(TIM3, &TIM3_OCInitStructure);

	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);


//   /* PWM1 Mode configuration: Channel4 */
/*
	TIM3_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM3_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM3_OCInitStructure.TIM_Pulse = Period/2;  //0;//HEAT4_PWM_Duty;//占空比TIM4->CCR4寄存器确定输出占空比

	TIM_OC4Init(TIM3, &TIM3_OCInitStructure);

	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
*/	
	
	

	TIM_ARRPreloadConfig(TIM3, ENABLE);

	/* TIM4 enable counter */
	TIM_Cmd(TIM3, ENABLE);
}


/*
主频			：168MHZ
APB1分频系数	：4，42MHZ
TIM4的频率		：APB主频 *2 /(Prescaler+1)=84MHZ
Period			：定时器计数的数量

Prescaler		(100-1)		(100-1)		(10-1)		
Period			8400		840			8400
PWM clk			100			1000		1000
*/
void TIM4_Config(uint16_t Prescaler,uint16_t Period)
{
	//TIM_OCInitTypeDef  TIM4_OCInitStructure;
	//TIM_TimeBaseInitTypeDef  TIM4_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
		
	
	/* TIM4 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	
	/* GPIOC and GPIOB clock enable */	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 
	/* GPIOE Configuration: */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOD, &GPIO_InitStructure); 	
	
	/* Connect TIM3 pins to AF2 */  
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4); 	
	
	
	
	//  uint16_t PrescalerValue = 0;
	/* Compute the prescaler value */
	//PrescalerValue = (uint16_t) ((SystemCoreClock/2) / TIM4_Freq) - 1;
	
	/* Time base configuration */
	TIM4_TimeBaseStructure.TIM_Period = Period;//Frequent3_Out;// TIM4->ARR寄存器确定输出频率 
	TIM4_TimeBaseStructure.TIM_Prescaler = Prescaler;
	TIM4_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM4_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM4_TimeBaseStructure);

	
	//   /* PWM1 Mode configuration: Channel1 */
	TIM4_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM4_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM4_OCInitStructure.TIM_Pulse = Period/2;  //0;//HEAT1_PWM_Duty;//占空比TIM4->CCR1寄存器确定输出占空比

	TIM_OC1Init(TIM4, &TIM4_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	//   /* PWM1 Mode configuration: Channel2 */
	TIM4_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM4_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM4_OCInitStructure.TIM_Pulse = Period/2;  //0;//HEAT2_PWM_Duty;//占空比TIM4->CCR2寄存器确定输出占空比

	TIM_OC2Init(TIM4, &TIM4_OCInitStructure);

	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
//   /* PWM1 Mode configuration: Channel3 */
	TIM4_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM4_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM4_OCInitStructure.TIM_Pulse = Period/2;  //0;//HEAT3_PWM_Duty;//Frequent3_Out/2;//Frequent1_Out/2;//占空比TIM4->CCR4寄存器确定输出占空比

	TIM_OC3Init(TIM4, &TIM4_OCInitStructure);

	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

//   /* PWM1 Mode configuration: Channel4 */
	TIM4_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM4_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM4_OCInitStructure.TIM_Pulse = Period/2;  //0;//HEAT4_PWM_Duty;//占空比TIM4->CCR4寄存器确定输出占空比

	TIM_OC4Init(TIM4, &TIM4_OCInitStructure);

	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM4, ENABLE);

	/* TIM4 enable counter */
	TIM_Cmd(TIM4, ENABLE);
}


void TIM_Set_Duty(TIM_TypeDef* TIMx, uint32_t CHx,uint8_t Duty)
{
	TIM_TimeBaseInitTypeDef*  TIM_TimeBaseStructure;
	
	if(TIMx==TIM3)
	{
		TIM_TimeBaseStructure = &TIM3_TimeBaseStructure;
	}else if(TIMx==TIM4)
	{
		TIM_TimeBaseStructure = &TIM4_TimeBaseStructure;
	}else{
		return ;
	}
	
	switch(CHx){
		case 1:
			TIM_SetCompare1(TIMx,TIM_TimeBaseStructure->TIM_Period/100*Duty);
		break;
		case 2:
			TIM_SetCompare2(TIMx,TIM_TimeBaseStructure->TIM_Period/100*Duty);
		break;
		case 3:
			TIM_SetCompare3(TIMx,TIM_TimeBaseStructure->TIM_Period/100*Duty);
		break;
		case 4:
			TIM_SetCompare4(TIMx,TIM_TimeBaseStructure->TIM_Period/100*Duty);
		break;
		default:
			break;
	}
	
}




/*
配置为输入，捕捉pwm信号
主频			：168MHZ
APB2分频系数	：2，84MHZ
TIM1的频率		：APB2主频 *2 /(Prescaler+1)=20MHZ
Period			：定时器计数的数量
*/
void TIM1_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* TIM1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	/* GPIOC and GPIOB clock enable */	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 
	/* GPIOE Configuration: */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOE, &GPIO_InitStructure); 	
	
	/* Connect TIM1 pins to AF2 */  
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);

	/* Time base configuration */
	TIM1_TimeBaseStructure.TIM_Period = 0xFFFF;	//0xFFFFFFFF;	//TIM1 16bit寄存器
	TIM1_TimeBaseStructure.TIM_Prescaler = TIME_PRESCALER(168);//TIME_PRESCALER_84;
	TIM1_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM1_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM1_TimeBaseStructure);
	
	/* Time ICInit configuration */
	TIM1_ICInitStructure.TIM_Channel		=	TIM_Channel_1;
	TIM1_ICInitStructure.TIM_ICPolarity		=	TIM_ICPolarity_Rising;
	TIM1_ICInitStructure.TIM_ICSelection	=	TIM_ICSelection_DirectTI;
	TIM1_ICInitStructure.TIM_ICPrescaler	=	TIM_ICPSC_DIV1;
	TIM1_ICInitStructure.TIM_ICFilter		=	0;
	
	TIM_ICInit(TIM1,&TIM1_ICInitStructure);
	
	/* Time ICInit configuration */
	TIM1_ICInitStructure.TIM_Channel		=	TIM_Channel_2;
	TIM1_ICInitStructure.TIM_ICPolarity		=	TIM_ICPolarity_Rising;
	TIM1_ICInitStructure.TIM_ICSelection	=	TIM_ICSelection_DirectTI;
	TIM1_ICInitStructure.TIM_ICPrescaler	=	TIM_ICPSC_DIV1;//TIM_ICPSC_DIV8;
	TIM1_ICInitStructure.TIM_ICFilter		=	0;
	
	TIM_ICInit(TIM1,&TIM1_ICInitStructure);
	
	/* Time ICInit configuration */
	TIM1_ICInitStructure.TIM_Channel		=	TIM_Channel_3;
	TIM1_ICInitStructure.TIM_ICPolarity		=	TIM_ICPolarity_Rising;
	TIM1_ICInitStructure.TIM_ICSelection	=	TIM_ICSelection_DirectTI;
	TIM1_ICInitStructure.TIM_ICPrescaler	=	TIM_ICPSC_DIV1;
	TIM1_ICInitStructure.TIM_ICFilter		=	0;
	
	TIM_ICInit(TIM1,&TIM1_ICInitStructure);
	TIM_Cmd(TIM1,ENABLE);
	TIM_ITConfig(TIM1,TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM1_CC_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01;                            //?????
	//NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}






/*
主频			：168MHZ
APB1分频系数	：4，42MHZ
TIM4的频率		：APB主频 *2 /(Prescaler+1)=84MHZ
Period			：定时器计数的数量

Prescaler		(100-1)		(100-1)		(10-1)		
Period			8400		840			8400
PWM clk			100			1000		1000
*/
void TIM2_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;
		
	
	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	

	/* Compute the prescaler value */
	//PrescalerValue = (uint16_t) ((SystemCoreClock/2) / TIM4_Freq) - 1;
	
	/* Time base configuration */
	TIM2_TimeBaseStructure.TIM_Period = TIME_10KHZ_PERIOD;
	TIM2_TimeBaseStructure.TIM_Prescaler = TIME_10KHZ_PRESCALER;
	TIM2_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM2_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM2_TimeBaseStructure);


	TIM_ARRPreloadConfig(TIM2, ENABLE);

	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}





/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
