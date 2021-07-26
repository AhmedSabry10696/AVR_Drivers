/**
 * @file SPI.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief SPI driver implementation
 * @version 0.1
 * @date 26-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "SPI.h"

static void (*SPI_STC_IntFptr)(void) = NULLPTR;

void SPI_Init(void)
{
    /* data order config */
    if (LSB_FIRST == spi.data_order)
    {
        SET_BIT(SPCR, DORD);
    }
    else
    {
        CLEAR_BIT(SPCR, DORD);
    }

    /* master or slave config */
    if (MASTER == spi.type)
    {
        SET_BIT(SPCR, MSTR);
    }
    else
    {
        CLEAR_BIT(SPCR, MSTR);
    }

    /* clock polarity */
    if (LEADING_EDGE_RISING == spi.clock_pol)
    {
        CLEAR_BIT(SPCR, CPOL);
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
        CLEAR_BIT(SPCR, CPHA);
    }

    /* clock speed */
    switch (spi.clock_speed)
    {
    case FCPU_DIV_2:
        SET_BIT(SPSR, SPI2X);
        CLEAR_BIT(SPCR, SPR0);
        CLEAR_BIT(SPCR, SPR1);
        break;
    case FCPU_DIV_4:
        CLEAR_BIT(SPSR, SPI2X);
        CLEAR_BIT(SPCR, SPR0);
        CLEAR_BIT(SPCR, SPR1);
        break;
    case FCPU_DIV_8:
        SET_BIT(SPSR, SPI2X);
        SET_BIT(SPCR, SPR0);
        CLEAR_BIT(SPCR, SPR1);
        break;
    case FCPU_DIV_16:
        CLEAR_BIT(SPSR, SPI2X);
        SET_BIT(SPCR, SPR0);
        CLEAR_BIT(SPCR, SPR1);
        break;
    case FCPU_DIV_32:
        SET_BIT(SPSR, SPI2X);
        CLEAR_BIT(SPCR, SPR0);
        SET_BIT(SPCR, SPR1);
        break;
    case FCPU_DIV_64:
        CLEAR_BIT(SPSR, SPI2X);
        CLEAR_BIT(SPCR, SPR0);
        SET_BIT(SPCR, SPR1);
        break;
    case FCPU_DIV_128:
        CLEAR_BIT(SPSR, SPI2X);
        SET_BIT(SPCR, SPR0);
        SET_BIT(SPCR, SPR1);
        break;
    }

    /* enable SPI */
    SET_BIT(SPCR, SPE);
}

u8 SPI_Send_Receive(u8 data)
{
    SPDR = data;

    /* note that polling in SPI to send data is better than interrupt cause spi is fast (to send one byte faster than interrupt response) */
    /* wait till transmission complete */
    while (0 == READ_BIT(SPSR, SPIF));

    return SPDR;
}

void SPI_Send_NoBlock(u8 data)
{
    SPDR = data;
}

u8 SPI_Receive_NoBlock(void)
{
    return SPDR;
}

u8 SPI_Receive_Periodic(u8 *pdata)
{
    if (1 == READ_BIT(SPSR, SPIF))
    {
        *pdata = SPDR;
        return 1;
    }
    else
    {
        return 0;
    }
}

void SPI_Int_Enable(void)
{
    SET_BIT(SPCR, SPIE);
}
void SPI_Int_Disable(void)
{
    CLEAR_BIT(SPCR, SPIE);
}

void SPI_STC_IntSetCallBack(void(*LocalFptr)(void))
{
	SPI_STC_IntFptr = LocalFptr;
}

ISR(SPI_STC_VECT)
{
    if (SPI_STC_IntFptr != NULLPTR)
    {
        SPI_STC_IntFptr();
    }
}