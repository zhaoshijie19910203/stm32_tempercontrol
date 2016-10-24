#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"


void spi2_Init(void);
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);
u8 SPI2_ReadWriteByte(u8 TxData);

#endif

