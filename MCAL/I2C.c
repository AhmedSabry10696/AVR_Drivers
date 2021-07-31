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

void TWI_Init(u8 address)
{
    /* TWSR prescaler value */
    CLEAR_BIT(TWSR,TWPS0);
    CLEAR_BIT(TWSR,TWPS1);
    
    /* FCPU {8 MHZ} Bit rate: 400 KHZ */
    TWBR = 0x02;

    /* set address and general-call off {bit 0} */
    TWAR = (address<<1);

    /* enable ACK */
    SET_BIT(TWCR,TWEA);
    /* enable TWI */
    SET_BIT(TWCR,TWEN);
}

TWI_Error_type TWI_Start(void)
{
    TWI_Error_type local = TWI_OK;

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

TWI_Error_type TWI_RepStart(void)
{
    TWI_Error_type local = TWI_OK;
    
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

TWI_Error_type TWI_Write_SLA_Write(u8 address)
{
    TWI_Error_type local = TWI_OK;

    TWDR = (address<<1);

    /* write operation */
    CLEAR_BIT(TWDR,0);

    /* clear start condition bit */
    CLEAR_BIT(TWCR, TWSTA);

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

TWI_Error_type TWI_Write_SLA_Read(u8 address)
{
    TWI_Error_type local = TWI_OK;

    TWDR = (address<<1);

    /* read operation */
    SET_BIT(TWDR,0);

    /* clear start condition bit */
    CLEAR_BIT(TWCR, TWSTA);

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

TWI_Error_type TWI_WriteByte(u8 data)
{
    TWI_Error_type local = TWI_OK;

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

TWI_Error_type TWI_ReadByte(u8 *data)
{
    TWI_Error_type local = TWI_OK;

    /* disable ACK */
    CLEAR_BIT(TWCR,TWEA);

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
        *data = TWDR;
    }
    
    /* enable ACK again */
    SET_BIT(TWCR,TWEA);
    
    return local;
}

void TWI_Stop(void)
{
    /* send stop condition */
    SET_BIT(TWCR,TWSTO);

    /* clear flag */
    SET_BIT(TWCR,TWINT);
}

void TWI_Listen(void)
{
    /* Wait for TWINT flag set in TWCR Register */
    while (0 == READ_BIT(TWCR, TWINT));
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

