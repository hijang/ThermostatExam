#ifndef __HEATER_CONTROLLER_SPY_H___
#define __HEATER_CONTROLLER_SPY_H___

enum
{
	HEATER_UNINITIALIZED = 0,
	HEATER_OFF = 10, 
	HEATER_ON,	
};

void  HeaterControllerSpy_Create();
void  HeaterControllerSpy_Destroy();

int  HeaterControllerSpy_GetLastState();


void  HeaterController_TurnOn();
void  HeaterController_TurnOff();



#endif // !__HEATER_CONTROLLER_SPY_H___
