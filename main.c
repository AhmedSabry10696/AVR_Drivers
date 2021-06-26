#define  F_CPU 8000000UL
#include <util/delay.h>
#include "MemMap.h"
#include "Utils.h"
#include "Sensors.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "ADC_Interface.h"

int main(void)
{	
	u16 x;
	/* DIO init */
	DIO_Init();
	ADC_Init(REF_AREF,ADC_Scaler_64);
	LCD_Init();
	
	LCD_WriteString("MPX4110 pres sensor");
	
	while(1)
	{
		LCD_GoTo(2,0);
		x= MPX4110_PressureRead();
		LCD_WriteNum(x/10);
		LCD_WriteChar('.');
		LCD_WriteNum(x%10);
		LCD_WriteString("    KPa");
		LCD_WriteString("   ");
	}
}