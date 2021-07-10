#define  F_CPU 8000000UL
#include <util/delay.h>
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "Ext_Interrupt.h"
#include "ADC_Interface.h"
#include "Timer.h"
#include "Timer_Services.h"

const int x = 10;

int main(void)
{	
	//sei();
	int *ptr = &x;
	*ptr = 30;

	/* DIO init */
	DIO_Init();

	while(1)
	{

	}
}