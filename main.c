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

static volatile u8 flag = 0;
static volatile u8 uart_data,temp = 0;

static void EXI_Func(void)
{
	flag = 1;
}

static void Uart_Func(void)
{
	uart_data = Uart_ReceiveNoBlock();
}

int main(void)
{
	u8 x = 0;
	sei();
	DIO_Init();
	LCD_Init();	
	SPI_Init();
	
	// ss pin
	DIO_WritePin(PINB4,LOW);
	
	Uart_Init();
	Uart_RXC_IntSetCallBack(Uart_Func);
	Uart_RXC_IntEnable();

	EXI_Enable(EX_INT0);
	EXI_TriggerEdge(EX_INT0,FALLING_EDGE);
	EXI_SetCallBack(EX_INT0,EXI_Func);
	
	LCD_WriteString("     SPI Master");
	
	LCD_GoTo(1,0);
	LCD_WriteString("x: ");
	
	LCD_GoTo(2,0);
	LCD_WriteString("Uart Data: ");
	
	LCD_GoTo(3,0);
	LCD_WriteString("Temp: ");
	
	while(1)
	{	
		LCD_GoTo(1,5);
		LCD_WriteNum(x);
		x++;
		if (x == 10)
		{
			x = 0;
		}
		_delay_ms(500);
		
		LCD_GoTo(2,10);
		LCD_WriteChar(uart_data);

		LCD_GoTo(3,10);
		LCD_WriteNum(temp);
		
		if(flag == 1)
		{
			temp = SPI_Send_Receive(uart_data);
			flag = 0;
		}
	}

	return 0;
}