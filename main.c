#define  F_CPU 8000000UL
#include <util/delay.h>
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "Ext_Interrupt.h"
#include "Stepper_Motor.h"

void toggle_led1(void)
{
	DIO_TogglePin(PINC0);
	_delay_ms(1000);
	DIO_TogglePin(PINC0);
	_delay_ms(1000);
}
void toggle_led2(void)
{
	DIO_TogglePin(PINC1);
	_delay_ms(1000);
	DIO_TogglePin(PINC1);
	_delay_ms(1000);

}
void toggle_led3(void)
{
	DIO_TogglePin(PINC2);
	_delay_ms(1000);
	DIO_TogglePin(PINC2);
	_delay_ms(1000);
}


int main(void)
{	
	/* DIO init */
	DIO_Init();

	
	while(1)
	{
		for (int i = 0;i<9;i++)
		{
			Stepper_UniPolarHalf_CW();
		}
		_delay_ms(2000);
		for (int i = 0;i<9;i++)
		{
			Stepper_UniPolarHalf_CCW();
		}
		_delay_ms(2000);
	}
}