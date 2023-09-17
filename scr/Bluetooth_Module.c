/*
 * Bluetooth_Module.c
 *
 *  Created on: Aug 6, 2023
 *      Author: mirage
 */

#include "Bluetooth_Module.h"
#include "Uart.h"
#include "Types.h"


void Bluetooth_Module_Init(void)
{
	Uart_Init();
}

void Bluetooth_Module_Send_String(u8* data)
{
	Uart_Transmit_String(data);
}

u8 Bluetooth_Module_Receive(void)
{
	u8 data = Uart_Receive();

	return data;
}