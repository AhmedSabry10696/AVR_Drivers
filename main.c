#define  F_CPU 8000000UL
#include <util/delay.h>
#include <string.h>
#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"

#include "DIO.h"
#include "LCD.h"
#include "SPI.h"

int main(void)
{
	sei();
	DIO_Init();
	LCD_Init();
	LCD_WriteString("welcome spi");
	LCD_GoTo(2,0);
	SPI_Init();
	
	u8 x= 0x00,y;
	while(1)
	{
		y = SPI_Send_Receive(x);
		x++;
		LCD_GoTo(1,0);
		LCD_WriteNum(y);
		_delay_ms(1000);
	}
}