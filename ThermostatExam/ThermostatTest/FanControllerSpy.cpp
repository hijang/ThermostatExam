extern "C"
{
#include "FanControllerSpy.h"
#include "FanController.h"
}


namespace
{
	unsigned short  currentFanSpeed_ = 0;
}

void  FanControllerSpy_Create()
{
	currentFanSpeed_ = 0;
}

void  FanControllerSpy_Destroy() {}

int  FanControllerSpy_GetFanSpeed()
{
	return currentFanSpeed_;
}

void  FanController_SetFanSpeed(unsigned short  speed)
{
	currentFanSpeed_ = speed;
}