
#define  F_CPU 8000000UL
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#define  delay 200

u8 MAN[] = {
	0x0E,
	0x0E,
	0x04,
	0x1F,
	0x0E,
	0x0E,
	0x0A,
	0x0A
};

u8 ARROW[] = {
	0x00,
	0x00,
	0x02,
	0x1F,
	0x02,
	0x00,
	0x00,
	0x00
};

int main(void)
{
	DIO_Init();
	LCD_Init();
	
	LCD_Create_Char(MAN,0);
	LCD_Create_Char(ARROW,1);

	LCD_WriteStringRowCol(0,0,"Char: ");
	LCD_WriteStringRowCol(2,0,"Asci: ");
	
    while (1) 
    {	
		for (u8 i = 'A';i<='Z';i++)
		{
			LCD_GoTo(0,8);
			LCD_WriteChar(i);
			
			LCD_GoTo(2,8);
			LCD_WriteNum(i);
			
			_delay_ms(300);
		}	
    }
}


/************************************************************************/
/* for (u8 i = 0;i<20;i++)
{
/* print man 
LCD_GoTo(0,19);
LCD_WriteChar(0);

/* print arrow 
LCD_GoTo(0,i);
LCD_WriteChar(1);

/* when arrow met the man
if (19 == i)
{
LCD_GoTo(0,19);
LCD_WriteChar(255);
_delay_ms(500);
}

_delay_ms(delay);
LCD_Clear();
}                                                                    
************************************************************************/