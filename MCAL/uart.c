/**
 * @file uart.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief uart driver implementation
 * @version 0.1
 * @date 10-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "uart.h"

static void (*uart_txc_fPtr)(void) = NULLPTR;
static void (*uart_rxc_fPtr)(void) = NULLPTR;
static void (*uart_dEmpty_fPtr)(void) = NULLPTR;

void UART_TX_enable(void)
{
    SET_BIT(UCSRB, TXEN);
}

void UART_TX_disable(void)
{
    CLR_BIT(UCSRB, TXEN);
}

void UART_RX_enable(void)
{
    SET_BIT(UCSRB, RXEN);
}

void UART_RX_disable(void)
{
    CLR_BIT(UCSRB, RXEN);
}

void UART_init(void)
{
    /* normal speed mode */
    CLR_BIT(UCSRA, U2X);
    SET_BIT(UCSRC, URSEL);

    /* parity setup */
    switch (uart.parity)
    {
    case NO_PARITY:
        CLR_BIT(UCSRC, UPM0);
        CLR_BIT(UCSRC, UPM1);
        break;

    case EVEN_PARITY:
        CLR_BIT(UCSRC, UPM0);
        SET_BIT(UCSRC, UPM1);
        break;
    case ODD_PARITY:
        SET_BIT(UCSRC, UPM0);
        SET_BIT(UCSRC, UPM1);
    }

    /* stop bit setup */
    if (ONE_STOP_BIT == uart.stop)
    {
        CLR_BIT(UCSRC, USBS);
    }
    else if (TWO_STOP_BIT == uart.stop)
    {
        SET_BIT(UCSRC, USBS);
    }

    /* data size setup */
    switch (uart.data)
    {
    case FIVE_BIT_DATA:
        CLR_BIT(UCSRC, UCSZ0);
        CLR_BIT(UCSRC, UCSZ1);
        CLR_BIT(UCSRB, UCSZ2);
        break;
    case SIX_BIT_DATA:
        SET_BIT(UCSRC, UCSZ0);
        CLR_BIT(UCSRC, UCSZ1);
        CLR_BIT(UCSRB, UCSZ2);
        break;
    case SEVEN_BIT_DATA:
        CLR_BIT(UCSRC, UCSZ0);
        SET_BIT(UCSRC, UCSZ1);
        CLR_BIT(UCSRB, UCSZ2);
        break;
    case EIGHT_BIT_DATA:
        SET_BIT(UCSRC, UCSZ0);
        SET_BIT(UCSRC, UCSZ1);
        CLR_BIT(UCSRB, UCSZ2);
        break;
    case NINE_BIT_DATA:
        SET_BIT(UCSRC, UCSZ0);
        SET_BIT(UCSRC, UCSZ1);
        SET_BIT(UCSRB, UCSZ2);
        break;
    }

    /* baud rate setup */
    switch (uart.baud)
    {
    case BAUD_2400:
        UBRRL = 207;
        break;
    case BAUD_4800:
        UBRRL = 103;
        break;
    case BAUD_9600:
        UBRRL = 51;
        break;
    case BAUD_14400:
        UBRRL = 34;
        break;
    case BAUD_19200:
        UBRRL = 25;
        break;
    case BAUD_28800:
        UBRRL = 16;
        break;
    case BAUD_38400:
        UBRRL = 12;
        break;
    case BAUD_57600:
        UBRRL = 8;
        break;
    case BAUD_76800:
        UBRRL = 6;
        break;
    case BAUD_115200:
        UBRRL = 3;
        break;
    case BAUD_230400:
        UBRRL = 1;
        break;
    case BAUD_250000:
        UBRRL = 1;
        break;
    case BAUD_500000:
        UBRRL = 0;
        break;
    case BAUD_1000000:
        UBRRL = 0;
        break;
    }

    /* Enable Transmitter and Receiver */
    SET_BIT(UCSRB, TXEN);
    SET_BIT(UCSRB, RXEN);
}

void UART_send(const u8 data)
{
    /* wait till flag being 1 */
    while (0 == READ_BIT(UCSRA, UDRE));

    /* write data */
    UDR = data;
}

u8 UART_receive(void)
{
    /* wait till flag being 1 */
    while (0 == READ_BIT(UCSRA, RXC));

    /* retrieve data */
    return UDR;
}

u8 UART_receivePeriodicCheck(u8 *data_ptr)
{
    if (1 == READ_BIT(UCSRA, RXC))
    {
        *data_ptr = UDR;
        return 1;
    }
    else
    {
        return 0;
    }
}

void UART_sendNoBlock(const u8 data)
{
    /* write data in buffer */
    UDR = data;
}

u8 UART_receiveNoBlock(void)
{
    /* retrieve data from buffer */
    return UDR;
}

void UART_TXC_intEnable(void)
{
    SET_BIT(UCSRB, TXCIE);
}

void UART_TXC_intDisable(void)
{
    CLR_BIT(UCSRB, TXCIE);
}

void UART_RXC_intEnable(void)
{
    SET_BIT(UCSRB, RXCIE);
}

void UART_RXC_intDisable(void)
{
    CLR_BIT(UCSRB, RXCIE);
}

void UART_DEMPTY_intEnable(void)
{
    SET_BIT(UCSRB, UDRIE);
}

void UART_DEMPTY_intDisable(void)
{
    CLR_BIT(UCSRB, UDRIE);
}

void UART_TXC_intSetCallBack(void (*localFptr)(void))
{
    uart_txc_fPtr = localFptr;
}

void UART_RXC_intSetCallBack(void (*localFptr)(void))
{
    uart_rxc_fPtr = localFptr;
}

void UART_DEMPTY_intSetCallBack(void (*localFptr)(void))
{
    uart_dEmpty_fPtr = localFptr;
}

ISR(USART_TXC_VECT)
{
    if (uart_txc_fPtr != NULLPTR)
    {
        uart_txc_fPtr();
    }
}
ISR(USART_RXC_VECT)
{
    if (uart_rxc_fPtr != NULLPTR)
    {
        uart_rxc_fPtr();
    }
}

ISR(USART_UDRE_VECT)
{
    if (uart_dEmpty_fPtr != NULLPTR)
    {
        uart_dEmpty_fPtr();
    }
}
