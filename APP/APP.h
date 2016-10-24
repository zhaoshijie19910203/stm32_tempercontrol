#ifndef _APP_H
#define _APP_H

#include "stm32f10x.h"
#include "hardware.h"
#include "includes.h"
#include "GUI.h"
#include "TemperShow.h"
#include "ds18b20.h"
#include "usart.h"

#define TASK_STK_SIZE 200

#define TASK_START_PRIO 		25
#define TFT_TOUCH_TASK_PRIO 17
#define LED1_TASK_PRIO  		10
#define LED2_TASK_PRIO  		11
#define KEYSCAN_TASK_PRIO 	15
#define WNDTEST_TASK_PRIO	  14
#define TEMPERGET_TASK_PRIO	20
#define DS18B20INIT_TASK_PRIO		21
#define DS18B20_TASK_PRIO		22
#define USART2PC_TASK_PRIO  23
#define TIMER_TASK_PRIO 		19

extern OS_STK TaskStk[OS_MAX_TASKS][TASK_STK_SIZE];

void Task_start_task(void *p_arg);
void tftTouch_task(void *p_arg);
void Led1_task(void *p_arg);
void Led2_task(void *p_arg);
void KeyScan_task(void *p_arg);
void WndTest_task(void *p_arg);
void temperGet_task(void *p_arg);
void ds18b20init_task(void *p_arg);
void ds18b20_task(void *p_arg);
void usart2pc_task(void *p_arg);
void timer_task(void *p_arg);



static void inttostr(int source,char * dest); //Êý×Ö×ª×Ö·û´®
static void inttostr2(char *dest);

extern OS_EVENT* msg_key;
extern OS_EVENT* sem;

#endif


