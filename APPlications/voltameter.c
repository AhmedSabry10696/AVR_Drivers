/**
 * @file Voltameter.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief print voltage value on lcd
 * @version 0.1
 * @date 20-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define  F_CPU 8000000UL
#include <util/delay.h>
#include "memory_map.h"
#include "utils.h"
#include "lcd.h"
#include "adc.h"

int main(void)
{
	u16 read = 0;
	f32 volt = 0;

	/* dio init */
	DIO_init();

	/* lcd init */
	LCD_init();

	/* adc init with AREF volt and 64 prescaller  125 KHZ */
	ADC_init(REF_AREF,ADC_Scaler_64);
	
	/* print labels on lcd */
	LCD_writeString("ADC Read: ");
	LCD_goTo(2,0);
	LCD_writeString(" Voltage: ");
	
	while(1)
	{
		/* read adc value */
		read = ADC_read(CH_0);

		/* convert adc read to volt */
		volt = read*5.0/1023;
		
		/* clear 4 cells to print adc read */
		LCD_clearCells(0,12,4);
		LCD_writeNum(read);

		/* clear 4 cells to print volt value */
		LCD_clearCells(2,12,4);
		LCD_writeFloat(volt);

		_delay_ms(300);
	}/*  end of while 1 */
}/* end of main */
