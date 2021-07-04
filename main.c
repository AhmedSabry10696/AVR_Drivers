#define  F_CPU 8000000UL
#include <util/delay.h>
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "Ext_Interrupt.h"
#include "ADC_Interface.h"
#include "Timer.h"


int main(void)
{	
	sei();
	/* DIO init */
	DIO_Init();
	ADC_Init(REF_AREF,ADC_Scaler_64);

	Timer0_Init(TIMER0_CTC,TIMER0_SCALER_8);

	while(1)
	{

	}
}