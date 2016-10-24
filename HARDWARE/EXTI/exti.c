#include "exti.h"

void exti_init(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //������ӳ��ʱ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2); //IO���ж���ӳ���ϵ
	EXTI_InitStruct.EXTI_Line = EXTI_Line2;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);  //��ʼ�������ж�
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����жϷ���
	NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);  //���ò�ʹ���ж�
}

static u8 flag = 0;

void EXTI2_IRQHandler(void)
{
	delay_ms(10);
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == RESET)
	{
		if(flag)
		{
			led0(0);
			led1(1);
		}
		else
		{
			led0(1);
			led1(0);
		}
		flag = !flag;
	}
	//EXTI_ClearITPendingBit(EXTI_Line2);  //����жϱ�־λ
	EXTI_ClearFlag(EXTI_Line2);  //����һ����������
}

