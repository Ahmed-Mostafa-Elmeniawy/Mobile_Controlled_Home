/*
 * Solenoid_Locker.c
 *
 *  Created on: Aug 6, 2023
 *      Author: mirage
 */

#include "Solenoid_Locker.h"
#include "Dio.h"


void Solenoid_Locker_Init(void)
{
	Dio_SetPinMode(SOLENOID_LOCKER_CONFIG, DIO_MODE_OUTPUT);
}

void Solenoid_Locker_Open(void)
{
	Dio_SetPinLevel(SOLENOID_LOCKER_CONFIG, DIO_LEVEL_LOW);
}

void Solenoid_Locker_Close(void)
{
	Dio_SetPinLevel(SOLENOID_LOCKER_CONFIG, DIO_LEVEL_HIGH);
}
