#include "CppUTest/TestHarness.h"


TEST_GROUP(Thermostat)
{
};

TEST(Thermostat, initState)
{
	// �µ������Ⱑ ���� ����
	Thermostat_Create();

	// ������ ���� LED�� �����ִ�.
	CHECK_EQUAL(CONTROL_LED_OFF, ControlPanel_GetLEDState());


	Thermostat_Destroy();
}