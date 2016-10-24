#ifndef __EXSRAM_H
#define __EXSRAM_H

#include "stm32f10x.h"

void SRAM_init(void);
void SRAM_Write_Buff(u8 *pBuff,u32 WriteAddr,u32 n);
void SRAM_Read_Buff(u8 *pBuff,u32 ReadAddr,u32 n);

#endif

