#define  F_CPU 8000000UL
#include <util/delay.h>
#include "memory_map.h"
#include "utils.h"
#include "std_types.h"
#include "dio.h"
#include "ext_interrupt.h"
#include "lcd.h"
#include "adc.h"

int main(void)
{
	sei();
	DIO_init();
	LCD_init();	
	ADC_init(REF_256V,ADC_SCALER_64);
	u16 x,y;
	while(1)
	{	
		
		x = ADC_read(CH_0);
		y = (u32)150*x/600;
		LCD_goTo(0,0);
		LCD_writeNum(y);
		LCD_writeString("   ");
	}

	return 0;
}