#define  F_CPU 8000000UL
#include <util/delay.h>

#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"
#include "DIO.h"
#include "Ext_Interrupt.h"
#include "Uart.h"
#include "LCD.h"
#include "EXT_EEPROM.h"

int main(void)
{
	sei();
	DIO_Init();
	LCD_Init();	
	EEPROM_Init();
	u8 y = 0;
	
	EEPROM_Write_Byte(512,10);
	_delay_ms(10);
	EEPROM_Read_Byte(512,&y);
		
	LCD_GoTo(2,0);
	LCD_WriteNum(y);
	
	while(1)
	{	

	}

	return 0;
}