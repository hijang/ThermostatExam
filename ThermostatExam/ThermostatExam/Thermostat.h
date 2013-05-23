#ifndef __THERMOSTAT_H__
#define __THERMOSTAT_H__

void  Thermostat_Create();
void  Thermostat_Destroy();



void  Thermostat_SetDesiredTemperature(int  desired);
void  Thermostat_Wakeup();

#endif // !__THERMOSTAT_H__
