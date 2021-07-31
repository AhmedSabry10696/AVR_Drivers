/**
 * @file EXT_EEPROM.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief External EEPROM driver implementation
 * @version 0.1
 * @date 30-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "EXT_EEPROM.h"

void EEPROM_Init(void)
{
    /* address of the controller in case it used as slave */
    TWI_Init(0x40);
}

EEPROM_Error_type EEPROM_Write_Byte(u16 address, u8 data)
{
    TWI_Error_type local = TWI_OK;

    local = TWI_Start();
    if (local != TWI_OK)
    {
        return ERROR;
    }

    local = TWI_Write_SLA_Write((u8)(0x50 | ((address & 0x0700) >> 8)));
    if (local != TWI_OK)
    {
        return ERROR;
    }

    local = TWI_WriteByte((u8)(address));
    if (local != TWI_OK)
    {
        return ERROR;
    }

    local = TWI_WriteByte(data);
    if (local != TWI_OK)
    {
        return ERROR;
    }

    TWI_Stop();

    return SUCCESS;
}

EEPROM_Error_type EEPROM_Read_Byte(u16 address, u8 *data)
{
    TWI_Error_type local = TWI_OK;

    local = TWI_Start();
    if (local != TWI_OK)
    {
        return ERROR;
    }

    local = TWI_Write_SLA_Write((u8)(0x50 | ((address & 0x0700) >> 8)));
    if (local != TWI_OK)
    {
        return ERROR;
    }

    local = TWI_WriteByte((u8)(address));
    if (local != TWI_OK)
    {
        return ERROR;
    }

    local = TWI_RepStart();
    if (local != TWI_OK)
    {
        return ERROR;
    }

    local = TWI_Write_SLA_Read((u8)(0x50 | ((address & 0x0700) >> 8)));
    if (local != TWI_OK)
    {
        return ERROR;
    }
    
    local = TWI_ReadByte(data);
    if (local != TWI_OK)
    {
        return ERROR;
    }

    TWI_Stop();

    return SUCCESS;
}