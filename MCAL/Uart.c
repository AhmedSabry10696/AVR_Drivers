/**
 * @file Uart.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief uart driver implementation
 * @version 0.1
 * @date 10-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Uart.h"

static void (*Uart_TXC_IntFptr)(void) = NULLPTR;
static void (*Uart_RXC_IntFptr)(void) = NULLPTR;
static void (*Uart_DEMPTY_IntFptr)(void) = NULLPTR;

void Uart_TX_Enable(void)
{
    SET_BIT(UCSRB,TXEN);
}
void Uart_TX_Disable(void)
{  
    CLEAR_BIT(UCSRB,TXEN);
}
void Uart_RX_Enable(void)
{
    SET_BIT(UCSRB,RXEN);
}
void Uart_RX_Disable(void)
{
    CLEAR_BIT(UCSRB,RXEN);
}

void Uart_Init(void)
{
    //u8 temp = 0x80;

    /* normal speed mode */
    CLEAR_BIT(UCSRA,U2X);    
    SET_BIT(UCSRC,URSEL);
    /* parity setup */
	switch (uart.parity)
    {
    case NO_PARITY:
        CLEAR_BIT(UCSRC,UPM0);
        CLEAR_BIT(UCSRC,UPM1);
        break;
    
    case EVEN_PARITY:
        CLEAR_BIT(UCSRC,UPM0);
        SET_BIT(UCSRC,UPM1);        
        break;
    case ODD_PARITY:
        SET_BIT(UCSRC,UPM0);
        SET_BIT(UCSRC,UPM1);
    }
    
    /* stop bit setup */
    if (uart.stop == ONE_STOP_BIT)
    {
        CLEAR_BIT(UCSRC,USBS);
    }
    else if (uart.stop == TWO_STOP_BIT)
    {
        SET_BIT(UCSRC,USBS);
    }

    /* data size setup */
    switch (uart.data)
    {
    case FIVE_BIT_DATA:
        CLEAR_BIT(UCSRC,UCSZ0);
        CLEAR_BIT(UCSRC,UCSZ1);
        CLEAR_BIT(UCSRB,UCSZ2);
        break;
    case SIX_BIT_DATA:
        SET_BIT(UCSRC,UCSZ0);
        CLEAR_BIT(UCSRC,UCSZ1);
        CLEAR_BIT(UCSRB,UCSZ2);
        break;    
    case SEVEN_BIT_DATA:
        CLEAR_BIT(UCSRC,UCSZ0);
        SET_BIT(UCSRC,UCSZ1);
        CLEAR_BIT(UCSRB,UCSZ2);
        break;
    case EIGHT_BIT_DATA:
        SET_BIT(UCSRC,UCSZ0);
        SET_BIT(UCSRC,UCSZ1);
        CLEAR_BIT(UCSRB,UCSZ2);
        break;
    case NINE_BIT_DATA:
        SET_BIT(UCSRC,UCSZ0);
        SET_BIT(UCSRC,UCSZ1);
        SET_BIT(UCSRB,UCSZ2);
        break;
    }

    //UCSRC = temp;

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
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
}

void Uart_Send(const u8 data)
{
    /* wait till flag being 1 */
	while(0 == READ_BIT(UCSRA,UDRE));

    /* write data */
	UDR = data;
}
u8 Uart_Receive(void)
{
    /* wait till flag being 1 */
	while(0 == READ_BIT(UCSRA,RXC));

    /* retrieve data */
	return UDR;
}

u8 Uart_Receive_PeriodicCheck(u8 *pdata)
{
    if (1 == READ_BIT(UCSRA,RXC))
    {
        *pdata = UDR;
        return 1;
    }
    else
    {
        return 0;
    }
}

void Uart_SendNoBlock(const u8 data)
{
    /* write data in buffer */
    UDR = data;
}
u8 Uart_ReceiveNoBlock(void)
{
    /* retrieve data from buffer */
    return UDR;
}

void Uart_TXC_IntEnable(void)
{
    SET_BIT(UCSRB,TXCIE);
}
void Uart_TXC_IntDisable(void)
{
    CLEAR_BIT(UCSRB,TXCIE);
}
void Uart_RXC_IntEnable(void)
{
    SET_BIT(UCSRB,RXCIE);
}
void Uart_RXC_IntDisable(void)
{
    CLEAR_BIT(UCSRB,RXCIE);
}
void Uart_DEMPTY_IntEnable(void)
{
    SET_BIT(UCSRB,UDRIE);
}
void Uart_DEMPTY_IntDisable(void)
{
    CLEAR_BIT(UCSRB,UDRIE);
}

void Uart_TXC_IntSetCallBack(void(*LocalFptr)(void))
{
	Uart_TXC_IntFptr = LocalFptr;
}
void Uart_RXC_IntSetCallBack(void(*LocalFptr)(void))
{
    Uart_RXC_IntFptr = LocalFptr;
}
void Uart_DEMPTY_IntSetCallBack(void(*LocalFptr)(void))
{
    Uart_DEMPTY_IntFptr = LocalFptr;
}

ISR(USART_TXC_VECT)
{
	if (Uart_TXC_IntFptr != NULLPTR)
	{
		Uart_TXC_IntFptr();
	}
}
ISR(USART_RXC_VECT)
{
	if (Uart_RXC_IntFptr != NULLPTR)
	{
		Uart_RXC_IntFptr();
	}
}
ISR(USART_UDRE_VECT)
{
	if (Uart_DEMPTY_IntFptr != NULLPTR)
	{
		Uart_DEMPTY_IntFptr();
	}
}