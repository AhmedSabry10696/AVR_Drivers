#define  F_CPU 8000000UL
#include <util/delay.h>
#include <string.h>
#include "MemMap.h"
#include "Utils.h"

#include "DIO.h"
#include "Timer_Services.h"
#include "Uart_Services.h"
#include "LCD.h"
#include "Servo_Motor.h"
#include "Sensors.h"

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
		Servo_SetPosition(num);	
	}
	else if (strcmp(comm,"lcd")==0)
	{
		LCD_GoTo(3,8);
		LCD_WriteNum(num);
		LCD_WriteString("   ");
	}
	else if(strcmp(comm,"ledon") == 0)
	{
		DIO_WritePin(PINB0+num,HIGH);
	}
	else if (strcmp(comm,"ledoff")==0)
	{
		DIO_WritePin(PINB0+num,LOW);
	}
	else if(strcmp(comm,"temp")==0)
	{
		u8 s[20] = {0};
		u8 size = IntToString(temp/10,s);
		s[size] = '.';
		s[size+1] = (temp%10) + '0';
		s[size+2] = 0;
		
		Uart_SendString("Temperature = ");
		Uart_SendString(s);
		Uart_Send('C');
	}
	else if (strcmp(comm,"pressureg") == 0)
	{
		u8 s[20] = {0};
		u8 size = IntToString(pres/10,s);
		s[size] = '.';
		s[size+1] = (pres%10) + '0';
		s[size+2] = 0;
		
		Uart_SendString("Pressure = ");
		Uart_SendString(s);
		Uart_SendString("KPA");
	}
	else
	{
		Uart_SendString("Undefined Command");
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
	
	DIO_Init();
	LCD_Init();
	Uart_Init();
	Servo_Init();
	ADC_Init(REF_AREF,ADC_Scaler_64);

	LCD_WriteString("Temp: ");
	LCD_GoTo(0,16);
	LCD_WriteChar('C');
	LCD_GoTo(1,0);
	LCD_WriteString("Pres: ");
	LCD_GoTo(1,16);
	LCD_WriteString("kPA");
	
	LCD_GoTo(3,0);
	LCD_WriteString("Num:");
	
	Uart_ReceiveStringAsyn(str);
	
	while(1)
	{
		temp = LM35_TempRead();
		pres = MPX4110_PressureRead();
		
		LCD_GoTo(0,8);
		LCD_WriteNum(temp/10);
		LCD_WriteString("    ");
		
		LCD_GoTo(1,8);
		LCD_WriteNum(pres/10);
		LCD_WriteChar('.');
		LCD_WriteNum(pres%10);
		LCD_WriteString("    ");
		
		if (str[0] != 0)
		{
			extract(str);
			str[0] = 0;
		}
	}
}