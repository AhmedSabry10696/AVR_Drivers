#define  F_CPU 8000000UL
#include <util/delay.h>
#include "MemMap.h"
#include "Utils.h"
#include "LCD_Interface.h"
#include "Keypad.h"

u8 key,from,to,result_f = 0;
u32 num;

void welcome(void)
{
	LCD_WriteStringRowCol(0,6,"Welcome To");
	LCD_WriteStringRowCol(1,1,"Converter Program");
	_delay_ms(1000);
	LCD_Clear();
}

void convert_from(void)
{
	LCD_Clear();			  
	LCD_WriteStringRowCol(0,0,"Convert From: ");
	LCD_WriteStringRowCol(1,0,"1 -> Decimal.");
	LCD_WriteStringRowCol(2,0,"2 -> Binary.");
	LCD_WriteStringRowCol(3,0,"3 -> Hexadecimal.");
}

void convert_to(void)
{
	LCD_WriteStringRowCol(0,0,"Convert To:    ");
}

void converter(void)
{
	LCD_Clear();
	if (from == '1')
	{
		LCD_WriteString("Decimal: ");
	}
	else if (from == '2')
	{
		LCD_WriteString("Binary: ");
	}
	else if (from == '3')
	{
		LCD_WriteString("Hexa: ");
	}
	
	LCD_GoTo(2,0);
	if (to == '1')
	{
		LCD_WriteString("Decimal: ");
	}
	else if (to == '2')
	{
		LCD_WriteString("Binary: ");
	}
	else if (to == '3')
	{
		LCD_WriteString("Hexa: ");
	}

	LCD_GoTo(0,10);
}

void get_from_to(void)
{
	convert_from();
	while (key != '1' && key != '2' && key != '3')
	{
		key = KEYPAD_GeyKey();
	}
	from = key;
	key = '.';

	convert_to();
	while (key != '1' && key != '2' && key != '3')
	{
		key = KEYPAD_GeyKey();
	}
	to = key;
	
	converter();
}

void invalid_choice(void)
{
	LCD_Clear();
	LCD_writeString("   Invalid Choice");
	LCD_WriteStringRowCol(2,0,"  Try Again Later");
	_delay_ms(1000);
}

int main(void)
{
	DIO_Init();
	LCD_Init();
	welcome();
	get_from_to();

	while(1)
	{
		key = KEYPAD_GeyKey();

		/* if any key pressed */
		if (key != NO_KEY)
		{
			if (result_f == 1)
			{
				result_f = 0;
				LCD_ClearCells(0,10,9);
				LCD_ClearCells(2,10,9);
				LCD_GoTo(0,10);
			}
		
			/* read decimal */
			if (from == '1')
			{	
				if (key >= '0' && key <= '9')
				{
					LCD_WriteChar(key);
					num = num*10 + key - '0';
				}
			}

			/* read binary */
			else if (from == '2')
			{
				if (key == '1'|| key == '0')
				{
					LCD_WriteChar(key);
					num = num*2 + key - '0';
				}
				
			}

			/* read hexadecimal */
			else if (from == '3')
			{
				if ((key >= '0' && key <= '9') || (key >= 'A' && key <= 'F'))
				{
					LCD_WriteChar(key);
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
				LCD_GoTo(2,10);

				/* print num as decimal */
				if (to == '1')
				{
					LCD_WriteNum(num);
				}

				/* print num as binary */
				else if (to == '2')
				{
					LCD_WriteBinary(num);
				}

				/* print num as hexadecimal */
				else if (to == '3')
				{
					LCD_WriteHex(num);
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