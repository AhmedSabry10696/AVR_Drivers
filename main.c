#define  F_CPU 8000000UL
#include <util/delay.h>

#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"
#include "DIO.h"
#include "Ext_Interrupt.h"
#include "Uart.h"
#include "LCD.h"
#include "I2C_Services.h"

int main(void)
{
	sei();
	DIO_Init();
	LCD_Init();	
	TWI_Init();
	
	while(1)
	{	

	}

	return 0;
}