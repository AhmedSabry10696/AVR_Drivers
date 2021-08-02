/**
 * @file i2c_services.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief I2C services implementation
 * @version 0.1
 * @date 29-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "i2c_services.h"

TwiError_type TWI_masterSendByte(u8 address, u8 data)
{
    TwiError_type local = TWI_OK;
    
    /* send start condition */
    local = TWI_start();
    if (local != TWI_OK)
    {
        return local;
    }
    
    /* I2C terminal in proteus write address with no shift {bit 0 R/W}*/
    local = TWI_write_SLA_write(address);
    if (local != TWI_OK)
    {
        return local;
    }
    
    /* send byte */
    local = TWI_writeByte(data);
    if (local != TWI_OK)
    {
        return local;
    }
    
    /* send stop condition */
    TWI_stop();

    /* Byte sent successfully */
    return local;
}

TwiError_type TWI_masterReceiveByte(u8 address, u8 *data_ptr)
{
    TwiError_type local = TWI_OK;
    
    /* send start condition */
    local = TWI_start();
    if (local != TWI_OK)
    {
        return local;
    }
    
    /* send slave address + read */
    local = TWI_write_SLA_read(address);
    if (local != TWI_OK)
    {
        return local;
    }

    /*  read received data */
    local = TWI_readByte(data_ptr);
    if (local != TWI_OK)
    {
        return local;
    }

    /* send stop condition */
    TWI_stop();

    /* Byte received successfully */
    return local;
}

TwiError_type TWI_masterSendString(u8 address, u8 *str)
{
    TwiError_type local = TWI_OK;

    /* send start condition */
    local = TWI_start();
    if(local != TWI_OK)
    {
        return local;
    }

    /* send slave address + write*/
    local = TWI_write_SLA_write(address);
    if(local != TWI_OK)
    {
        return local;
    }

    /* loop on string till null */
    for (u8 i = 0; i < str[i]; i++)
    {
        local = TWI_writeByte(str[i]);
        if (local != TWI_OK)
        {
            return local;
        }
    }

    /* send stop condition */
    TWI_stop();

    /* str sent successfully */
    return local;
}
