#include "tim.h"

//T=Ftosc/(TIM_Period+1)*(TIM_Prescaler+1);(Ftosc是定时器时钟)
//T=Ftosc/(arr+1)*(psc+1)  Ftosc一般为72MHz

void tim_init(u16 arr,u16 psc)  //timer3 init  arr自动装填值 psc(0-65535)预分频数
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV2;  //见TIMx_CR1的位9:8 定义在定时器时钟频率和数字滤波器使用的采样频率之间的分频比例
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //更新中断使能
	TIM_Cmd(TIM3,ENABLE); //打开定时器
}

static u8 i=0;

void TIM3_IRQHandler(void)   //定时器中断函数
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		i = !i;
		led0(i);
	}
}

