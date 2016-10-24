#include "LED.h"

void ledInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	
	led0(1);
	led1(1);
}

void led0(u8 t)
{
	if(t == 0)
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	else
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
}

void led1(u8 t)
{
	if(t == 0)
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);
	else
		GPIO_SetBits(GPIOE,GPIO_Pin_5);
}

