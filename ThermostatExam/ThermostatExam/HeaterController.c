#include "HeaterController.h"


void  HeaterController_TurnOn()
{
	// target ȯ���� �ƴϸ� �Ʒ��� �ڵ尡 �������� �ʴ´�.
	*((unsigned short*)0x01EE) |= (1 << 4);
}

void  HeaterController_TurnOff()
{
	// target ȯ���� �ƴϸ� �Ʒ��� �ڵ尡 �������� �ʴ´�.
	*((unsigned short*)0x01EE) &= ~(1 << 4);
}