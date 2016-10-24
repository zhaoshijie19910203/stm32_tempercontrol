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
	
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //ȫ˫��
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High; //ʱ�Ӽ��� ����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ ��������ΪSPI_CPOL_High
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge; //�ڶ������������ݱ�����
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft; //���nss
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; //ʱ�ӷ�Ƶ
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB; //��һλ����λ����
	SPI_InitStruct.SPI_CRCPolynomial = 7; //CRCУ�����ʽ ѭ������У��
	SPI_Init(SPI2, &SPI_InitStruct);
	
	SPI_Cmd(SPI2,ENABLE);
	 
	SPI2_ReadWriteByte(0xff);   //��������
}

void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI2->CR1&=0XFFC7;   //��ֹSPI�豸
	SPI2->CR1|=SPI_BaudRatePrescaler;	//����SPI2�ٶ� 
	SPI_Cmd(SPI2,ENABLE);  //ʹ��SPI
} 
//SPIx ��дһ���ֽ�
//TxData��Ҫд����ֽ�
//����ֵ����ȡ�����ֽ�

u8 SPI2_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //���ͻ���ձ�־λ  �ȴ��������
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI2, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //���ܻ���ǿձ�־λ �ȴ��������
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI2); //	����ͨ��SPIx������ܵ�����				    
}
