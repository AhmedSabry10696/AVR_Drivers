/**
 * @file I2C.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief I2C Driver implementation
 * @version 0.1
 * @date 28-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "I2C.h"

static void (*TWI_IntFptr)(void) = NULLPTR;

void TWI_Init(void)
{
    /* Bit rate: 400 KHZ */
    TWBR = 0x02;

    /* TWSR prescaler value */
    TWSR = 0x00;

    /* address: 1 and general-call off {bit 0} */
    TWAR = 0x20;

    /* enable TWI and ACK */
    TWCR = (1 << TWEN) | (1 << TWEA);
}

void TWI_Start(void)
{
    /* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    /* Wait for TWINT flag set in TWCR Register */
    while (0 == READ_BIT(TWCR, TWINT))
        ;
}

void TWI_Stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_Write(u8 data)
{
    /* Write data in TWI data register {while TWINT = 1}*/
    TWDR = data;

    /* 
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);

    /* Wait for TWINT flag set in TWCR Register */
    while (0 == READ_BIT(TWCR, TWINT))
        ;
}

u8 TWI_Read_With_ACK(void)
{
    /* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN = 1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    /* Wait for TWINT flag set in TWCR Register */
    while (0 == READ_BIT(TWCR, TWINT))
        ;

    /* Read Data */
    return TWDR;
}

u8 TWI_Read_With_NACK(void)
{
    /* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);

    /* Wait for TWINT flag set in TWCR Register */
    while (0 == READ_BIT(TWCR, TWINT))
        ;

    /* Read Data */
    return TWDR;
}

void TWI_FlagPolling(void)
{
    /* 
	 * Clear the TWINT flag TWINT=1
	 * Enable sending ACK TWEA=1
	 * Enable TWI Module TWEN = 1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    /* Wait for TWINT flag set in TWCR Register */
    while (0 == READ_BIT(TWCR, TWINT))
        ;
}

void TWI_IntEnable(void)
{
    SET_BIT(TWCR, TWIE);
}

void TWI_IntDisable(void)
{
    CLEAR_BIT(TWCR, TWIE);
}

void TWI_IntSetCallBack(void (*LocalFptr)(void))
{
    TWI_IntFptr = LocalFptr;
}

ISR(TWI_VECT)
{
    if (TWI_IntFptr != NULLPTR)
    {
        TWI_IntFptr();
    }
}