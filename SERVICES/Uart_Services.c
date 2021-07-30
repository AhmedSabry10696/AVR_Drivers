/**
 * @file Uart_Services.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Uart services implementation
 * @version 0.1
 * @date 12-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Uart_Services.h"

void Uart_SendString(const u8 *str)
{
	u8 i;

	/* loop on string */
	for (i = 0; str[i]; i++)
	{
		/* send byte by byte */
		Uart_Send(str[i]);
	}

	/* send # at the end of string */
	/* Uart_Send('#'); */
}
void Uart_ReceiveString(u8 *str)
{
	u8 i = 0;

	/* store byte by byte in str buffer */
	str[i] = Uart_Receive();

	/* receive till # */
	for (; str[i] != '#';)
	{
		i++;
		str[i] = Uart_Receive();
	}

	/* end string with null */
	str[i] = 0;
}
void Uart_SendLong(u32 num)
{
	/* send first byte of long number */
	Uart_Send((u8)(num & 0x000000ff));

	/* send second byte of long number */
	Uart_Send((u8)((num >> 8) & 0x000000ff));

	/* send third byte of long number */
	Uart_Send((u8)((num >> 16) & 0x000000ff));

	/* send fourth byte of long number */
	Uart_Send((u8)((num >> 24) & 0x000000ff));
}
u32 Uart_ReceiveLong(void)
{
	/* receive first byte of long number */
	u8 b1 = Uart_Receive();

	/* receive second byte of long number */
	u8 b2 = Uart_Receive();

	/* receive third byte of long number */
	u8 b3 = Uart_Receive();

	/* receive fourth byte of long number */
	u8 b4 = Uart_Receive();

	/* concat all four bytes to get long number */
	u32 num = b1 | ((u32)b2 << 8) | ((u32)b3 << 16) | ((u32)b4 << 24);

	return num;
}

static u8 *Psend_str;
static u8 send_flag = 1;
static void Uart_TXC_Func(void)
{
	static u8 i = 1;
	if (Psend_str[i] != 0)
	{
		Uart_SendNoBlock(Psend_str[i]);
		i++;
	}
	else
	{
		i = 1;
		send_flag = 1;
	}
}
void Uart_SendStringAsyn(const u8 *str)
{
	if (1 == send_flag)
	{
		/* send first char only and ISR continue others */
		Uart_SendNoBlock(str[0]);
		Uart_TXC_IntEnable();
		Psend_str = str;
		Uart_TXC_IntSetCallBack(Uart_TXC_Func);
		send_flag = 0;
	}
}

static u8 *Preceive_str;
static void Uart_RXC_Func(void)
{
	static u8 i = 0;
	Preceive_str[i] = Uart_ReceiveNoBlock();
	if (Preceive_str[i] == '#')
	{
		Preceive_str[i] = 0;
		i = 0;
	}
	else
	{
		i++;
	}
}
void Uart_ReceiveStringAsyn(u8 *str)
{
	Preceive_str = str;
	Uart_RXC_IntEnable();
	Uart_RXC_IntSetCallBack(Uart_RXC_Func);
}