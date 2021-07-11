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

#include "uart.h"

void Uart_Init(void)
{
    // frame 8bit, disable parity, 1stop

    // baud rate 9600 normal speed
    UBRRL = 51;
    CLEAR_BIT(UCSRA,U2X);

    SET_BIT(UCSRB,TXEN);
    SET_BIT(UCSRB,RXEN);
}

void Uart_Send(u8 data)
{

}

u8 Uart_Receive(void)
{

}