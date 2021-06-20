
#define  F_CPU 8000000UL
#include <util/delay.h>
#include "MemMap.h"
#include "Utils.h"
#include "LCD_Interface.h"
#include "ADC_interface.h"

void volume_diff(u8 *prev,u8 *current)
{
	static u8 t;
	u16 read = ADC_Read(CH_0);
	read = read*20/1024;
	
	*prev = t;
	*current = read;
	if(*current == 19)
		*current = 20;

	t = read;
}

int main(void)
{
	u8 prev = 0,current = 0,diff = 0,i;

	/* dio init */
	DIO_Init();

	/* lcd init */
	LCD_Init();

	/* adc init with AREF volt and 64 prescaller 125 KHZ */
	ADC_Init(REF_AREF,ADC_Scaler_64);
	
	/* print labels on lcd */
	LCD_WriteString("Volume Level:");
	LCD_GoTo(2,0);
	
	while(1)
	{
		volume_diff(&prev, &current);

		if(current > prev)
		{
			diff = current - prev;
			for (i = 0; i < diff; i++)
			{
				LCD_WriteChar(255);
				_delay_ms(200);
			}
		}

		else if(current < prev)
		{
			diff = prev - current;
			for (i = 0; i <=diff; i++)
			{
				LCD_GoTo(2,prev-i);
				LCD_WriteChar(0);
				_delay_ms(200);
			}
			LCD_GoTo(2,prev-diff);
		}
	}/*  end of while 1 */
}/* end of main */