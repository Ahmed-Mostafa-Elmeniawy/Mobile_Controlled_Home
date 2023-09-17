/*
 * Solenoid_Locker.h
 *
 *  Created on: Aug 6, 2023
 *      Author: mirage
 */

#ifndef INC_SOLENOID_LOCKER_H_
#define INC_SOLENOID_LOCKER_H_

#include "Dio.h"
#include "Types.h"

#define SOLENOID_LOCKER_CONFIG		DIO_PORTA,DIO_PIN0

void Solenoid_Locker_Init(void);
void Solenoid_Locker_Open(void);
void Solenoid_Locker_Close(void);


#endif /* INC_SOLENOID_LOCKER_H_ */
