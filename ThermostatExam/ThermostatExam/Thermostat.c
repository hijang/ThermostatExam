#include "Thermostat.h"

#include "HeaterController.h"
#include "CoolerController.h"
#include "SensorProbe.h"
#include "FanController.h"

#include <math.h>




/* MACRO DEFINE */
#define __UMEM8(addr)  (*((volatile unsigned char  *)addr))
#define __UMEM16(addr) (*((volatile unsigned short *)addr))

#define TIMER16CA	__UMEM16(0xA308)
#define	TIMER10BC_W	__UMEM16(0x0000A254)

void  initializeTargetSpecifics()
{
	// target 환경이 아니면 아래 코드는 동작하지 않는다.
	TIMER16CA = (unsigned short)0x1031;		/* Duty Load					*/
	TIMER10BC_W |= 0x0080;						/* Enable timer operation	*/
}


static int  desiredTemperature_ = 0;

void  Thermostat_Create()
{
	initializeTargetSpecifics();

	HeaterController_TurnOff();
	CoolerController_TurnOff();

	desiredTemperature_ = -1;  // unset
}

void  Thermostat_Destroy()
{
}

void  Thermostat_SetDesiredTemperature(int  desired)
{
	desiredTemperature_ = desired;
}


/*
// 좋지 않은 구현.
// 버그 존재
void  Thermostat_Wakeup()
{
	static int  wasHeaterOrCooler;  // 전 상태가 heater가 켜져있었다면 0, cooler가 켜져있었다면 1
	const int  currentTemperature = SensorProbe_GetTemperature();

	if ( currentTemperature == desiredTemperature_ )
	{
		if ( wasHeaterOrCooler == 0 )
		{
			HeaterController_TurnOff();
		}
		else if ( wasHeaterOrCooler == 1 )
		{
			CoolerController_TurnOff();	
		}
		else
		{
		}		
	}
	else
	{
		if ( currentTemperature < desiredTemperature_ )
		{
			// 온도가 높으면 히터 가동
			HeaterController_TurnOn();
			wasHeaterOrCooler = 0;

			if ( desiredTemperature_ - currentTemperature > 10 )
			{
				FanController_SetFanSpeed(500);
			}
			else if ( desiredTemperature_ - currentTemperature > 2 )
			{
				FanController_SetFanSpeed(200);
			}
			else
			{
				FanController_SetFanSpeed(0);
			}
		}
		else
		{
			// 온도가 낮으면 쿨러 가동
			CoolerController_TurnOn();
			wasHeaterOrCooler = 1;

			if ( currentTemperature - desiredTemperature_ > 10 )
			{
				FanController_SetFanSpeed(500);
			}
			else if ( currentTemperature - desiredTemperature_ >= 2 )
			{
				FanController_SetFanSpeed(200);
			}
			else
			{
				FanController_SetFanSpeed(0);
			}
		}
	}
}
*/


static 
unsigned short  determinFanSpeed(int  differential)
{
	if (differential <= 2)
		return 0;

	return (differential > 10) ? 500 : 200;
}

void  Thermostat_Wakeup()
{
	const int  currentTemperature = SensorProbe_GetTemperature();
	const int  differential = abs(currentTemperature - desiredTemperature_);

	void (*heaterAction)() = HeaterController_TurnOff;
	void (*coolerAction)() = CoolerController_TurnOff;
	
	if (differential != 0)
	{
		if (currentTemperature < desiredTemperature_)
			heaterAction = HeaterController_TurnOn;
		else
			coolerAction = CoolerController_TurnOn;
	}

	heaterAction();
	coolerAction();
	FanController_SetFanSpeed( determinFanSpeed(differential) );	
}