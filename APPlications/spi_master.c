/**
 * @file SPI_Master.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief atmega32 controller (master) receive data through uart and display it on lcd, and there is also
 * 		  button on ext0 when button pressed this controller send the uart data through spi and get the
 * 		  latest temp value.	
 * @version 0.1
 * @date 28-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define F_CPU 8000000UL
#include <util/delay.h>

#include "Memory_map.h"
#include "utils.h"
#include "std_types.h"
#include "dio.h"
#include "ext_interrupt.h"
#include "uart.h"
#include "lcd.h"
#include "spi.h"

static volatile u8 flag = 0;
static volatile u8 uart_data, temp = 0;

static void EXI_func(void)
{
	flag = 1;
}

static void Uart_func(void)
{
	uart_data = Uart_receiveNoBlock();
}

int main(void)
{
	u8 x = 0;
	sei();
	DIO_init();
	LCD_init();
	SPI_init();

	/* ss pin */
	DIO_writePin(PINB4, LOW);

	UART_init();
	UART_RXC_intSetCallBack(Uart_func);
	Uart_RXC_IntEnable();

	EXI_enable(EX_INT0);
	EXI_triggerEdge(EX_INT0, FALLING_EDGE);
	EXI_setCallBack(EX_INT0, EXI_func);

	LCD_writeString("     SPI Master");

	LCD_goTo(1, 0);
	LCD_writeString("x: ");

	LCD_goTo(2, 0);
	LCD_writeString("Uart Data: ");

	LCD_goTo(3, 0);
	LCD_writeString("Temp: ");

	while (1)
	{
		LCD_goTo(1, 5);
		LCD_writeNum(x);
		x++;
		if (x == 10)
		{
			x = 0;
		}
		_delay_ms(500);

		LCD_goTo(2, 10);
		LCD_writeChar(uart_data);

		LCD_goTo(3, 10);
		LCD_writeNum(temp);

		if (flag == 1)
		{
			temp = SPI_sendReceive(uart_data);
			flag = 0;
		}
	}

	return 0;
}
