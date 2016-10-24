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
	SysTick_Init();  //滴答定时器的初始化启动 开中断
	KEY_Init();
	delay_init();  //如果带操作系统ucos 则此函数也会进行滴答定时器的初始化和启动 以及开中断
	
	GUI_Init();	
	AT24CXX_Init();                //初始化24C02
	tp_dev.init();								//初始化触摸
	
	Adc_Init();
	uart_init(9600);  //串口1  8位 无奇偶校验 1位停止位
	MGPIO_Init();
	
	OSInit();
	OSTaskCreate (Task_start_task, NULL, (OS_STK *)&TaskStk[0][TASK_STK_SIZE-1], (INT8U)TASK_START_PRIO);
	OSStart();
	
	return 0;
}







