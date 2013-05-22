#include "CppUTest/TestHarness.h"

extern "C"
{
#include "Thermostat.h"
#include "ContolPanelSpy.h"
}




TEST_GROUP(Thermostat)
{
};

TEST(Thermostat, LEDShouldBeOffWhenInitialState)
{
	// �µ������Ⱑ ���� ����
	Thermostat_Create();

	// ������ ���� LED�� �����ִ�.
	CHECK_EQUAL(CONTROL_LED_OFF, ControlPanelSpy_GetLastLEDState());


	Thermostat_Destroy();
}