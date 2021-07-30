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

u8 TWI_Master_WriteByte(u8 SlaveAddress, u8 data)
{
    /* send start condition */
    TWI_Start();
    if (TW_STATUS != TW_START)
    {
        return 0;
    }

    /* send slave address + write */
    /* I2C terminal in proteus write address with no shift {bit 0 R/W}*/
    TWI_Write((SlaveAddress << 1) | TW_W);
    if (TW_STATUS != TW_MT_SLA_W_ACK)
    {
        return 0;
    }

    /* send byte */
    TWI_Write(data);
    if (TW_STATUS != TW_MT_DATA_ACK)
    {
        return 0;
    }

    /* send stop condition */
    TWI_Stop();

    /* Byte sent successfully */
    return 1;
}

u8 TWI_Master_ReadByte(u8 SlaveAddress, u8 *data)
{
    /* send start condition */
    TWI_Start();

    if (TW_STATUS != TW_START)
    {
        return 0;
    }

    /* send slave address + read */
    TWI_Write((SlaveAddress << 1) | TW_R);
    if (TW_STATUS != TW_MT_SLA_R_ACK)
    {
        return 0;
    }

    /*  read received data */
    *data = TWI_Read_With_NACK();
    if (TW_STATUS != TW_MR_DATA_NACK)
    {
        return 0;
    }

    /* send stop condition */
    TWI_Stop();

    /* Byte received successfully */
    return 1;
}

u8 TWI_Slave_ReadByte(u8 *data)
{
    while (TW_STATUS != TW_SR_SLA_ACK)
    {
        /* clear flag and wait to set flag again */
        TWI_FlagPolling();
    }

    /* read data */
    *data = TWI_Read_With_ACK();

    /* check status */
    if (TW_STATUS == TW_SR_DATA_ACK || TW_STATUS == TW_SR_DATA_NACK)
    {
        /* correct data */
        return 1;
    }
    else
    {
        /* wrong data */
        return 0;
    }
}

u8 TWI_Slave_WriteByte(u8 data)
{
    while (TW_STATUS != TW_ST_SLA_ACK)
    {
        /* clear flag and wait to set flag again */
        TWI_FlagPolling();
    }

    /* write data */
    TWI_Write(data);

    /* check status */
    if (TW_STATUS == TW_ST_DATA_ACK || TW_STATUS == TW_ST_DATA_NACK)
    {
        /* Done */
        return 1;
    }
    else
    {
        /* Error */
        return 0;
    }
}

u8 TWI_Master_WriteString(u8 SlaveAddress, u8 *str)
{
    /* send start condition */
    TWI_Start();

    if (TW_STATUS != TW_START)
    {
        return 0;
    }

    /* send slave address + write*/
    TWI_Write((SlaveAddress << 1) | TW_W);
    if (TW_STATUS != TW_MT_SLA_W_ACK)
    {
        return 0;
    }

    /* loop on string till null */
    for (u8 i = 0; i < str[i]; i++)
    {
        TWI_Write(str[i]);
        if (TW_STATUS != TW_MT_DATA_ACK)
        {
            return 0;
        }
    }

    /* send stop condition */
    TWI_Stop();

    /* Byte sent successfully */
    return 1;
}