
#include "Types.h"
#include "Macros.h"
#include "Registers.h"
#include "I2c.h"





void I2c_MasterInit(u8 address)
{
	SET_BIT(TWCR, I2C_ENABLE_BIT);

	/* Setting the address of the master in case of multimaster systems */
	TWAR = (address << 1);
}

void I2c_SlaveInit(u8 address)
{
	SET_BIT(TWCR, I2C_ENABLE_BIT);

	/* Setting the address of the slave */
	TWAR = (address << 1);
}

I2c_StatusType I2c_SendStart()
{
	I2c_StatusType status = 0;

	/* Setting the prescaler bits to zero for checking the status */
	CLR_BIT(TWSR, I2C_PRESCALER_TWSR_BIT_0);
	CLR_BIT(TWSR, I2C_PRESCALER_TWSR_BIT_1);

	SET_BIT(TWCR, I2C_START_CONDITION_BIT);

	status = TWSR;

	return status; 
}

I2c_StatusType I2c_SendSlaveAddress(u8 address, I2c_RequestType request)
{
	I2c_StatusType status = 0;
 
	/* Setting the prescaler bits to zero for checking the status */
	CLR_BIT(TWSR, I2C_PRESCALER_TWSR_BIT_0);
	CLR_BIT(TWSR, I2C_PRESCALER_TWSR_BIT_1); 

	switch (request)
	{
	case I2C_REQUEST_WRITE:
		TWDR = ((address << 1) | I2C_REQUEST_WRITE);
		status = TWSR;
		break; 

	case I2C_REQUEST_READ:
		TWDR = ((address << 1) | I2C_REQUEST_READ);
		status = TWSR;
		break;

	default:
		break;
	}

	/* Clearing the interrupt flag to continue the transfer */
	SET_BIT(TWCR, I2C_INTERRUPT_FLAG);

	return status; 
}

I2c_StatusType I2c_WriteData(u8 data)
{
	I2c_StatusType status = 0;

	/* Setting the prescaler bits to zero for checking the status */
	CLR_BIT(TWSR, I2C_PRESCALER_TWSR_BIT_0);
	CLR_BIT(TWSR, I2C_PRESCALER_TWSR_BIT_1);

	/* Writing data into the data register */
	TWDR = data;

	status = TWSR;

	/* Clearing the interrupt flag to continue the transfer */
	SET_BIT(TWCR, I2C_INTERRUPT_FLAG);

	return status;
}

I2c_StatusType I2c_ReadData(u8* data)
{
	I2c_StatusType status = 0;

	/* Setting the prescaler bits to zero for checking the status */
	CLR_BIT(TWSR, I2C_PRESCALER_TWSR_BIT_0);
	CLR_BIT(TWSR, I2C_PRESCALER_TWSR_BIT_1);

	/* Reading data from the data register */
	*data = TWDR;

	status = TWSR;

	/* Clearing the interrupt flag to continue the transfer */
	SET_BIT(TWCR, I2C_INTERRUPT_FLAG);

	return status;
}

void I2c_SendStop(void)
{
	SET_BIT(TWCR, I2C_STOP_CONDITION_BIT);
}

void I2c_EnableAck(void)
{
	SET_BIT(TWCR, I2C_ENABLE_ACKNOWLEDGE_BIT);
}

void I2c_DisableAck(void)  
{
	CLR_BIT(TWCR, I2C_ENABLE_ACKNOWLEDGE_BIT);
}


