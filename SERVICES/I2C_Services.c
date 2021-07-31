/**
 * @file I2C_Services.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief I2C services implementation
 * @version 0.1
 * @date 29-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "I2C_Services.h"
#include "LCD.h"


TWI_Error_type TWI_Master_SendByte(u8 address, u8 data)
{
    TWI_Error_type local = TWI_OK;
    
    /* send start condition */
    local = TWI_Start();
    if (local != TWI_OK)
    {
        return local;
    }
    
    /* I2C terminal in proteus write address with no shift {bit 0 R/W}*/
    local = TWI_Write_SLA_Write(address);
    if (local != TWI_OK)
    {
        return local;
    }
    
    /* send byte */
    local = TWI_WriteByte(data);
    if (local != TWI_OK)
    {
        return local;
    }
    
    /* send stop condition */
    TWI_Stop();

    /* Byte sent successfully */
    return local;
}

TWI_Error_type TWI_Master_ReceiveByte(u8 address, u8 *data)
{
    TWI_Error_type local = TWI_OK;
    
    /* send start condition */
    local = TWI_Start();
    if (local != TWI_OK)
    {
        return local;
    }
    
    /* send slave address + read */
    local = TWI_Write_SLA_Read(address);
    if (local != TWI_OK)
    {
        return local;
    }

    /*  read received data */
    local = TWI_ReadByte(data);
    if (local != TWI_OK)
    {
        return local;
    }

    /* send stop condition */
    TWI_Stop();

    /* Byte received successfully */
    return local;
}

TWI_Error_type TWI_Master_SendString(u8 address, u8 *str)
{
    TWI_Error_type local = TWI_OK;

    /* send start condition */
    local = TWI_Start();
    if(local != TWI_OK)
    {
        return local;
    }

    /* send slave address + write*/
    local = TWI_Write_SLA_Write(address);
    if(local != TWI_OK)
    {
        return local;
    }

    /* loop on string till null */
    for (u8 i = 0; i < str[i]; i++)
    {
        local = TWI_WriteByte(str[i]);
        if (local != TWI_OK)
        {
            return local;
        }
    }

    /* send stop condition */
    TWI_Stop();

    /* str sent successfully */
    return local;
}