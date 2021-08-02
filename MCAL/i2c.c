/**
 * @file i2c.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief I2C Driver implementation
 * @version 0.1
 * @date 28-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "i2c.h"

static void (*twi_fPtr)(void) = NULLPTR;

void TWI_init(u8 address)
{
    /* TWSR prescaler value */
    CLR_BIT(TWSR,TWPS0);
    CLR_BIT(TWSR,TWPS1);
    
    /* FCPU {8 MHZ} Bit rate: 400 KHZ */
    TWBR = 0x02;

    /* set address and general-call off {bit 0} */
    TWAR = (address<<1);

    /* enable ACK */
    SET_BIT(TWCR,TWEA);
    /* enable TWI */
    SET_BIT(TWCR,TWEN);
}

TwiError_type TWI_start(void)
{
    TwiError_type local = TWI_OK;

    /* send start condition */
    SET_BIT(TWCR,TWSTA);

    /* clear flag */
    SET_BIT(TWCR,TWINT);

    /* Wait for TWINT flag set in TWCR Register */
    while (0 == READ_BIT(TWCR, TWINT));

    if(TW_STATUS != TW_START)
    {
        local = TWI_SC_ERROR;
    }
    return local;
}

TwiError_type TWI_repStart(void)
{
    TwiError_type local = TWI_OK;
    
    /* send start condition */
    SET_BIT(TWCR,TWSTA);

    /* clear flag */
    SET_BIT(TWCR,TWINT);

    /* Wait for TWINT flag set in TWCR Register */
    while (0 == READ_BIT(TWCR, TWINT));
    
    if(TW_STATUS != TW_REP_START)
    {
        local = TWI_RSC_ERROR;
    }
    return local;
}

TwiError_type TWI_write_SLA_write(u8 address)
{
    TwiError_type local = TWI_OK;

    TWDR = (address<<1);

    /* write operation */
    CLR_BIT(TWDR,0);

    /* clear start condition bit */
    CLR_BIT(TWCR, TWSTA);

    /* clear flag */
    SET_BIT(TWCR, TWINT);

    /* Wait for TWINT flag set in TWCR Register */
    while (0 == READ_BIT(TWCR, TWINT));

    if(TW_STATUS != TW_MT_SLA_W_ACK)
    {
        local = TWI_MT_SLA_W_ERROR;
    }
    return local;
}

TwiError_type TWI_write_SLA_read(u8 address)
{
    TwiError_type local = TWI_OK;

    TWDR = (address<<1);

    /* read operation */
    SET_BIT(TWDR,0);

    /* clear start condition bit */
    CLR_BIT(TWCR, TWSTA);

    /* clear flag */
    SET_BIT(TWCR, TWINT);

    /* Wait for TWINT flag set in TWCR Register */
    while (0 == READ_BIT(TWCR, TWINT));

    if(TW_STATUS != TW_MT_SLA_R_ACK)
    {
        local = TWI_MR_SLA_R_ERROR;
    }
    return local;
}

TwiError_type TWI_writeByte(u8 data)
{
    TwiError_type local = TWI_OK;

    TWDR = data;

    /* clear flag */
    SET_BIT(TWCR, TWINT);

    /* Wait for TWINT flag set in TWCR Register */
    while (0 == READ_BIT(TWCR, TWINT));

    if(TW_STATUS != TW_MT_DATA_ACK)
    {
        local = TWI_MT_Data_ERROR;
    }
    return local;
}

TwiError_type TWI_readByte(u8 *data_ptr)
{
    TwiError_type local = TWI_OK;

    /* disable ACK */
    CLR_BIT(TWCR,TWEA);

     /* clear flag */
    SET_BIT(TWCR, TWINT);

    /* Wait for TWINT flag set in TWCR Register */
    while (0 == READ_BIT(TWCR, TWINT));

    if(TW_STATUS != TW_MR_DATA_NACK)
    {
        local = TWI_MR_Data_ERROR;
    }
    else
    {
        *data_ptr = TWDR;
    }
    
    /* enable ACK again */
    SET_BIT(TWCR,TWEA);
    
    return local;
}

void TWI_stop(void)
{
    /* send stop condition */
    SET_BIT(TWCR,TWSTO);

    /* clear flag */
    SET_BIT(TWCR,TWINT);
}

void TWI_listen(void)
{
    /* Wait for TWINT flag set in TWCR Register */
    while (0 == READ_BIT(TWCR, TWINT));
}

void TWI_intEnable(void)
{
    SET_BIT(TWCR, TWIE);
}

void TWI_intDisable(void)
{
    CLR_BIT(TWCR, TWIE);
}

void TWI_intSetCallBack(void (*localFptr)(void))
{
    twi_fPtr = localFptr;
}

ISR(TWI_VECT)
{
    if (twi_fPtr != NULLPTR)
    {
        twi_fPtr();
    }
}

