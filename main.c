#include <avr/io.h>
#include <avr/interrupt.h>
#define  F_CPU 8000000UL
#include <util/delay.h>
#include "MemMap.h"
#include "Utils.h"
#include "LCD_Interface.h"
#include "ADC_interface.h"
#include "Sensors.h"

int main(void)
{	
	/* DIO init */
	DIO_Init();

	/* lcd init */
	LCD_Init();
	
	while(1)
	{
		
	}/*  end of while 1 */
}/* end of main */

ISR()
{
	
	
}