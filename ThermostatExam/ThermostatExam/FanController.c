#include "FanController.h"


void  FanController_SetFanSpeed(unsigned short  speed)
{
// target ȯ���� �ƴϸ� �Ʒ��� �ڵ尡 �������� �ʴ´�.
	*((unsigned short*)0x01EE) = speed;
}