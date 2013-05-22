
extern "C"
{
#include "ContolPanelSpy.h"
}

namespace
{
	int  lastLEDState = CONTROL_LED_UNINITIALIZED;
}

void  ContolPanel_TurnGreenLED()
{
	
}

void  ContolPanel_TurnRedLED()
{
	
}

void  ContolPanel_TurnOffLED()
{
	lastLEDState = CONTROL_LED_OFF;
}



int  ControlPanelSpy_GetLastLEDState()
{
	return lastLEDState;
}