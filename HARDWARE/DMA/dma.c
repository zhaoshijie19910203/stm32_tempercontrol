#include "dma.h"

u16 DMA1_MEM_LEN;//����ÿ��DMA���ݴ���ĳ���


// wsad �����ַ  ccad �洢����ַ  dacn���ݴ�����
void DMA_init(DMA_Channel_TypeDef* DMAy_Channelx,u32 wsad,u32 ccad,u16 dacn)
{
	DMA_InitTypeDef DMA_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_DeInit(DMAy_Channelx);   //Ĭ�ϳ�ʼ��
	DMA1_MEM_LEN=dacn;
	DMA_InitStruct.DMA_PeripheralBaseAddr = wsad;
	DMA_InitStruct.DMA_MemoryBaseAddr = ccad;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST; //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
	DMA_InitStruct.DMA_BufferSize = dacn; //dma����Ĵ�С
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ�Ĵ������� ���Ǵ��ڵ�ַ
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ�Ĵ�����ַ����
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;  //dma ģʽ�Ƿ�ѭ��
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;  //���ȼ�
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable; //û�����ó��ڴ浽�ڴ洫��
	DMA_Init(DMAy_Channelx, &DMA_InitStruct);
}

//����һ��DMA����
void DMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{ 
	DMA_Cmd(DMA_CHx, DISABLE );    
 	DMA_SetCurrDataCounter(DMA1_Channel4,DMA1_MEM_LEN);//DMAͨ��������ʱд�봫���ֽ���Ŀ; ͨ������ʱ��Ϊֻ����ָʾ��ǰ����ʣ���ֽ���
 	DMA_Cmd(DMA_CHx, ENABLE);  
}	
