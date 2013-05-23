#include "SensorProbe.h"


int  SensorProbe_GetTemperature()
{
	// 아래의 코드는 target 환경이 아니면 동작하지 않는다.
	return *(int*)0x03EA;
}