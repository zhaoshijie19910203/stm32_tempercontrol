#include "exsram.h"

#define BANK1_SRAM_ADDR ((u32)(0x68000000))  //ȷ����ַ

void SRAM_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStruct;
	FSMC_NORSRAMTimingInitTypeDef FSMC_ReadWriteTimingStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = 0xf03f;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = 0x043f;
	GPIO_Init(GPIOG, &GPIO_InitStruct);
	
	FSMC_ReadWriteTimingStruct.FSMC_AddressSetupTime = 0x00; //��ַ����ʱ��Ϊ1��ʱ������
	FSMC_ReadWriteTimingStruct.FSMC_AddressHoldTime = 0x00; //?????? ??A???
	FSMC_ReadWriteTimingStruct.FSMC_DataSetupTime = 0x03; //??????
	FSMC_ReadWriteTimingStruct.FSMC_BusTurnAroundDuration = 0x00;
	FSMC_ReadWriteTimingStruct.FSMC_CLKDivision = 0x00; //??CLK?????????,?HCLK?????
	FSMC_ReadWriteTimingStruct.FSMC_DataLatency = 0x00; //???????
	FSMC_ReadWriteTimingStruct.FSMC_AccessMode = FSMC_AccessMode_A; //????A
	
	FSMC_NORSRAMInitStruct.FSMC_Bank = FSMC_Bank1_NORSRAM3;
	FSMC_NORSRAMInitStruct.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; //???????
	FSMC_NORSRAMInitStruct.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStruct.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStruct.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable; //??????????
	FSMC_NORSRAMInitStruct.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable; //???????????
	FSMC_NORSRAMInitStruct.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low; //????????
	FSMC_NORSRAMInitStruct.FSMC_WrapMode = FSMC_WrapMode_Disable; //?????????
	FSMC_NORSRAMInitStruct.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState; //?????????
	FSMC_NORSRAMInitStruct.FSMC_WriteOperation = FSMC_WriteOperation_Enable; //???FSMC???????
	FSMC_NORSRAMInitStruct.FSMC_WaitSignal = FSMC_WaitSignal_Disable; //???????
	FSMC_NORSRAMInitStruct.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStruct.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; //��дʱ����ͬ
	FSMC_NORSRAMInitStruct.FSMC_ReadWriteTimingStruct = &FSMC_ReadWriteTimingStruct;
	FSMC_NORSRAMInitStruct.FSMC_WriteTimingStruct = &FSMC_ReadWriteTimingStruct;
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStruct);
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3,ENABLE);
	
}

//pBuff д������ָ��  WriteAddrд���ַ nд���ֽڸ���

void SRAM_Write_Buff(u8 *pBuff,u32 WriteAddr,u32 n)
{
	while(n > 0)
	{
		*((vu8*)(BANK1_SRAM_ADDR+WriteAddr)) = *pBuff;
		WriteAddr += 2; //��Ϊfsmc���Զ�����ַ����һλ����ַ���1�������2
		pBuff++;
		n--;
	}
}

void SRAM_Read_Buff(u8 *pBuff,u32 ReadAddr,u32 n)
{
	while(n > 0)
	{
		*pBuff = *((vu8*)(BANK1_SRAM_ADDR+ReadAddr));
		ReadAddr += 2; //��Ϊfsmc���Զ�����ַ����һλ����ַ���1�������2
		pBuff++;
		n--;
	}
}



