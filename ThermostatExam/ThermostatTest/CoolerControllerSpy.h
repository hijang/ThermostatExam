#ifndef __COOLER_CONTROLLER_SPY_H__
#define __COOLER_CONTROLLER_SPY_H__


enum
{
	COOLER_UNINITIALIZED = 0,
	COOLER_OFF = 10, 
	COOLER_ON,	
};

void  CoolerControllerSpy_Create();
void  CoolerControllerSpy_Destroy();

int  CoolerControllerSpy_GetLastState();


void  CoolerController_TurnOn();
void  CoolerController_TurnOff();


#endif // !__COOLER_CONTROLLER_SPY_H__
