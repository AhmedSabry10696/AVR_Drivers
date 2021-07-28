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

#define  F_CPU 8000000UL
#include <util/delay.h>

#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"
#include "DIO.h"
#include "Ext_Interrupt.h"
#include "Uart.h"
#include "LCD.h"
#include "SPI.h"
#include "Sensors.h"

static volatile u8 flag = 0;
static volatile u8 uart_data = '#';

static void SPI_Func(void)
{
	uart_data = SPI_Receive_NoBlock();
}

int main(void)
{
	u16 x = 0,temp;
	sei();
	DIO_Init();
	LCD_Init();	
	ADC_Init(REF_AVCC,ADC_Scaler_64);
	
	SPI_Init();
	SPI_STC_IntSetCallBack(SPI_Func);
	SPI_Int_Enable();
	
	LCD_WriteString("     SPI Slave");
	
	LCD_GoTo(1,0);
	LCD_WriteString("x: ");
	
	LCD_GoTo(2,0);
	LCD_WriteString("Uart Data: ");
	
	LCD_GoTo(3,0);
	LCD_WriteString("Temp: ");
	
	while(1)
	{	
		temp = LM35_TempRead();
		
		LCD_GoTo(3,10);
		LCD_WriteNum(temp/10);
		
		LCD_GoTo(2,10);
		LCD_WriteChar(uart_data);
		
		SPI_Send_NoBlock(temp/10);
		
		LCD_GoTo(1,5);
		LCD_WriteNum(x);
		x++;
		if (x == 10)
		{
			x = 0;
		}
		_delay_ms(300);
	}

	return 0;
}