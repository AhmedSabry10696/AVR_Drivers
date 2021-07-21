/**
 * @file VolumeLevel.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief volume level control 
 * @version 0.1
 * @date 20-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define  F_CPU 8000000UL
#include <util/delay.h>
#include "MemMap.h"
#include "Utils.h"
#include "LCD.h"
#include "ADC.h"

/**
 * @brief get previous and current value of the volume
 * 
 * @param prev prev reading
 * @param current current reading 
 */
void volume_diff(u8 *prev,u8 *current)
{
    /* t for store the prev value of volume */
	static u8 t;

    /* read adc value */
	u16 read = ADC_Read(CH_0);

    /* map adc value from 0:1023 to 0:20 */
	read = read*20/1024;
	
    /* return prev value of the volume */
	*prev = t;

    /* return current value of the volume */
	*current = read;

    /* update prev value in the function to current value */ 
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
        /* get prev and current values of the volume */
		volume_diff(&prev, &current);

        /* if current more than prev then volume is growing up */
		if(current > prev)
		{
            /* difference to grow */
			diff = current - prev;
			for (i = 0; i < diff; i++)
			{
				LCD_WriteChar(255);
				_delay_ms(200);
			}
		}

        /* if current less than prev then volume is declining */
		else if(current < prev)
		{
            /* difference to decline */
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