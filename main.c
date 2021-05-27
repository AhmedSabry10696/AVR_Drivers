
#define  F_CPU 8000000UL
#include <util/delay.h>

#include "DIO_Interface.h"
#include "Segment.h"

int main(void)
{
	DIO_Init();  
	
    while (1) 
    {
		for (char i = 0; i < 16; i++)
		{
			SEGMENT_Display_Digit(i);
			_delay_ms(1000);
		}
    }
}

