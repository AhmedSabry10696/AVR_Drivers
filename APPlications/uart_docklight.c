#define  F_CPU 8000000UL
#include <util/delay.h>
#include <string.h>
#include "memory_map.h"
#include "utils.h"

#include "dio.h"
#include "timer_services.h"
#include "uart_services.h"
#include "lcd.h"
#include "servo_motor.h"
#include "sensors.h"

u16 temp,pres;

u8 IntToString(u8 num, u8 *str)
{
    u8 digit,i = 0,temp,size;
    
    while(num > 0)
    {
        digit = num % 10;
        str[i] = digit + '0';
        i++;
        num /= 10;
    }
    size = i;
    
    /* revers string */
    for (i = 0; i < size/2; i++)
    {
        temp = str[i];
        str[i] = str[size-i-1];
        str[size-i-1] = temp;
    }
    str[size] = '\0';
	return size;
}

void check(u8 *comm,u8 num)
{
	if (strcmp(comm,"servo") == 0)
	{
		SERVO_setPosition(num);	
	}
	else if (strcmp(comm,"lcd")==0)
	{
		LCD_goTo(3,8);
		LCD_writeNum(num);
		LCD_writeString("   ");
	}
	else if(strcmp(comm,"ledon") == 0)
	{
		DIO_writePin(PINB0+num,HIGH);
	}
	else if (strcmp(comm,"ledoff")==0)
	{
		DIO_writePin(PINB0+num,LOW);
	}
	else if(strcmp(comm,"temp")==0)
	{
		u8 s[20] = {0};
		u8 size = IntToString(temp/10,s);
		s[size] = '.';
		s[size+1] = (temp%10) + '0';
		s[size+2] = 0;
		
		UART_sendString("Temperature = ");
		UART_sendString(s);
		UART_send('C');
	}
	else if (strcmp(comm,"pressure") == 0)
	{
		u8 s[20] = {0};
		u8 size = IntToString(pres/10,s);
		s[size] = '.';
		s[size+1] = (pres%10) + '0';
		s[size+2] = 0;
		
		UART_sendString("Pressure = ");
		UART_sendString(s);
		UART_sendString("KPA");
	}
	else
	{
		UART_sendString("Undefined Command");
	}
}

void extract(u8 *str)
{
	u8 comm[10] = {0};
	u8 num = 0,i=0;

	while (str[i] != ' '&&str[i] !=0)
	{
		comm[i] = str[i];
		i++;
	}
	comm[i] = 0;
	
	i++;
	while (str[i] != 0)
	{
		
		num = (num*10)+ str[i]-'0';
		i++;
	}
	check(comm,num);
}

int main(void)
{
	char str[100] = {0};
	sei();
	
	DIO_init();
	LCD_init();
	UART_init();
	SERVO_init();
	ADC_init(REF_AREF,ADC_Scaler_64);

	LCD_writeString("Temp: ");
	LCD_goTo(0,16);
	LCD_writeChar('C');
	LCD_goTo(1,0);
	LCD_writeString("Pres: ");
	LCD_goTo(1,16);
	LCD_writeString("kPA");
	
	LCD_goTo(3,0);
	LCD_writeString("Num:");
	
	UART_receiveStringAsyn(str);
	
	while(1)
	{
		temp = LM35_tempRead();
		pres = MPX4110_pressureRead();
		
		LCD_goTo(0,8);
		LCD_writeNum(temp/10);
		LCD_writeString("    ");
		
		LCD_goTo(1,8);
		LCD_writeNum(pres/10);
		LCD_writeChar('.');
		LCD_writeNum(pres%10);
		LCD_writeString("    ");
		
		if (str[0] != 0)
		{
			extract(str);
			str[0] = 0;
		}
	}
}
