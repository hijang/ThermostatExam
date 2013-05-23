
extern "C"
{
#include "CoolerControllerSpy.h"
}

namespace
{
	int  lastCoolerState = COOLER_UNINITIALIZED;
}

void  CoolerControllerSpy_Create()
{
	lastCoolerState = COOLER_UNINITIALIZED;
}

void  CoolerControllerSpy_Destroy(){}

int  CoolerControllerSpy_GetLastState()
{
	return lastCoolerState;
}


void  CoolerController_TurnOn()
{
	lastCoolerState = COOLER_ON;
}

void  CoolerController_TurnOff()
{
	lastCoolerState = COOLER_OFF;
}