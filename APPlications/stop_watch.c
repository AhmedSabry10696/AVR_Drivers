#define  F_CPU 8000000UL
#include <util/delay.h>

#include "memory_map.h"
#include "utils.h"
#include "segment.h"

#define START	PINA0
#define STOP	PINA0
#define INCRE	PINA0

#define RESET	PINA1
#define DECRE	PINA1

#define MODE	PINA2

#define CATH	PINB1

#define LED		PINB0

int main(void)
{
	DIO_init();
	u8 flag = 0;
	u8 count = 30;
	
	/* 7 segment common pin */
	DIO_writePin(CATH,LOW);
    
	while (1) 
    {	
		/* display count of 7 segment */
		SEGMENT_display(count);
		
		/* when count = 0 Led flashing */
		if(0 == count)
		{
			/* flash led */
			DIO_togglePin(LED);
			
			/* delay (check for reset and mode during flashing delay) */
			for (u16 i = 0;i<500;i++)
			{
				_delay_ms(1);
				
				/* Reset button pressed */
				if (0 == DIO_readPin(RESET))
				{
					count = 30;
					/* stop flashing */
					DIO_writePin(LED,LOW);
					break;
				}
				
				/* Mode button pressed */
				if (0 == DIO_readPin(MODE))
				{
					while(0 == DIO_readPin(MODE));
					
					/* Stop led flashing */
					DIO_writePin(LED,LOW);
					
					/* while Mode button not pressed check for increment,decrement,mode (OK) */
					while(1 == DIO_readPin(MODE))
					{
						/* flashing 7 segment display to identify config mode */
						DIO_togglePin(CATH);
						_delay_ms(100);

						SEGMENT_display(count);
						
						/* check for increment button */
						if (0 == DIO_readPin(INCRE))
						{
							count++;
							if(count == 100)
							count = 0;
							_delay_ms(80);
						}
						
						/* check for decrement button */
						else if (0 == DIO_readPin(DECRE))
						{
							count--;
							if(count == 255)
							count = 99;
							_delay_ms(80);
						}
					}/* End while mode button released */
					
					/* if mode button pressed again (OK) */
					while(0 == DIO_readPin(MODE));
					
					/* stop flashing 7 segment display */
					DIO_writePin(CATH,LOW);
				}/* end of mode button case */
			}/*end of delay for */
		}/* end if */
		
        else
		{
			/* start stop button pressed */
			if (0 == DIO_readPin(START))
			{
				/* wait till it released */
				while (0 == DIO_readPin(START));
				
				flag = 0;
				for (;count>0;count--)
				{
					SEGMENT_display(count);
					
					/* delay and check for another buttons */
					for (u16 i = 0;i<500;i++)
					{
						_delay_ms(1);
						
						/* stop condition check */
						if (0 == DIO_readPin(STOP))
						{
							while (0 == DIO_readPin(STOP));
							flag = 1;
							break;
						}
						
						/* reset button check */
						if (0 == DIO_readPin(RESET))
						{
							while(0 == DIO_readPin(RESET));
							count = 30;
							flag = 1;
						}
						
						/* Mode button */
						if (0 == DIO_readPin(MODE))
						{
							while(0 == DIO_readPin(MODE));
							flag = 1;
							break;
						}
					}/* end of delay for */
						
					/* stop when stop or reset pressed */
					if(flag == 1)
					{
						break;
					}
				}/* end of count for */
			}/* end of  start stop button if */
						
			/* reset button */
			if (0 == DIO_readPin(RESET))
			{
				count = 30;
			}
					
			/* mode button pressed */
			if (0 == DIO_readPin(MODE))
			{
				/* wait till mode button is released */
				while(0 == DIO_readPin(MODE));
				
				/* while Mode button released check incre and decre and ok */
				while(1 == DIO_readPin(MODE))
				{
					/* flashing 7 segment display to identify config mode */
					DIO_togglePin(CATH);
					_delay_ms(100);
					SEGMENT_display(count);
					
					/* check for increment button */
					if (0 == DIO_readPin(INCRE))
					{
						count++;
						if(count == 100)
						count = 0;
						_delay_ms(80);
					}
					
					/* check for decrement button */
					else if (0 == DIO_readPin(DECRE))
					{
						count--;
						if(count == 255)
						count = 99;
						_delay_ms(80);
					}
				}
				
				/* if mode button pressed again (OK) */
				while(0 == DIO_readPin(MODE));
				
				/* stop flashing 7 segment display */
				DIO_writePin(CATH,LOW);
			}/* end of mode button */
		}
	}/*  end of while 1 */
}/* end of main */
