#define  F_CPU 8000000UL
#include <util/delay.h>
#include "memory_map.h"
#include "utils.h"
#include "lcd.h"
#include "keypad.h"

u8 key,from,to,result_f = 0;
u32 num;

void welcome(void)
{
	LCD_writeStringRowCol(0,6,"Welcome To");
	LCD_writeStringRowCol(1,1,"Converter Program");
	_delay_ms(1000);
	LCD_clear();
}

void convert_from(void)
{
	LCD_clear();			  
	LCD_writeStringRowCol(0,0,"Convert From: ");
	LCD_writeStringRowCol(1,0,"1 -> Decimal.");
	LCD_writeStringRowCol(2,0,"2 -> Binary.");
	LCD_writeStringRowCol(3,0,"3 -> Hexadecimal.");
}

void convert_to(void)
{
	LCD_writeStringRowCol(0,0,"Convert To:    ");
}

void converter(void)
{
	LCD_clear();
	if (from == '1')
	{
		LCD_writeString("Decimal: ");
	}
	else if (from == '2')
	{
		LCD_writeString("Binary: ");
	}
	else if (from == '3')
	{
		LCD_writeString("Hexa: ");
	}
	
	LCD_goTo(2,0);
	if (to == '1')
	{
		LCD_writeString("Decimal: ");
	}
	else if (to == '2')
	{
		LCD_writeString("Binary: ");
	}
	else if (to == '3')
	{
		LCD_writeString("Hexa: ");
	}

	LCD_goTo(0,10);
}

void get_from_to(void)
{
	convert_from();
	while (key != '1' && key != '2' && key != '3')
	{
		key = KEYPAD_getKey();
	}
	from = key;
	key = '.';

	convert_to();
	while (key != '1' && key != '2' && key != '3')
	{
		key = KEYPAD_getKey();
	}
	to = key;
	
	converter();
}

void invalid_choice(void)
{
	LCD_clear();
	LCD_writeString("   Invalid Choice");
	LCD_writeStringRowCol(2,0,"  Try Again Later");
	_delay_ms(1000);
}

int main(void)
{
	DIO_init();
	LCD_init();
	welcome();
	get_from_to();

	while(1)
	{
		key = KEYPAD_getKey();

		/* if any key pressed */
		if (key != NO_KEY)
		{
			if (result_f == 1)
			{
				result_f = 0;
				LCD_clearCells(0,10,9);
				LCD_clearCells(2,10,9);
				LCD_goTo(0,10);
			}
		
			/* read decimal */
			if (from == '1')
			{	
				if (key >= '0' && key <= '9')
				{
					LCD_writeChar(key);
					num = num*10 + key - '0';
				}
			}

			/* read binary */
			else if (from == '2')
			{
				if (key == '1'|| key == '0')
				{
					LCD_writeChar(key);
					num = num*2 + key - '0';
				}
				
			}

			/* read hexadecimal */
			else if (from == '3')
			{
				if ((key >= '0' && key <= '9') || (key >= 'A' && key <= 'F'))
				{
					LCD_writeChar(key);
					if (key > '9')
					{
						num = num*16 + key - 'A'+10;
					}
					else
					{
						num = num*16 + key- '0';
					}
				}
			}

			if (key == '=')
			{
				LCD_goTo(2,10);

				/* print num as decimal */
				if (to == '1')
				{
					LCD_writeNum(num);
				}

				/* print num as binary */
				else if (to == '2')
				{
					LCD_writeBinary(num);
				}

				/* print num as hexadecimal */
				else if (to == '3')
				{
					LCD_writeHex(num);
				}
				num = 0;
				result_f = 1;
			}
			
			/* clear key */
			if (key == 'C')
			{
				num = 0;
				to = 0;
				from = 0;
				result_f = 0;
				get_from_to();
			}
			
		}
	}/*  end of while 1 */
}/* end of main */