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

void EEPROM_write(const u16 address, const u8 data)
{
    /* Wait for completion of previous write */
    while (1 == READ_BIT(EECR, EEWE));

    /* Set up address and data registers */
    EEAR = address;
    EEDR = data;

    /* Write logical one to EEMWE */
    SET_BIT(EECR, EEMWE);

    /* Start EEPROM write by setting EEWE */
    SET_BIT(EECR, EEWE);
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