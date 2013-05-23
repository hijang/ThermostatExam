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

	void  whenTemperatureIs(int  temperature)
	{
		FakeSensorProbe_SetTemperature(temperature);

		Thermostat_Wakeup();
	}

	void  heaterShouldBeOff()
	{
		CHECK_EQUAL(HEATER_OFF, HeaterControllerSpy_GetLastState());
	}

	void  heaterShouldBeOnAndRotateOf(int  speed)
	{
		CHECK_EQUAL(COOLER_OFF, CoolerControllerSpy_GetLastState());
		CHECK_EQUAL(HEATER_ON, HeaterControllerSpy_GetLastState());
		CHECK_EQUAL(speed, FanControllerSpy_GetFanSpeed());
	}

	void  coolerShouldBeOff()
	{
		CHECK_EQUAL(COOLER_OFF, CoolerControllerSpy_GetLastState());
	}

	void  coolerShouldBeOnAndRotateOf(int  speed)
	{
		CHECK_EQUAL(HEATER_OFF, HeaterControllerSpy_GetLastState());
		CHECK_EQUAL(COOLER_ON, CoolerControllerSpy_GetLastState());
		CHECK_EQUAL(speed, FanControllerSpy_GetFanSpeed());
	}
};

TEST(Thermostat, LEDShouldBeOffWhenInitialState)
{
	// 온도조절기가 켜진 직후	
	
	heaterShouldBeOff();
	coolerShouldBeOff();
}


TEST(Thermostat, HeaterShouldBeOnWhenTemperatureIsLowerThanDesired)
{
	Thermostat_SetDesiredTemperature(20);
	
	whenTemperatureIs(10);

	heaterShouldBeOnAndRotateOf(200);
}

TEST(Thermostat, FanShouldRunFastWhenHighDifferential)
{
	Thermostat_SetDesiredTemperature(20);
	
	whenTemperatureIs(5);
	
	heaterShouldBeOnAndRotateOf(500);
}

TEST(Thermostat, FanShouldRunSlowWhenLowDifferential)
{
	Thermostat_SetDesiredTemperature(20);
		
	whenTemperatureIs(17);

	heaterShouldBeOnAndRotateOf(200);
}


TEST(Thermostat, FanShouldStopWhenVeryLowDifferential)
{
	Thermostat_SetDesiredTemperature(20);
		
	whenTemperatureIs(19);

	heaterShouldBeOnAndRotateOf(0); // 송풍팬은 정지.
}

TEST(Thermostat, HeaterTurnOnAndThenOff)
{
	Thermostat_SetDesiredTemperature(20);
		
	whenTemperatureIs(10);

	heaterShouldBeOnAndRotateOf(200);

	// and
	whenTemperatureIs(20);

	heaterShouldBeOff();
}

TEST(Thermostat, CoolerTurnOnAndThenOff)
{
	Thermostat_SetDesiredTemperature(20);
		
	whenTemperatureIs(30);

	coolerShouldBeOnAndRotateOf(200);


	whenTemperatureIs(20);

	coolerShouldBeOff();
}




TEST(Thermostat, CoolerShouldBeOnWhenTemperatureIsHigherThanDesired)
{
	Thermostat_SetDesiredTemperature(20);
	
	whenTemperatureIs(30);
	
	coolerShouldBeOnAndRotateOf(200);
}


TEST(Thermostat, CoolerTurnOnAndThenHeaterTrunOn)
{
	Thermostat_SetDesiredTemperature(20);
		
	whenTemperatureIs(30);

	coolerShouldBeOnAndRotateOf(200);


	whenTemperatureIs(10);

	heaterShouldBeOnAndRotateOf(200);
}

