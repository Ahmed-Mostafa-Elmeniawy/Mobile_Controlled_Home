/*
 * Bluetooth_Module.h
 *
 *  Created on: Aug 6, 2023
 *      Author: mirage
 */

#ifndef INC_BLUETOOTH_MODULE_H_
#define INC_BLUETOOTH_MODULE_H_

#include "Types.h"

void Bluetooth_Module_Init(void);
void Bluetooth_Module_Send_String(u8 *data);
u8 Bluetooth_Module_Receive(void);

#endif /* INC_BLUETOOTH_MODULE_H_ */
