/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.12                          *
*        Compiled Jun 29 2011, 15:28:47                              *
*        (c) 2011 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "TemperShow.h"


// USER START (Optionally insert additional defines)
u8 heat_flag = 0;
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 320, 480, 0, 0},
  { TEXT_CreateIndirect, "Text", ID_TEXT_0, 161, 63, 114, 42, 0, 100},
  { TEXT_CreateIndirect, "Text", ID_TEXT_1, 161, 121, 114, 42, 0, 100},
  { TEXT_CreateIndirect, "Text", ID_TEXT_2, 33, 63, 114, 42, 0, 100},
  { TEXT_CreateIndirect, "Text", ID_TEXT_3, 33, 121, 114, 42, 0, 100},
	{ TEXT_CreateIndirect, "Text", ID_TEXT_4, 33, 210, 114, 42, 0, 100},
  { TEXT_CreateIndirect, "Text", ID_TEXT_5, 161, 210, 114, 42, 0, 100},
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 49, 275, 82, 40, 0, 0},
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 176, 275, 82, 40, 0, 0},
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
	int Id, NCode;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetFont(hItem, &GUI_Font32B_ASCII);
		TEXT_SetBkColor(hItem,GUI_GRAY);
    TEXT_SetTextColor(hItem, 0x00FF0000);
    TEXT_SetText(hItem, "pt1000");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetFont(hItem, &GUI_Font32B_ASCII);
		TEXT_SetBkColor(hItem,GUI_GRAY);
    TEXT_SetTextColor(hItem, 0x00FF0000);
		TEXT_SetText(hItem, "ds18b20");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetFont(hItem, &GUI_Font24B_ASCII);
		TEXT_SetBkColor(hItem,GUI_GRAY);
    TEXT_SetTextColor(hItem, 0x00FF0000);
    TEXT_SetText(hItem, "pt1000:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetFont(hItem, &GUI_Font24B_ASCII);
		TEXT_SetBkColor(hItem,GUI_GRAY);
    TEXT_SetTextColor(hItem, 0x00FF0000);
    TEXT_SetText(hItem, "ds18b20:");
		//
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetFont(hItem, &GUI_Font24B_ASCII);
		TEXT_SetBkColor(hItem,GUI_GRAY);
    TEXT_SetTextColor(hItem, 0x00FF0000);
    TEXT_SetText(hItem, "state:");
		//
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetFont(hItem, &GUI_Font32B_ASCII);
		TEXT_SetBkColor(hItem,GUI_GRAY);
    TEXT_SetTextColor(hItem, 0x00FF0000);
		TEXT_SetText(hItem, "STOP");
		//
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetFont(hItem, &GUI_Font24B_ASCII);
    BUTTON_SetText(hItem, "start");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
		BUTTON_SetFont(hItem, &GUI_Font24B_ASCII);
    BUTTON_SetText(hItem, "stop");
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
	case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
				HEAT(1);  //�򿪹�̬�̵���
				led1(ON);
				heat_flag = 1;
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
				TEXT_SetTextColor(hItem,GUI_RED);
				TEXT_SetText(hItem,"heating");
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
				HEAT(0);  
				led1(OFF);
				heat_flag = 0;
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
				TEXT_SetTextColor(hItem,GUI_BLUE);
				TEXT_SetText(hItem,"stop");
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateFramewin
*/
WM_HWIN CreateFramewin(void);
WM_HWIN CreateFramewin(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
