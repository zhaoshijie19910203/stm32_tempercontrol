#include "gpio.h"

void MGPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
}

void GPIO_B6(u8 t)
{
	if(t == 0)
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	else
		GPIO_SetBits(GPIOB,GPIO_Pin_6);
}

