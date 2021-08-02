/**
 * @file ext_eeprom.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief External EEPROM driver implementation
 * @version 0.1
 * @date 30-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ext_eeprom.h"

void EEPROM_init(void)
{
    /* address of the controller in case it used as slave */
    TWI_init(0x40);
}

EEPROM_Error_type EEPROM_writeByte(u16 address, u8 data)
{
    TwiError_type local = TWI_OK;

    /* send start condition */
    local = TWI_start();

    /* if failed return error code */
    if (local != TWI_OK)
    {
        return ERROR;
    }

    /* send slave address with write request
    * {0101 0000} | {0000 0 A9 A8 A7} = {0101 0987} 
    * in function shifted left 1010 987{0} write      
    */ 
    local = TWI_write_SLA_write((u8)(0x50 | ((address & 0x0700) >> 8)));
    
    /* if failed return error code */
    if (local != TWI_OK)
    {
        return ERROR;    
    }

    /* send second byte of address */
    local = TWI_writeByte((u8)(address));
    if (local != TWI_OK)
    {
        return ERROR;
    }

    /* send byte to write in address */
    local = TWI_writeByte(data);
    /* if failed, return error */
    if (local != TWI_OK)
    {
        return ERROR;
    }

    /* send stop condition */
    TWI_stop();

    /* return success */
    return SUCCESS;
}

EEPROM_Error_type EEPROM_readByte(u16 address, u8 *data_ptr)
{
    TwiError_type local = TWI_OK;

    /* send start condition */
    local = TWI_start();
    /* return error if failed */
    if (local != TWI_OK)
    {
        return ERROR;
    }

    /* send slave address with write request */
    local = TWI_write_SLA_write((u8)(0x50 | ((address & 0x0700) >> 8)));
    /* return error if failed */
    if (local != TWI_OK)
    {
        return ERROR;
    }

    /* send second byte of the address */
    local = TWI_writeByte((u8)(address));
    /* return error if failed */
    if (local != TWI_OK)
    {
        return ERROR;
    }

    /* send repeated start condition */
    local = TWI_repStart();
    /* return error if failed */
    if (local != TWI_OK)
    {
        return ERROR;
    }

    /* send slave address with read request */
    local = TWI_write_SLA_read((u8)(0x50 | ((address & 0x0700) >> 8)));
    /* return error if failed */
    if (local != TWI_OK)
    {
        return ERROR;
    }
    
    /* read byte */
    local = TWI_readByte(data_ptr);
    /* return error if failed */
    if (local != TWI_OK)
    {
        return ERROR;
    }

    /* send stop condition */
    TWI_stop();

    /* return success */
    return SUCCESS;
}
