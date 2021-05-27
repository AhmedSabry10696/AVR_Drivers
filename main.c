
#define  F_CPU 8000000UL
#include <util/delay.h>

#include "DIO_Interface.h"
#include "SEGMENT_Interface.h"

int main(void)
{
	DIO_Init();  
	
    while (1) 
    {
		for (char i = 0; i < 100; i++)
		{
			SEGMENT_Display(i);
			_delay_ms(200);
		}
    }
}

