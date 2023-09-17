/*
 * main.c
 *
 *  Created on: Jan 27, 2023
 *      Author: ahmad
 */

#include "Types.h"
#include "Macros.h"
#include "Registers.h"
#include "Dio.h"
#include "Led.h"
#include "Button.h"
#include "Ssd.h"
#include "Lcd.h"
#include "Keypad.h"
#include "ExtInt.h"
#include "Gie.h"
#include "Adc.h"
#include "Interrupts.h"
#include "Gpt.h"
#include "Pwm.h"
#include "Icu.h"
#include "I2c.h"
#include "Wdt.h"
#include "Uart.h"
#include "Eeprom.h"
#include "Buzzer.h"
#include "Solenoid_Locker.h"
#include "Bluetooth_Module.h"
#include "Delay.h"

#define MOBILE_CONTROLLED_HOME  1

u8 Passwords_Data[10][4] = {
	"100",
	"111",
	"122",
	"133",
	"144",
	"155",
	"166",
	"177",
	"188",
	"199"
};

int main(void)
{
	// IMT Graduation Project
#if MOBILE_CONTROLLED_HOME

	u8 data_received = 0;
	u8 password[4] = {};
	u8 Wrong_Number_Count = 0;
	u8 i = 0, j = 0, leave_room = 0;
	u8 count_error = 0;


	Led_Init(LED_PIN);
	Solenoid_Locker_Init();
	Buzzer_Init();
	Bluetooth_Module_Init();

	Solenoid_Locker_Close();

	while (1)
	{
		// Initializing i and j every loop
		i = 0;
		j = 0;

		Bluetooth_Module_Send_String((u8*)"Please Enter Your Password\n");

		do
		{
			password[i] = Bluetooth_Module_Receive();

			j = password[i];

			Uart_Transmit(j);

			i++;

		} while (j != 'E');

		Bluetooth_Module_Send_String((u8*)"\n");

		password[3] = '\0'; /*In order to look like a string*/

		if (Wrong_Number_Count < 2)
		{
			Buzzer_TurnOff();

			/*Checking if the password in correct*/
			for (i = 0; i < 10; i++)
			{
				for (j = 0; j < 3; j++)
				{
					if (Passwords_Data[i][j] == password[j])
					{
						count_error = 0;
						//Bluetooth_Module_Send_String((u8*)"\n");
					}
					else
					{
						count_error = 1;
						break;
					}
				}

				if (count_error == 0)
				{
					break;
				}

			}

			/*Code for the correct password*/
			if (count_error == 0)
			{
				Wrong_Number_Count = 0;

				Bluetooth_Module_Send_String((u8*)"Correct Password\n");
				Bluetooth_Module_Send_String((u8*)"Do you want lights?\n");
				Bluetooth_Module_Send_String((u8*)"1 => For Yes\n");
				Bluetooth_Module_Send_String((u8*)"2 => For No\n");


				Solenoid_Locker_Open();
				data_received = Bluetooth_Module_Receive();


				switch (data_received)
				{
				case '1':
					Led_TurnOn(LED_PIN);
					break;
				case '2':
					Led_TurnOff(LED_PIN);
					break;
				default:
					break;
				}


				Bluetooth_Module_Send_String((u8*)"Do you want to leave the room?\n");
				Bluetooth_Module_Send_String((u8*)"Enter 1 for YES\n");
				Bluetooth_Module_Send_String((u8*)"Enter nothing to stay in the room\n");
				count_error = 0;
				while (count_error == 0)
				{
					leave_room = Bluetooth_Module_Receive();

					switch (leave_room)
					{
					case '1':
						Solenoid_Locker_Close();
						Led_TurnOff(LED_PIN);
						count_error = 1; // Leaving the while loop
						break;
					default:
						Bluetooth_Module_Send_String((u8*)"Enter a valid response\n");
						break;
					}
				}

			}
			else
			{
				/* Code for the wrong password */
				Bluetooth_Module_Send_String((u8*)"Wrong Password\n");
				Wrong_Number_Count++;
			}
		}
		else
		{
			Wrong_Number_Count = 0;

			Bluetooth_Module_Send_String((u8*)"You have reached your maximum number of tries\n");
			Bluetooth_Module_Send_String((u8*)"Wait for 4 seconds to try again\n");
			for (i = 0; i < 4; i++)
			{
				Buzzer_TurnOn(1000);
				Buzzer_TurnOff();
				Gpt_Delay(500);
			}
		}

	}

#endif

}