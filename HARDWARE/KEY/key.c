#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "includes.h"
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEKÕ½½¢STM32¿ª·¢°å
//°´¼üÇý¶¯´úÂë	   
//ÕýµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//ÐÞ¸ÄÈÕÆÚ:2012/9/3
//°æ±¾£ºV1.0
//°æÈ¨ËùÓÐ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//°´¼ü³õÊ¼»¯º¯Êý
void KEY_Init(void) //IO³õÊ¼»¯
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
	//³õÊ¼»¯KEY0-->GPIOA.13,KEY1-->GPIOA.15  ÉÏÀ­ÊäÈë
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//Ê¹ÄÜPORTA,PORTEÊ±ÖÓ

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//PE2~4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ÉèÖÃ³ÉÉÏÀ­ÊäÈë
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//³õÊ¼»¯GPIOE2,3,4

	//³õÊ¼»¯ WK_UP-->GPIOA.0	  ÏÂÀ­ÊäÈë
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0ÉèÖÃ³ÉÊäÈë£¬Ä¬ÈÏÏÂÀ­	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»¯GPIOA.0

}
//°´¼ü´¦Àíº¯Êý
//·µ»Ø°´¼üÖµ
//mode:0,²»Ö§³ÖÁ¬Ðø°´;1,Ö§³ÖÁ¬Ðø°´;
//0£¬Ã»ÓÐÈÎºÎ°´¼ü°´ÏÂ
//1£¬KEY0°´ÏÂ  				KEY_RIGHT
//2£¬KEY1°´ÏÂ  				KEY_DOWN
//3£¬KEY2°´ÏÂ 				KEY_LEFT
//4£¬KEY3°´ÏÂ WK_UP		KEY_UP
//×¢Òâ´Ëº¯ÊýÓÐÏìÓ¦ÓÅÏÈ¼¶,KEY0>KEY1>KEY2>KEY3!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//°´¼ü°´ËÉ¿ª±êÖ¾
	if(mode)key_up=1;  //Ö§³ÖÁ¬°´		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==1))
	{
	//	delay_ms(10);//È¥¶¶¶
		OSTimeDlyHMSM(0,0,0,10);  //zsj×Ô¼ºÐÞ¸ÄµÄ²»ÓÃdelay_ms   ÒòÎªdelay_msÉæ¼°µ½µÎ´ð¶¨Ê±Æ÷
		key_up=0;
		if(KEY0==0)return KEY_RIGHT;
		else if(KEY1==0)return KEY_DOWN;
		else if(KEY2==0)return KEY_LEFT;
		else if(KEY3==1)return KEY_UP;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==0)key_up=1; 	    
 	return 0;// ÎÞ°´¼ü°´ÏÂ
}
