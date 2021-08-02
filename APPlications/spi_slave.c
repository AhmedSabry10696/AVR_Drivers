/**
 * @file SPI_Slave.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief atmega32 controller (slave) reads temp sensor value and display it on lcd and send the latest temp val
 * 		  to another atmega32 controller (master) through spi and get value from spi and print it to screen.
 * @version 0.1
 * @date 28-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define F_CPU 8000000UL
#include <util/delay.h>

#include "memory_map.h"
#include "utils.h"
#include "std_types.h"
#include "dio.h"
#include "ext_interrupt.h"
#include "uart.h"
#include "lcd.h"
#include "spi.h"
#include "sensors.h"

static volatile u8 flag = 0;
static volatile u8 uart_data = '#';

static void SPI_func(void)
{
	uart_data = SPI_receiveNoBlock();
}

int main(void)
{
	u16 x = 0, temp;
	sei();
	DIO_init();
	LCD_init();
	ADC_init(REF_AVCC, ADC_Scaler_64);

	SPI_init();
	SPI_STC_intSetCallBack(SPI_Func);
	SPI_intEnable();

	LCD_writeString("     SPI Slave");

	LCD_goTo(1, 0);
	LCD_writeString("x: ");

	LCD_goTo(2, 0);
	LCD_writeString("Uart Data: ");

	LCD_goTo(3, 0);
	LCD_writeString("Temp: ");

	while (1)
	{
		temp = LM35_tempRead();

		LCD_goTo(3, 10);
		LCD_writeNum(temp / 10);

		LCD_goTo(2, 10);
		LCD_writeChar(uart_data);

		SPI_sendNoBlock(temp / 10);

		LCD_goTo(1, 5);
		LCD_writeNum(x);
		
		x++;
		if (x == 10)
		{
			x = 0;
		}
		_delay_ms(300);
	}

	return 0;
}
