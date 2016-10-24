#ifndef _WNDTEST_H
#define _WNDTEST_H

#include "stm32f10x.h"
#include "hardware.h"
#include "includes.h"
#include "GUI.h"
#include "DIALOG.h"

#define ID_WINDOW_0     (GUI_ID_USER + 0x00)
#define ID_BUTTON_0     (GUI_ID_USER + 0x08)
#define ID_BUTTON_1     (GUI_ID_USER + 0x09)
#define ID_PROGBAR_0    (GUI_ID_USER + 0x0C)
#define ID_CHECKBOX_0   (GUI_ID_USER + 0x0E)
#define ID_CHECKBOX_1   (GUI_ID_USER + 0x0F)


WM_HWIN CreateWindow(void);

#endif

