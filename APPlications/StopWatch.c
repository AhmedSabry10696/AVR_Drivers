#define  F_CPU 8000000UL
#include <util/delay.h>

#include "MemMap.h"
#include "Utils.h"
#include "SEGMENT_Interface.h"

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
	DIO_Init();
	u8 flag = 0;
	u8 count = 30;
	
	/* 7 segment common pin */
	DIO_WritePin(CATH,LOW);
    
	while (1) 
    {	
		/* display count of 7 segment */
		SEGMENT_Display(count);
		
		/* when count = 0 Led flashing */
		if(0 == count)
		{
			/* flash led */
			DIO_TogglePin(LED);
			
			/* delay (check for reset and mode during flashing delay) */
			for (u16 i = 0;i<500;i++)
			{
				_delay_ms(1);
				
				/* Reset button pressed */
				if (0 == DIO_ReadPin(RESET))
				{
					count = 30;
					/* stop flashing */
					DIO_WritePin(LED,LOW);
					break;
				}
				
				/* Mode button pressed */
				if (0 == DIO_ReadPin(MODE))
				{
					while(0 == DIO_ReadPin(MODE));
					
					/* Stop led flashing */
					DIO_WritePin(LED,LOW);
					
					/* while Mode button not pressed check for increment,decrement,mode (OK) */
					while(1 == DIO_ReadPin(MODE))
					{
						/* flashing 7 segment display to identify config mode */
						DIO_TogglePin(CATH);
						_delay_ms(100);

						SEGMENT_Display(count);
						
						/* check for increment button */
						if (0 == DIO_ReadPin(INCRE))
						{
							count++;
							if(count == 100)
							count = 0;
							_delay_ms(80);
						}
						
						/* check for decrement button */
						else if (0 == DIO_ReadPin(DECRE))
						{
							count--;
							if(count == 255)
							count = 99;
							_delay_ms(80);
						}
					}/* End while mode button released */
					
					/* if mode button pressed again (OK) */
					while(0 == DIO_ReadPin(MODE));
					
					/* stop flashing 7 segment display */
					DIO_WritePin(CATH,LOW);
				}/* end of mode button case */
			}/*end of delay for */
		}/* end if */
		
        else
		{
			/* start stop button pressed */
			if (0 == DIO_ReadPin(START))
			{
				/* wait till it released */
				while (0 == DIO_ReadPin(START));
				
				flag = 0;
				for (;count>0;count--)
				{
					SEGMENT_Display(count);
					
					/* delay and check for another buttons */
					for (u16 i = 0;i<500;i++)
					{
						_delay_ms(1);
						
						/* stop condition check */
						if (0 == DIO_ReadPin(STOP))
						{
							while (0 == DIO_ReadPin(STOP));
							flag = 1;
							break;
						}
						
						/* reset button check */
						if (0 == DIO_ReadPin(RESET))
						{
							while(0 == DIO_ReadPin(RESET));
							count = 30;
							flag = 1;
						}
						
						/* Mode button */
						if (0 == DIO_ReadPin(MODE))
						{
							while(0 == DIO_ReadPin(MODE));
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
			if (0 == DIO_ReadPin(RESET))
			{
				count = 30;
			}
					
			/* mode button pressed */
			if (0 == DIO_ReadPin(MODE))
			{
				/* wait till mode button is released */
				while(0 == DIO_ReadPin(MODE));
				
				/* while Mode button released check incre and decre and ok */
				while(1 == DIO_ReadPin(MODE))
				{
					/* flashing 7 segment display to identify config mode */
					DIO_TogglePin(CATH);
					_delay_ms(100);
					SEGMENT_Display(count);
					
					/* check for increment button */
					if (0 == DIO_ReadPin(INCRE))
					{
						count++;
						if(count == 100)
						count = 0;
						_delay_ms(80);
					}
					
					/* check for decrement button */
					else if (0 == DIO_ReadPin(DECRE))
					{
						count--;
						if(count == 255)
						count = 99;
						_delay_ms(80);
					}
				}
				
				/* if mode button pressed again (OK) */
				while(0 == DIO_ReadPin(MODE));
				
				/* stop flashing 7 segment display */
				DIO_WritePin(CATH,LOW);
			}/* end of mode button */
		}
	}/*  end of while 1 */
}/* end of main */