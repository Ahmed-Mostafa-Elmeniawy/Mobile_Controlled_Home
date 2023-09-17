/*
 * Buzzer.c
 *
 *  Created on: Aug 6, 2023
 *      Author: mirage
 */

#include "Buzzer.h"
#include "Dio.h"
#include "Gpt.h"
#include "Types.h"


void Buzzer_Init(void)
{
	Dio_SetPinMode(BUZZER_CONFIG, DIO_MODE_OUTPUT);
}

/*Use it in a loop*/
void Buzzer_TurnOn(u16 delay_ms)
{

	Dio_SetPinLevel(BUZZER_CONFIG, DIO_LEVEL_HIGH);

	Gpt_Delay(delay_ms);

	Dio_SetPinLevel(BUZZER_CONFIG, DIO_LEVEL_LOW);

	Gpt_Delay(delay_ms);

}


void Buzzer_TurnOff(void)
{
	Dio_SetPinLevel(BUZZER_CONFIG, DIO_LEVEL_LOW);
}

