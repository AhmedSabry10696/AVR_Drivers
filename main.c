
#define  F_CPU 8000000UL
#include <util/delay.h>

#include "DIO_Interface.h"
#include "DC_Motor.h"

int main(void)
{
	DIO_Init();  
	DIO_WritePin(PINB0,HIGH);
	DIO_WritePin(PINB1,HIGH);
	_delay_ms(3000);
    while (1) 
    {
		if (DIO_ReadPin(PINC0) == LOW)
		{
			DC_Motor_CW();
			
		}
		if (DIO_ReadPin(PINC1) == LOW)
		{
			DC_Motor_CCW();
		}
		if(DIO_ReadPin(PINC2) == LOW)
		{
			DC_Motor_Stop();
		}
		_delay_ms(200);
    }
}

