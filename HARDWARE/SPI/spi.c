#include "spi.h"

void spi2_Init(void)
{
	SPI_InitTypeDef SPI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //全双工
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High; //时钟极性 串行同步时钟的空闲状态为高电平 所以设置为SPI_CPOL_High
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge; //第二个跳变沿数据被采样
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft; //软件nss
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; //时钟分频
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB; //第一位传高位数据
	SPI_InitStruct.SPI_CRCPolynomial = 7; //CRC校验多项式 循环冗余校验
	SPI_Init(SPI2, &SPI_InitStruct);
	
	SPI_Cmd(SPI2,ENABLE);
	 
	SPI2_ReadWriteByte(0xff);   //启动传输
}

void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI2->CR1&=0XFFC7;   //禁止SPI设备
	SPI2->CR1|=SPI_BaudRatePrescaler;	//设置SPI2速度 
	SPI_Cmd(SPI2,ENABLE);  //使能SPI
} 
//SPIx 读写一个字节
//TxData：要写入的字节
//返回值：读取到的字节

u8 SPI2_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //发送缓存空标志位  等待发送完成
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI2, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //接受缓存非空标志位 等待接收完成
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI2); //	返回通过SPIx最近接受的数据				    
}
