/**
 * @file LDR.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief LDR controls three leds based on lux value
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
#include "LCD_Interface.h"
#include "ADC_interface.h"

int main(void)
{
	u16 read = 0;
	
    /* dio init */
    DIO_Init();

    /* adc init with AREF and 64 prescaller  125 KHZ */
	ADC_Init(REF_AREF,ADC_Scaler_64);
	
	while(1)
	{
        /* read adc value */
		read = ADC_Read(CH_0);
		
        /* level 1 very high light */
		if(read < 60)
		{
            /* turn off three leds */
			DIO_WritePort(PB,0x00);
		}

        /* level 2 high light */
		else if (read < 330)
		{
            /* turn on one led */
			DIO_WritePort(PB,0x00);
			DIO_WritePort(PB,0x01);
		}

        /* level 3 medium light */
		else if (read < 800)
		{
            /*  turn on two leds */
			DIO_WritePort(PB,0x00);
			DIO_WritePort(PB,0x03);
		}
        
        /* level 4 dark */
		else if (read < 1024)
		{
            /* turn on three leds */
			DIO_WritePort(PB,0x07);
		}
			
	}/*  end of while 1 */
}/* end of main */