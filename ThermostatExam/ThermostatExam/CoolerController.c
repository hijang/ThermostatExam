#include "CoolerController.h"


void  CoolerController_TurnOn()
{
	// target 환경이 아니면 아래의 코드가 동작하지 않는다.
	*((unsigned short*)0x01EE) |= (1 << 5);
}

void  CoolerController_TurnOff()
{
	// target 환경이 아니면 아래의 코드가 동작하지 않는다.
	*((unsigned short*)0x01EE) &= ~(1 << 5);
}