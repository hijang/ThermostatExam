#include "CoolerController.h"


void  CoolerController_TurnOn()
{
	// target ȯ���� �ƴϸ� �Ʒ��� �ڵ尡 �������� �ʴ´�.
	*((unsigned short*)0x01EE) |= (1 << 5);
}

void  CoolerController_TurnOff()
{
	// target ȯ���� �ƴϸ� �Ʒ��� �ڵ尡 �������� �ʴ´�.
	*((unsigned short*)0x01EE) &= ~(1 << 5);
}