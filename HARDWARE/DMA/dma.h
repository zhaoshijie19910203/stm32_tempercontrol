#ifndef __DMA_H
#define __DMA_H

#include "stm32f10x.h"

void DMA_init(DMA_Channel_TypeDef* DMAy_Channelx,u32 wsad,u32 ccad,u16 dacn);
void DMA_Enable(DMA_Channel_TypeDef*DMA_CHx);
void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx);
#endif

