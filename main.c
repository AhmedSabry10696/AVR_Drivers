#define  F_CPU 8000000UL
#include <util/delay.h>

#include "memory_map.h"
#include "utils.h"
#include "std_types.h"
#include "dio.h"
#include "ext_interrupt.h"
#include "uart.h"
#include "lcd.h"
#include "EXT_EEPROM.h"

int main(void)
{
	sei();
	DIO_init();
	LCD_init();	
	EEPROM_init();
	u8 y = 0;
	
	EEPROM_writeByte(512,10);
	_delay_ms(10);
	EEPROM_readByte(512,&y);
		
	LCD_goTo(2,0);
	LCD_writeNum(y);
	
	while(1)
	{	

	}

	return 0;
}