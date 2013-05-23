#include "CppUTest/TestHarness.h"

extern "C"
{
#include "Thermostat.h"

#include "HeaterControllerSpy.h"
#include "CoolerControllerSpy.h"
#include "FakeSensorProbe.h"
#include "FanControllerSpy.h"
}




TEST_GROUP(Thermostat)
{
	void  setup()
	{
		HeaterControllerSpy_Create();
		CoolerControllerSpy_Create();
		FakeSensorProbe_Create();
		FanControllerSpy_Create();

		Thermostat_Create();
	}

	void  teardown()
	{
		Thermostat_Destroy();
	}
};

TEST(Thermostat, LEDShouldBeOffWhenInitialState)
{
	// �µ������Ⱑ ���� ����
	
	
	// ���Ϳ� �𷯴� ��� �����ִ�.
	CHECK_EQUAL(HEATER_OFF, HeaterControllerSpy_GetLastState());
	CHECK_EQUAL(COOLER_OFF, CoolerControllerSpy_GetLastState());
}


TEST(Thermostat, HeaterShouldBeOnWhenTemperatureIsLowerThanDesired)
{
	// ���� �µ��� 20�� �ε�
	Thermostat_SetDesiredTemperature(20);
	
	// ���� �ǳ� �µ��� 10�� �̸�
	FakeSensorProbe_SetTemperature(10);

	Thermostat_Wakeup();

	// ���Ͱ� �����Ǿ�� �Ѵ�.
	CHECK_EQUAL(HEATER_ON, HeaterControllerSpy_GetLastState());
}

TEST(Thermostat, FanShouldRunFastWhenHighDifferential)
{
	Thermostat_SetDesiredTemperature(20);
	
	FakeSensorProbe_SetTemperature(5);

	Thermostat_Wakeup();

	//��ǳ���� ������ ���ƾ� �Ѵ�.
	CHECK_EQUAL(500, FanControllerSpy_GetFanSpeed());
}

TEST(Thermostat, FanShouldRunSlowWhenLowDifferential)
{
	Thermostat_SetDesiredTemperature(20);
		
	FakeSensorProbe_SetTemperature(17);

	Thermostat_Wakeup();

	//��ǳ���� ����� ���ƾ� �Ѵ�.
	CHECK_EQUAL(200, FanControllerSpy_GetFanSpeed());
}


TEST(Thermostat, FanShouldStopWhenVeryLowDifferential)
{
	Thermostat_SetDesiredTemperature(20);
		
	FakeSensorProbe_SetTemperature(19);

	Thermostat_Wakeup();

	//��ǳ���� ���� �ʾƾ��Ѵ�.
	CHECK_EQUAL(0, FanControllerSpy_GetFanSpeed());
}

TEST(Thermostat, HeaterTurnOnAndThenOff)
{
	Thermostat_SetDesiredTemperature(20);
		
	FakeSensorProbe_SetTemperature(10);
	Thermostat_Wakeup();

	CHECK_EQUAL(HEATER_ON, HeaterControllerSpy_GetLastState());

	FakeSensorProbe_SetTemperature(20);
	Thermostat_Wakeup();

	CHECK_EQUAL(HEATER_OFF, HeaterControllerSpy_GetLastState());
	CHECK_EQUAL(0, FanControllerSpy_GetFanSpeed());
}

TEST(Thermostat, CoolerTurnOnAndThenOff)
{
	Thermostat_SetDesiredTemperature(20);
		
	FakeSensorProbe_SetTemperature(30);
	Thermostat_Wakeup();

	CHECK_EQUAL(COOLER_ON, CoolerControllerSpy_GetLastState());

	FakeSensorProbe_SetTemperature(20);
	Thermostat_Wakeup();

	CHECK_EQUAL(COOLER_OFF, CoolerControllerSpy_GetLastState());
	CHECK_EQUAL(0, FanControllerSpy_GetFanSpeed());
}




TEST(Thermostat, CoolerShouldBeOnWhenTemperatureIsHigherThanDesired)
{
	// ���� �µ��� 20�� �ε�
	Thermostat_SetDesiredTemperature(20);
	
	// ���� �ǳ� �µ��� 30�� �̸�
	FakeSensorProbe_SetTemperature(30);

	Thermostat_Wakeup();

	// �𷯰� �����Ǿ�� �Ѵ�.
	CHECK_EQUAL(COOLER_ON, CoolerControllerSpy_GetLastState());
}


TEST(Thermostat, CoolerTurnOnAndThenHeaterTrunOn)
{
	Thermostat_SetDesiredTemperature(20);
		
	FakeSensorProbe_SetTemperature(30);
	Thermostat_Wakeup();

	CHECK_EQUAL(COOLER_ON, CoolerControllerSpy_GetLastState());
	CHECK_EQUAL(HEATER_OFF, HeaterControllerSpy_GetLastState());

	FakeSensorProbe_SetTemperature(10);
	Thermostat_Wakeup();

	CHECK_EQUAL(COOLER_OFF, CoolerControllerSpy_GetLastState());
	CHECK_EQUAL(HEATER_ON, HeaterControllerSpy_GetLastState());
}

