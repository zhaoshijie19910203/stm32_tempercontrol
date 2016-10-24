#ifndef _TEMPERSHOW_H
#define _TEMPERSHOW_H

#include "stm32f10x.h"
#include "hardware.h"
#include "includes.h"
#include "GUI.h"
#include "DIALOG.h"


#define ID_FRAMEWIN_0   (GUI_ID_USER + 0x01)
#define ID_TEXT_0   (GUI_ID_USER + 0x02)
#define ID_TEXT_1   (GUI_ID_USER + 0x04)
#define ID_TEXT_2   (GUI_ID_USER + 0x05)
#define ID_TEXT_3   (GUI_ID_USER + 0x06)
#define ID_TEXT_4   (GUI_ID_USER + 0x07)
#define ID_TEXT_5   (GUI_ID_USER + 0x08)

#define ID_BUTTON_0   (GUI_ID_USER + 0x09)
#define ID_BUTTON_1   (GUI_ID_USER + 0x0a)

#define HEAT(x)  GPIO_B6(x)

extern u8 heat_flag;

WM_HWIN CreateFramewin(void);

#endif

