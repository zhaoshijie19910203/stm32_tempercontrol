#include "key.h"

void key_init()
{
	//key_up(PA0)������ key0(PE4) key1(PE3) key2(PE2)������
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; //��������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; //��������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

u8 getKeyValue()  //0xAB B�����ĸ�������״̬
{
	u8 t;
	t = (u8)(GPIO_ReadInputData(GPIOE)&0x001c);
	t >>= 1;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
		t += 1;
	return t;
}

//����һ��0xAB��ֵ B��0 1 2 3λ�ֱ����KEY_UP KEY2 KEY1 KEY0��״̬ 1Ϊ���� 0Ϊ�ɿ�
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

