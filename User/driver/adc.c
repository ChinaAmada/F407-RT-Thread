

/* Includes ------------------------------------------------------------------*/
#include "adc.h"
#include "config.h"




//uint16_t ADC1Converted_Digital_Value[ADC1_CHANNEL_NUM] = {0};


u16 ADC_Result[ADC1_CHANNEL_NUM]={0};



float Average_Float(float* arr,uint32_t len)
{
	uint32_t i;
	float target_sun=0;
	
	for(i=0;i<len;i++)
	{
		target_sun += arr[i];
	}
	
	return (float)target_sun/len;
}

/*
u16 fir[NUM][PER];
 
void ADC_Filter(void)
{
	register u16 sum=0;
	u8 count=0,i=0,j=0;
	for(;i<PER;i++)
	{
		while(j<NUM)
		{//865
			sum+=fir[j][i];
			count++;
			j++;
		}
		ADC_Result[i]=sum/count;
		sum=0;count=0;j=0;
	}
}
*/

void ADC_All_Config(void)
{ 
	ADC_GPIO_config();
	ADC_Common_config();
	ADC_DMA_config();
}


void ADC_GPIO_config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE); 
	
	/* Configure ADC1 Channel0-7 pin as analog input ******************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure ADC1 Channel8-9 pin as analog input ******************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure ADC1 Channel10-12 pin as analog input ******************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}


void ADC_Common_config(void)
{
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);                           //使能ADC1时钟
 
 
	//RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	                           //ADC1??
	//RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);                           //????
 
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;                       //????
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;  //???????????x???
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//ADC_DMAAccessMode_1;               //DMA??(DMA????????)
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//ADC_Prescaler_Div4;                    //???4???ADCCLK=PCLK2/4=84/4=21Mhz,ADC????????36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);                                      //??? 
	
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;                         //12???
	ADC_InitStructure.ADC_ScanConvMode =ENABLE;                                    //??(??DMA???????)
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//ENABLE;                             //??????(??DMA?????????)
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;    //??????,??????
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                         //???	
	ADC_InitStructure.ADC_NbrOfConversion = ADC1_CHANNEL_NUM;                                    //?????????? (DMA??????????)
	ADC_InitStructure.ADC_ExternalTrigConv = 0;
	ADC_Init(ADC1, &ADC_InitStructure);                                            //ADC???
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1,  ADC_SampleTime_144Cycles);   //res[0]
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2,  ADC_SampleTime_144Cycles);   //res[0]
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3,  ADC_SampleTime_144Cycles);   //res[1]
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4,  ADC_SampleTime_144Cycles);   //res[2]
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5,  ADC_SampleTime_144Cycles);   //res[3]
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6,  ADC_SampleTime_144Cycles);   //res[4]
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7,  ADC_SampleTime_144Cycles);   //res[5]
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8,  ADC_SampleTime_144Cycles);   //res[6]
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 9,  ADC_SampleTime_144Cycles);   //res[7]
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 10,  ADC_SampleTime_144Cycles);  //res[8]-PC0
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 11, ADC_SampleTime_144Cycles);  //res[9]-PC1
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 12,  ADC_SampleTime_144Cycles); //res[8]-PC2
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 13, ADC_SampleTime_144Cycles);  //res[9]-PC3
 
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);                                                         //??AD???
}


void ADC_DMA_config(void)
{
	DMA_InitTypeDef  DMA_InitStructure;
//W
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);                          //DMA2 ADC1在DMA2

	DMA_DeInit(DMA2_Stream0);
	
	while (DMA_GetCmdStatus(DMA2_Stream0) != DISABLE){}                             //??DMA??? 
	
	/* ?? DMA Stream */
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;                                  //????
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(ADC1_BASE+0x4C);                                //DMA????
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)(&ADC_Result[0]);//(uint32_t)&ADC1Converted_Digital_Value;                                   //DMA ???0??
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;                        //????????
	DMA_InitStructure.DMA_BufferSize = ADC1_CHANNEL_NUM;                                       //????? 
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;               //???????
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                        //???????
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;    //??????:8?
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;            //???????:8?
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                                //?????? 
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                          //?????
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;                    //?????????
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;            //????????
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);                                     //???DMA Stream
	//DMA_ClearFlag(DMA2_Stream0,DMA_IT_TC);
	//DMA_ITConfig(DMA2_Stream0,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA2_Stream0, ENABLE);	
/*	
	NVIC_InitStructure.NVIC_IRQChannel=DMA2_Stream0_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01;                     //?????
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01;                            //?????
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
*/
}

void DMA2_Stream0_IRQHandler(void) 
{
	if (DMA_GetFlagStatus(DMA2_Stream0, DMA_IT_TCIF0) == SET)  
	{
		//ADC_Filter();
		DMA_ClearFlag(DMA2_Stream0, DMA_IT_TCIF0); 
	}
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
