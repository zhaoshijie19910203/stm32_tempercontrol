#include "key.h"

void key_init()
{
	//key_up(PA0)带下拉 key0(PE4) key1(PE3) key2(PE2)带上拉
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; //下拉输入
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

u8 getKeyValue()  //0xAB B中是四个按键的状态
{
	u8 t;
	t = (u8)(GPIO_ReadInputData(GPIOE)&0x001c);
	t >>= 1;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
		t += 1;
	return t;
}

//返回一个0xAB的值 B的0 1 2 3位分别代表KEY_UP KEY2 KEY1 KEY0的状态 1为按下 0为松开
u8 keyScan()   
{
	static u8 t;
	u8 k; 
	delay_init();
	k = getKeyValue();
	if(t == 0x00)
	{
			if(k == 0x0e)
			{
				t = 0x00;
			}
			else
			{
				delay_ms(20);
				if(k != 0x0e)
				{
					if((k&0x01) != 0)
						t |= 0x01;
					if((k&0x02) == 0)
						t |= 0x02;
					if((k&0x04) == 0)
						t |= 0x04;
					if((k&0x08) == 0)
						t |= 0x08;
				}
			}
	}
	if(k == 0x0e)
		t = 0x00;
	
	return t;
}

