#include "APP.h"
#include "stdio.h"


OS_EVENT* msg_key;
OS_EVENT* sem;

static int pt1000_temper;
static int ds18b20_temper;
static char stemper[10];
static char temper2pc[9];
static WM_HWIN hwin;

OS_STK TaskStk[OS_MAX_TASKS][TASK_STK_SIZE];

void Task_start_task(void *p_arg)   //��������������ڴ���ʵ�����õ������¼���
{
	p_arg = p_arg;
	
	msg_key = OSMboxCreate(NULL);
	sem = OSSemCreate((u16)2);
	
	OSTaskCreate (Led1_task, NULL, (OS_STK *)&TaskStk[1][TASK_STK_SIZE-1], (INT8U)LED1_TASK_PRIO);
//	OSTaskCreate (Led2_task, NULL, (OS_STK *)&TaskStk[2][TASK_STK_SIZE-1], (INT8U)LED2_TASK_PRIO);
	OSTaskCreate (tftTouch_task, NULL, (OS_STK *)&TaskStk[3][TASK_STK_SIZE-1], (INT8U)TFT_TOUCH_TASK_PRIO);
	OSTaskCreate (KeyScan_task, NULL, (OS_STK *)&TaskStk[4][TASK_STK_SIZE-1], (INT8U)KEYSCAN_TASK_PRIO);
	OSTaskCreate (WndTest_task, NULL, (OS_STK *)&TaskStk[5][TASK_STK_SIZE-1], (INT8U)WNDTEST_TASK_PRIO);
	OSTaskCreate (temperGet_task, NULL, (OS_STK *)&TaskStk[6][TASK_STK_SIZE-1], (INT8U)TEMPERGET_TASK_PRIO);
	OSTaskCreate (ds18b20init_task, NULL, (OS_STK *)&TaskStk[7][TASK_STK_SIZE-1], (INT8U)DS18B20INIT_TASK_PRIO);
	OSTaskCreate (usart2pc_task, NULL, (OS_STK *)&TaskStk[8][TASK_STK_SIZE-1], (INT8U)USART2PC_TASK_PRIO);
	OSTaskCreate (timer_task, NULL, (OS_STK *)&TaskStk[9][TASK_STK_SIZE-1], (INT8U)TIMER_TASK_PRIO);
	
	OSTaskSuspend(TASK_START_PRIO);
}

void tftTouch_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		GUI_TOUCH_Exec();
		GUI_Exec();
		OSTimeDlyHMSM(0,0,0,10);  //10ms���һ�δ�����  ����һ����Ļ
	}
}

void Led1_task(void *p_arg)
{
	u8 *key;
	u8 err;
	p_arg = p_arg;  //�����ã�����ֹ�������
	while(1)
	{	
		key = OSMboxPend(msg_key,10,&err);
		if(err == OS_ERR_NONE)
		{
			switch(*key)
			{
				case KEY_LEFT  	: 	led0(OFF); break;
				case KEY_RIGHT 	: 	led0(ON);  break;
			}
		}
		OSTimeDlyHMSM(0,0,0,10);
	}
}

void Led2_task(void *p_arg)
{
	u8 error;
	p_arg = p_arg;  //�����ã�����ֹ�������
	while(1)
	{
		OSSemPend(sem,0,&error);  //pevent->OSEventCnt--  sem = OSSemCreate((u16)1);
		led1(ON);                //����ֻ��ִ��һ��
		OSTimeDlyHMSM(0,0,1,0);
		led1(OFF);
		OSTimeDlyHMSM(0,0,1,0);
	}
}

void KeyScan_task(void *p_arg)
{
	u8 key = 0;
	p_arg = p_arg;
	while(1)
	{
		key = KEY_Scan(0);
		if((key == KEY_LEFT)||(key == KEY_RIGHT)||(key == KEY_DOWN))
		{
			OSMboxPost(msg_key,&key);
		}
		else if(key == KEY_UP)
		{
			OSSemPost(sem);
		}
		OSTimeDlyHMSM(0,0,0,10);
	}
}

void WndTest_task(void *p_arg)
{
	p_arg = p_arg;
	hwin = CreateFramewin();
	OSTaskSuspend(WNDTEST_TASK_PRIO);
}

void temperGet_task(void *p_arg)
{
	u16 adcx;
	float voltage;
	float current;
	float ftemper;
	
	p_arg = p_arg;

	while(1)
	{
		adcx = Get_Adc_Average(ADC_Channel_1,600);  //��600����ƽ��ֵ
		voltage = (float)adcx*3.3/4096;   //��õĵ�ѹֵ
		current = voltage*1000/150;
		ftemper = 120*(current-4)/16;
		pt1000_temper = (int)(ftemper*100);   //������λС��
		
		inttostr(pt1000_temper,stemper);
		TEXT_SetText(WM_GetDialogItem(hwin,ID_TEXT_0),stemper);
		OSTimeDlyHMSM(0,0,0,100);
	}
}
//��ʼ���ɹ� ����ds18b20�������� ��ɾ���Լ� 
void ds18b20init_task(void *p_arg)
{
	p_arg = p_arg;
// 	while(DS18B20_Init())  //��ʼ��ʧ�ܽ���ѭ��
// 	{
// 		led0(OFF);   
// 		OSTimeDlyHMSM(0,0,0,100);
// 	}
//	led0(ON);   //��ʼ���ɹ� ����led0  
	OSTaskCreate (ds18b20_task, NULL, (OS_STK *)&TaskStk[9][TASK_STK_SIZE-1], (INT8U)DS18B20_TASK_PRIO);
	OSTaskDel(DS18B20INIT_TASK_PRIO);
}

void ds18b20_task(void *p_arg)
{
	short temper = 0;
	p_arg = p_arg;
	while(1)
	{
		//temper = DS18B20_Get_Temp();
		if(temper<0)
		{
			OSTimeDlyHMSM(0,0,0,10);  //��ʱû���¶�С��0�� ��ʾ���д���
		}
		else
		{
		//	ds18b20_temper = (int)(temper*10);   //������λС��
			inttostr(ds18b20_temper,stemper);
			TEXT_SetText(WM_GetDialogItem(hwin,ID_TEXT_1),stemper);
		}
			
		OSTimeDlyHMSM(0,0,0,100);  //100ms���һ��ds18b20
	}
}

//���� ����λ��ͨ��
void usart2pc_task(void *p_arg)
{
	u8 t;
	u8 len;	
	u16 times=0;
	u8 flag = 0;
	p_arg = p_arg;
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
				len=USART_RX_STA&0x3fff;//�õ��˴ν��յ����ݳ���
				printf("\r\n???????:\r\n\r\n");
				for(t=0;t<len;t++)
				{
					USART_SendData(USART1, USART_RX_BUF[t]);//???1????
					while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//??????
				}
				printf("\r\n\r\n");//????
				USART_RX_STA=0;
		}
		else
		{
				times++;
				inttostr2(temper2pc);
				if(times%200==0)printf(temper2pc);  
			//	if(times%30==0) led0(flag=~flag);//��ʾϵͳ��������
				OSTimeDlyHMSM(0,0,0,10);   
		}
	}
}
//����һЩ�й�ʱ������ݣ����綨ʱ��˸
void timer_task(void *p_arg)
{
	u16 time = 0;
	p_arg = p_arg;
	while(1)
	{
		OSTimeDlyHMSM(0,0,0,100);
		time++;
		if(time >= 10000)
			time = 0;
		
		if(heat_flag == 1)  //����Ǽ���״̬ ��˸��ʾ
		{
			if(time%20 < 10)
				TEXT_SetText(WM_GetDialogItem(hwin,ID_TEXT_5),"heating");
			else
				TEXT_SetText(WM_GetDialogItem(hwin,ID_TEXT_5),"");
		}
	}
}

//��Ƭ��ucgui��ʾ�¶���Ҫ��int2str
static void inttostr(int source,char * dest)
{
   int i;
   for (i=4;i>0;i--)   //��ʾ4λ 
   {
       dest[i-1] = (source % 10) + 0x30;
       source /= 10;
   }
	 dest[4] = dest[3];
	 dest[3] = dest[2];
	 dest[2] = '.';
	 dest[5] = ' ';
	 dest[6] = 'C';
}
//��4λpt1000���� 4λds18b20���� ���ת�����ַ��� ���ڴ���ͨ���͸���λ��
static void inttostr2(char *dest)
{
  dest[0] = pt1000_temper / 1000 + 0x30;
	dest[1] = pt1000_temper % 1000 / 100 + 0x30;
	dest[2] = pt1000_temper % 1000 %100 / 10 + 0x30;
	dest[3] = pt1000_temper % 1000 %100 % 10 + 0x30;
	dest[4] = ds18b20_temper / 1000 + 0x30;
	dest[5] = ds18b20_temper % 1000 / 100 + 0x30;
	dest[6] = ds18b20_temper % 1000 %100 / 10 + 0x30;
	dest[7] = ds18b20_temper % 1000 %100 % 10 + 0x30;
	dest[8] = '\n';
}


