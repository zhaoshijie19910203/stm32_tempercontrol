#include "tim.h"

//T=Ftosc/(TIM_Period+1)*(TIM_Prescaler+1);(Ftosc�Ƕ�ʱ��ʱ��)
//T=Ftosc/(arr+1)*(psc+1)  Ftoscһ��Ϊ72MHz

void tim_init(u16 arr,u16 psc)  //timer3 init  arr�Զ�װ��ֵ psc(0-65535)Ԥ��Ƶ��
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV2;  //��TIMx_CR1��λ9:8 �����ڶ�ʱ��ʱ��Ƶ�ʺ������˲���ʹ�õĲ���Ƶ��֮��ķ�Ƶ����
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //�����ж�ʹ��
	TIM_Cmd(TIM3,ENABLE); //�򿪶�ʱ��
}

static u8 i=0;

void TIM3_IRQHandler(void)   //��ʱ���жϺ���
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		i = !i;
		led0(i);
	}
}

