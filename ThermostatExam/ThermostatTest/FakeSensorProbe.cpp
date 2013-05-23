extern "C"
{
#include "FakeSensorProbe.h"

#include "SensorProbe.h"
}


namespace
{
	int  currentTemperature_ = -1;
}

void  FakeSensorProbe_Create()
{
	currentTemperature_ = -1;
}

void  FakeSensorProbe_Destroy() {}


void  FakeSensorProbe_SetTemperature(int  temperature)
{
	currentTemperature_ = temperature;
}


int  SensorProbe_GetTemperature()
{
	return currentTemperature_;
}