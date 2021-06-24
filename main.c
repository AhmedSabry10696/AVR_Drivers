#define  F_CPU 8000000UL
#include <util/delay.h>

#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "Ext_Interrupt.h"

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
	sei();
	EXI_Enable(EX_INT0);
	EXI_Enable(EX_INT1);
	EXI_Enable(EX_INT2);
	
	EXI_TriggerEdge(EX_INT0,FALLING_EDGE);
	EXI_TriggerEdge(EX_INT1,RISING_EDGE);
	EXI_TriggerEdge(EX_INT2,FALLING_EDGE);
	
	EXI_SetCallBack(EX_INT0,toggle_led1);
	EXI_SetCallBack(EX_INT1,toggle_led2);
	EXI_SetCallBack(EX_INT2,toggle_led3);
	
	while(1)
	{
		DIO_TogglePin(PINC3);
		_delay_ms(2000);
	}
}