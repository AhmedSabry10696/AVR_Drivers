/**
 * @file uart_services.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Uart services implementation
 * @version 0.1
 * @date 12-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "uart_services.h"

void UART_sendString(const u8 *str)
{
	u8 i;

	/* loop on string */
	for (i = 0; str[i]; i++)
	{
		/* send byte by byte */
		UART_send(str[i]);
	}

	/* send # at the end of string */
	/* Uart_Send('#'); */
}

void UART_receiveString(u8 *str)
{
	u8 i = 0;

	/* store byte by byte in str buffer */
	str[i] = UART_receive();

	/* receive till # */
	for (; str[i] != '#';)
	{
		i++;
		str[i] = UART_receive();
	}

	/* end string with null */
	str[i] = 0;
}

void UART_sendLong(u32 num)
{
	/* send first byte of long number */
	UART_send((u8)(num & 0x000000ff));

	/* send second byte of long number */
	UART_send((u8)((num >> 8) & 0x000000ff));

	/* send third byte of long number */
	UART_send((u8)((num >> 16) & 0x000000ff));

	/* send fourth byte of long number */
	UART_send((u8)((num >> 24) & 0x000000ff));
}

u32 UART_receiveLong(void)
{
	/* receive first byte of long number */
	u8 b1 = UART_receive();

	/* receive second byte of long number */
	u8 b2 = UART_receive();

	/* receive third byte of long number */
	u8 b3 = UART_receive();

	/* receive fourth byte of long number */
	u8 b4 = UART_receive();

	/* concat all four bytes to get long number */
	u32 num = b1 | ((u32)b2 << 8) | ((u32)b3 << 16) | ((u32)b4 << 24);

	return num;
}

static u8 *sendStr_ptr;
static u8 send_flag = 1;
static void UART_TXC_func(void)
{
	static u8 i = 1;
	if (sendStr_ptr[i] != 0)
	{
		UART_sendNoBlock(sendStr_ptr[i]);
		i++;
	}
	else
	{
		i = 1;
		send_flag = 1;
	}
}

void UART_sendStringAsyn(u8 *str)
{
	if (1 == send_flag)
	{
		/* send first char only and ISR continue others */
		UART_sendNoBlock(str[0]);
		UART_TXC_intEnable();
		sendStr_ptr = str;
		UART_TXC_intSetCallBack(UART_TXC_func);
		send_flag = 0;
	}
}

static u8 *receiveStr_ptr;
static void UART_RXC_func(void)
{
	static u8 i = 0;
	receiveStr_ptr[i] = UART_receiveNoBlock();
	if (receiveStr_ptr[i] == '#')
	{
		receiveStr_ptr[i] = 0;
		i = 0;
	}
	else
	{
		i++;
	}
}

void UART_receiveStringAsyn(u8 *str)
{
	receiveStr_ptr = str;
	UART_RXC_intEnable();
	UART_RXC_intSetCallBack(UART_RXC_func);
}