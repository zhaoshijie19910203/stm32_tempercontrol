#include "stm32f10x.h"
#include "hardware.h"
#include "includes.h"

#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"
#include "APP.h"

#define SystemFrequency 72000000

void SysTick_Init(void)
{
	SysTick_Config(SystemFrequency/OS_TICKS_PER_SEC);
}

int main(void)
{
	NVIC_Configuration();
	ledInit();
	SysTick_Init();  //�δ�ʱ���ĳ�ʼ������ ���ж�
	KEY_Init();
	delay_init();  //���������ϵͳucos ��˺���Ҳ����еδ�ʱ���ĳ�ʼ�������� �Լ����ж�
	
	GUI_Init();	
	AT24CXX_Init();                //��ʼ��24C02
	tp_dev.init();								//��ʼ������
	
	Adc_Init();
	uart_init(9600);  //����1  8λ ����żУ�� 1λֹͣλ
	MGPIO_Init();
	
	OSInit();
	OSTaskCreate (Task_start_task, NULL, (OS_STK *)&TaskStk[0][TASK_STK_SIZE-1], (INT8U)TASK_START_PRIO);
	OSStart();
	
	return 0;
}







