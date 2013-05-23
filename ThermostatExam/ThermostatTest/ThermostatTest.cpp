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
	// 온도조절기가 켜진 직후
	
	
	// 히터와 쿨러는 모두 꺼져있다.
	CHECK_EQUAL(HEATER_OFF, HeaterControllerSpy_GetLastState());
	CHECK_EQUAL(COOLER_OFF, CoolerControllerSpy_GetLastState());
}


TEST(Thermostat, HeaterShouldBeOnWhenTemperatureIsLowerThanDesired)
{
	// 설정 온도가 20도 인데
	Thermostat_SetDesiredTemperature(20);
	
	// 현재 실내 온도가 10도 이면
	FakeSensorProbe_SetTemperature(10);

	Thermostat_Wakeup();

	// 히터가 가동되어야 한다.
	CHECK_EQUAL(HEATER_ON, HeaterControllerSpy_GetLastState());
}

TEST(Thermostat, FanShouldRunFastWhenHighDifferential)
{
	Thermostat_SetDesiredTemperature(20);
	
	FakeSensorProbe_SetTemperature(5);

	Thermostat_Wakeup();

	//송풍팬이 강모드로 돌아야 한다.
	CHECK_EQUAL(500, FanControllerSpy_GetFanSpeed());
}

TEST(Thermostat, FanShouldRunSlowWhenLowDifferential)
{
	Thermostat_SetDesiredTemperature(20);
		
	FakeSensorProbe_SetTemperature(17);

	Thermostat_Wakeup();

	//송풍팬이 약모드로 돌아야 한다.
	CHECK_EQUAL(200, FanControllerSpy_GetFanSpeed());
}


TEST(Thermostat, FanShouldStopWhenVeryLowDifferential)
{
	Thermostat_SetDesiredTemperature(20);
		
	FakeSensorProbe_SetTemperature(19);

	Thermostat_Wakeup();

	//송풍팬이 돌지 않아야한다.
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
	// 설정 온도가 20도 인데
	Thermostat_SetDesiredTemperature(20);
	
	// 현재 실내 온도가 30도 이면
	FakeSensorProbe_SetTemperature(30);

	Thermostat_Wakeup();

	// 쿨러가 가동되어야 한다.
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

