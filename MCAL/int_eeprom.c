/**
 * @file int_eeprom.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief EEPROM driver implementation
 * @version 0.1
 * @date 15-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "int_eeprom.h"

static void (*eeprom_rdy_fPtr)(void) = NULLPTR;

void EEPROM_write(const u16 address, const u8 data)
{
    /* Wait for completion of previous write */
    while (1 == READ_BIT(EECR, EEWE));

    /* Set up address and data registers */
    EEAR = address;
    EEDR = data;

    /* disable global interrupt */
    cli();

    /* Write logical one to EEMWE */
    SET_BIT(EECR, EEMWE);

    /* Start EEPROM write by setting EEWE--> must be done withing four clock cycles
    *  after setting EEMWE so I use cli() and sei() 
    */
    SET_BIT(EECR, EEWE);

    /* enable global interrupt */
    sei();
}

u8 EEPROM_read(const u16 address)
{
    /* Wait for completion of previous write */
    while (1 == READ_BIT(EECR, EEWE));

    /* Set up address register */
    EEAR = address;

    /* Start EEPROM read by writing EERE */
    SET_BIT(EECR, EERE);

    /* Return data from data register */
    return EEDR;
}

void EEPROM_intEnable(void)
{
    SET_BIT(EECR, EERIE);
}

void EEPROM_intDisable(void)
{
    CLR_BIT(EECR, EERIE);
}

void EEPROM_intSetCallback(void (*localFptr)(void))
{
    eeprom_rdy_fPtr = localFptr;
}

ISR(EE_RDY_VECT)
{
    if (eeprom_rdy_fPtr != NULLPTR)
    {
        eeprom_rdy_fPtr();
    }
}