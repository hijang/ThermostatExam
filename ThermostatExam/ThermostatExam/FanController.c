#include "FanController.h"


void  FanController_SetFanSpeed(unsigned short  speed)
{
// target 환경이 아니면 아래의 코드가 동작하지 않는다.
	*((unsigned short*)0x01EE) = speed;
}