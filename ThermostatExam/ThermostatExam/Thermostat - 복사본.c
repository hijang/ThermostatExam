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

void  Thermostat_Wakeup()
{
	const int  currentTemperature = SensorProbe_GetTemperature();

	if ( currentTemperature == desiredTemperature_ )
		HeaterController_TurnOff();
	
	if ( currentTemperature < desiredTemperature_ )
		HeaterController_TurnOn();
	else
		CoolerController_TurnOn();

	if ( abs(currentTemperature - desiredTemperature_) > 10 )
		FanController_SetFanSpeed(500);
	else
		FanController_SetFanSpeed(200);

	if ( abs(currentTemperature - desiredTemperature_) <= 2 )
		FanController_SetFanSpeed(0);
}
