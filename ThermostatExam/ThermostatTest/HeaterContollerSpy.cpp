
extern "C"
{
#include "HeaterControllerSpy.h"
}

namespace
{
	int  lastHeaterState = HEATER_UNINITIALIZED;
}

void  HeaterControllerSpy_Create()
{
	lastHeaterState = HEATER_UNINITIALIZED;
}

void  HeaterControllerSpy_Destroy(){}

int  HeaterControllerSpy_GetLastState()
{
	return lastHeaterState;
}


void  HeaterController_TurnOn()
{
	lastHeaterState = HEATER_ON;
}

void  HeaterController_TurnOff()
{
	lastHeaterState = HEATER_OFF;
}
