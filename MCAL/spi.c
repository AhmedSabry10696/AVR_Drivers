/**
 * @file spi.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief SPI driver implementation
 * @version 0.1
 * @date 26-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "spi.h"

static void (*spi_stc_fPtr)(void) = NULLPTR;

void SPI_init(void)
{
    /* data order config */
    if (LSB_FIRST == spi.data_order)
    {
        SET_BIT(SPCR, DORD);
    }
    else
    {
        CLR_BIT(SPCR, DORD);
    }

    /* master or slave config */
    if (MASTER == spi.type)
    {
        SET_BIT(SPCR, MSTR);
    }
    else
    {
        CLR_BIT(SPCR, MSTR);
    }

    /* clock polarity */
    if (LEADING_EDGE_RISING == spi.clock_pol)
    {
        CLR_BIT(SPCR, CPOL);
    }
    else
    {
        SET_BIT(SPCR, CPOL);
    }

    /* clock phase */
    if (SETUP_LEADING == spi.clock_phase)
    {
        SET_BIT(SPCR, CPHA);
    }
    else
    {
        CLR_BIT(SPCR, CPHA);
    }

    /* clock speed */
    switch (spi.clock_speed)
    {
    case FCPU_DIV_2:
        SET_BIT(SPSR, SPI2X);
        CLR_BIT(SPCR, SPR0);
        CLR_BIT(SPCR, SPR1);
        break;
    case FCPU_DIV_4:
        CLR_BIT(SPSR, SPI2X);
        CLR_BIT(SPCR, SPR0);
        CLR_BIT(SPCR, SPR1);
        break;
    case FCPU_DIV_8:
        SET_BIT(SPSR, SPI2X);
        SET_BIT(SPCR, SPR0);
        CLR_BIT(SPCR, SPR1);
        break;
    case FCPU_DIV_16:
        CLR_BIT(SPSR, SPI2X);
        SET_BIT(SPCR, SPR0);
        CLR_BIT(SPCR, SPR1);
        break;
    case FCPU_DIV_32:
        SET_BIT(SPSR, SPI2X);
        CLR_BIT(SPCR, SPR0);
        SET_BIT(SPCR, SPR1);
        break;
    case FCPU_DIV_64:
        CLR_BIT(SPSR, SPI2X);
        CLR_BIT(SPCR, SPR0);
        SET_BIT(SPCR, SPR1);
        break;
    case FCPU_DIV_128:
        CLR_BIT(SPSR, SPI2X);
        SET_BIT(SPCR, SPR0);
        SET_BIT(SPCR, SPR1);
        break;
    }

    /* enable SPI */
    SET_BIT(SPCR, SPE);
}

u8 SPI_sendReceive(u8 data)
{
    SPDR = data;

    /* note that polling in SPI to send data is better than interrupt cause spi is fast (to send one byte faster than interrupt response) */
    /* wait till transmission complete */
    while (0 == READ_BIT(SPSR, SPIF));

    return SPDR;
}

void SPI_sendNoBlock(u8 data)
{
    SPDR = data;
}

u8 SPI_receiveNoBlock(void)
{
    return SPDR;
}

u8 SPI_receivePeriodic(u8 *data_ptr)
{
    if (1 == READ_BIT(SPSR, SPIF))
    {
        *data_ptr = SPDR;
        return 1;
    }
    else
    {
        return 0;
    }
}

void SPI_intEnable(void)
{
    SET_BIT(SPCR, SPIE);
}

void SPI_intDisable(void)
{
    CLR_BIT(SPCR, SPIE);
}

void SPI_STC_intSetCallBack(void (*localFptr)(void))
{
    spi_stc_fPtr = localFptr;
}

ISR(SPI_STC_VECT)
{
    if (spi_stc_fPtr != NULLPTR)
    {
        spi_stc_fPtr();
    }
}
