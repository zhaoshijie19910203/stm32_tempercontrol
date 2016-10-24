#include "dma.h"

u16 DMA1_MEM_LEN;//保存每次DMA数据传输的长度


// wsad 外设地址  ccad 存储器地址  dacn数据传输量
void DMA_init(DMA_Channel_TypeDef* DMAy_Channelx,u32 wsad,u32 ccad,u16 dacn)
{
	DMA_InitTypeDef DMA_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_DeInit(DMAy_Channelx);   //默认初始化
	DMA1_MEM_LEN=dacn;
	DMA_InitStruct.DMA_PeripheralBaseAddr = wsad;
	DMA_InitStruct.DMA_MemoryBaseAddr = ccad;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST; //数据传输方向，从内存读取发送到外设
	DMA_InitStruct.DMA_BufferSize = dacn; //dma缓存的大小
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变 都是串口地址
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存寄存器地址递增
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;  //dma 模式是否循环
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;  //优先级
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable; //没有设置成内存到内存传输
	DMA_Init(DMAy_Channelx, &DMA_InitStruct);
}

//开启一次DMA传输
void DMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{ 
	DMA_Cmd(DMA_CHx, DISABLE );    
 	DMA_SetCurrDataCounter(DMA1_Channel4,DMA1_MEM_LEN);//DMA通道不工作时写入传输字节数目; 通道工作时变为只读，指示当前传输剩余字节数
 	DMA_Cmd(DMA_CHx, ENABLE);  
}	
