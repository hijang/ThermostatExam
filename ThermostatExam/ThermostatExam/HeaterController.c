#include "HeaterController.h"


void  HeaterController_TurnOn()
{
	// target 환경이 아니면 아래의 코드가 동작하지 않는다.
	*((unsigned short*)0x01EE) |= (1 << 4);
}

void  HeaterController_TurnOff()
{
	// target 환경이 아니면 아래의 코드가 동작하지 않는다.
	*((unsigned short*)0x01EE) &= ~(1 << 4);
}