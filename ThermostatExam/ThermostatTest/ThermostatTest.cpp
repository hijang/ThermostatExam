#include "CppUTest/TestHarness.h"


TEST_GROUP(Thermostat)
{
};

TEST(Thermostat, initState)
{
	// 온도조절기가 켜진 직후
	Thermostat_Create();

	// 제어판 동작 LED는 꺼져있다.
	CHECK_EQUAL(CONTROL_LED_OFF, ControlPanel_GetLEDState());


	Thermostat_Destroy();
}