#include "SensorProbe.h"


int  SensorProbe_GetTemperature()
{
	// �Ʒ��� �ڵ�� target ȯ���� �ƴϸ� �������� �ʴ´�.
	return *(int*)0x03EA;
}