/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "config.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}


/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}



/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);				
		/* Read one byte from the receive data register */
		
		Usart2_Push_Char();
	}else if(USART_GetITStatus(USART2,USART_IT_IDLE) != RESET){
		USART_ReceiveData(USART2);
		//Usart6_Set_RecPack_Flag();
	}
}

void USART6_IRQHandler(void)
{
	if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART6,USART_IT_RXNE);				
		/* Read one byte from the receive data register */
		
		Usart6_Push_Char();
	}else if(USART_GetITStatus(USART6,USART_IT_IDLE) != RESET){
		USART_ReceiveData(USART6);
		//Usart6_Set_RecPack_Flag();
	}
}


extern struct rt_semaphore Can1_Rx_Sem; 
void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg  Can1_RX_Buff;
	
  CAN_Receive(CAN1, CAN_FIFO0, &Can1_RX_Buff);
  CAN1_Push_Packet(&Can1_RX_Buff);
  rt_sem_release(&Can1_Rx_Sem);
}


extern uint32_t Freq_InputCapture[];
void TIM1_CC_IRQHandler(void)
{
	static uint32_t capture_value1[3]={0},capture_value2[3]={0};
	static uint16_t flag_capture[3] = {0};
	static uint32_t capture[3]={0};
	
	if(TIM_GetITStatus(TIM1,TIM_IT_CC1)!=RESET)
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_CC1);
		
		if(flag_capture[0]==0)
		{
			flag_capture[0]=1;
			capture_value1[0]=(uint32_t)(TIM1->CCR1);
		}else if(flag_capture[0]==1)
		{
			flag_capture[0]=0;
			capture_value2[0]=(uint32_t)(TIM1->CCR1);
			
			if(capture_value2[0]>capture_value1[0])
			{
				capture[0] = capture_value2[0]-capture_value1[0];
			}else if(capture_value2[0]<capture_value1[0])
			{
				capture[0] = capture_value2[0]+(0xFFFF-capture_value1[0]);
			}else{
				capture[0]=0;
			}
			
			if(capture[0]!=0)
				Freq_InputCapture[0] = (uint32_t)SystemCoreClock/(TIME_PRESCALER_84+1)/capture[0]/8;
			else
				Freq_InputCapture[0]=0;
		}
	}else if(TIM_GetITStatus(TIM1,TIM_IT_CC2)!=RESET)
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_CC2);
		
		if(flag_capture[1]==0)
		{
			flag_capture[1]=1;
			capture_value1[1]=(uint32_t)(TIM1->CCR2);
		}else if(flag_capture[1]==1)
		{
			flag_capture[1]=0;
			capture_value2[1]=(uint32_t)(TIM1->CCR2);
			
			if(capture_value2[1]>capture_value1[1])
			{
				capture[1] = capture_value2[1]-capture_value1[1];
			}else if(capture_value2[1]<capture_value1[1])
			{
				capture[1] = capture_value2[1]+(0xFFFF-capture_value1[1]);
			}else{
				capture[1]=0;
			}
			
			if(capture[1]!=0)
				Freq_InputCapture[1] = (uint32_t)SystemCoreClock/(TIME_PRESCALER_84+1)/capture[1];
			else
				Freq_InputCapture[1]=0;
		}
	}else if(TIM_GetITStatus(TIM1,TIM_IT_CC3)!=RESET)
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_CC3);
		
		if(flag_capture[2]==0)
		{
			flag_capture[2]=1;
			capture_value1[2]=(uint32_t)(TIM1->CCR3);
		}else if(flag_capture[2]==1)
		{
			flag_capture[2]=0;
			capture_value2[2]=(uint32_t)(TIM1->CCR3);
			
			if(capture_value2[2]>capture_value1[2])
			{
				capture[2] = capture_value2[2]-capture_value1[2];
			}else if(capture_value2[2]<capture_value1[2])
			{
				capture[2] = capture_value2[2]+(0xFFFF-capture_value1[2]);
			}else{
				capture[2]=0;
			}
			
			if(capture[2]!=0)
				Freq_InputCapture[2] = (uint32_t)SystemCoreClock/(TIME_PRESCALER_84+1)/capture[2];
			else
				Freq_InputCapture[2]=0;
		}
	}
	
}


extern void TIM2_Update_Hook(void);
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		
		TIM2_Update_Hook();
	}
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
