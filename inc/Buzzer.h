/*
 * Buzzer.h
 *
 *  Created on: Aug 6, 2023
 *      Author: mirage
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "Dio.h"
#include "Types.h"

#define BUZZER_CONFIG	DIO_PORTD,DIO_PIN6

void Buzzer_Init(void);
void Buzzer_TurnOn(u16 delay_ms);
void Buzzer_TurnOff(void);


#endif /* INC_BUZZER_H_ */
