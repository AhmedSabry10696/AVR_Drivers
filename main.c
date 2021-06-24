#define  F_CPU 8000000UL
#include <util/delay.h>
#include "MemMap.h"
#include "Utils.h"
#include "LCD_Interface.h"
#include "ADC_interface.h"
#include "Sensors.h"

int main(void)
{
	u16 volt;
	
	/* DIO init */
	DIO_Init();

	/* lcd init */
	LCD_Init();

	/* adc init with AREF volt and 64 prescaler 125 KHZ */
	ADC_Init(REF_AREF,ADC_Scaler_64);

	
	while(1)
	{
		LCD_GoTo(0,0);
		volt = POT_VoltRead();
		LCD_WriteNum(volt);
		LCD_WriteString("    ");
	}/*  end of while 1 */
}/* end of main */