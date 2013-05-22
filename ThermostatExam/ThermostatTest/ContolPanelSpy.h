#ifndef __CONTROLPANELSPY_H__
#define __CONTROLPANELSPY_H__

#include "ControlPanel.h"

enum
{
	CONTROL_LED_UNINITIALIZED = 0,
	CONTROL_LED_OFF = 10, 
	CONTROL_LED_GREEN,
	CONTROL_LED_RED,
};

int  ControlPanelSpy_GetLastLEDState();


#endif // !__CONTROLPANELSPY_H__
