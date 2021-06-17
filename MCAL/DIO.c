/**
 * @file DIO.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief DIO driver
 * @version 0.1
 * @date 25-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "DIO_Interface.h"

void DIO_InitPin(DIO_Pin_type pin, DIO_PinStatus_type status)
{
	u8 pin_num = pin%8;
	DIO_Port_type port = pin/8;
	
	switch (status)
	{
    case OUTPUT:
        switch (port)
        {
        case PA:
            SET_BIT(DDRA,pin_num);
            break;
        case PB:
            SET_BIT(DDRB,pin_num);
            break;
        case PC:
            SET_BIT(DDRC,pin_num);
            break;
        case PD:
            SET_BIT(DDRD,pin_num);
            break;
        }
        break;
    
    case INFREE:
        switch (port)
        {
        case PA:
            CLEAR_BIT(DDRA,pin_num);
            break;
        case PB:
            CLEAR_BIT(DDRB,pin_num);
            break;
        case PC:
            CLEAR_BIT(DDRC,pin_num);
            break;
        case PD:
            CLEAR_BIT(DDRD,pin_num);
            break;
        }
        break;
    
    case INPULLUP:
        switch (port)
        {
        case PA:
            CLEAR_BIT(DDRA,pin_num);
            SET_BIT(PORTA,pin_num);
            break;
        case PB:
            CLEAR_BIT(DDRB,pin_num);
            SET_BIT(PORTB,pin_num);
            break;
        case PC:
            CLEAR_BIT(DDRC,pin_num);
            SET_BIT(PORTC,pin_num);
            break;
        case PD:
            CLEAR_BIT(DDRD,pin_num);
            SET_BIT(PORTD,pin_num);
            break;
        }
        break;
	}	
}

void DIO_WritePin(DIO_Pin_type pin, DIO_Voltage_type volt)
{
	u8 pin_num = pin%8;
	DIO_Port_type port = pin/8;
	
	if (HIGH == volt)
	{
        switch (port)
        {
        case PA:
            SET_BIT(PORTA,pin_num);
            break;
        case PB:
            SET_BIT(PORTB,pin_num);
            break;
        case PC:
            SET_BIT(PORTC,pin_num);
            break;
        case PD:
            SET_BIT(PORTD,pin_num);
            break;
        }
	}
	else if (LOW == volt)
	{
		switch(port)
        {
        case PA:
            CLEAR_BIT(PORTA,pin_num);
            break;
        case PB:
            CLEAR_BIT(PORTB,pin_num);
            break;
        case PC:
            CLEAR_BIT(PORTC,pin_num);
            break;
        case PD:
            CLEAR_BIT(PORTD,pin_num);
            break;
        }
	}
}

void DIO_TogglePin(DIO_Pin_type pin)
{
	u8 pin_num = pin%8;
	DIO_Port_type port = pin/8;
	DIO_Voltage_type volt = LOW;

	switch (port)
	{
		case PA:
			TOGGLE_BIT(PORTA,pin_num);
			break;
		case PB:
			TOGGLE_BIT(PORTB,pin_num);
			break;
		case PC:
			TOGGLE_BIT(PORTC,pin_num);
			break;
		case PD:
			TOGGLE_BIT(PORTD,pin_num);
			break;
	}
}

DIO_Voltage_type DIO_ReadPin(DIO_Pin_type pin)
{
    u8 pin_num = pin%8;
    DIO_Port_type port = pin/8;
    DIO_Voltage_type volt = LOW;

    switch (port)
    {
    case PA:
        volt = READ_BIT(PINA,pin_num);
        break;
    case PB:
        volt = READ_BIT(PINB,pin_num);
        break;
    case PC:
        volt = READ_BIT(PINC,pin_num);
        break;
    case PD:
        volt = READ_BIT(PIND,pin_num);
        break;
    }
    return volt;
}

void DIO_WritePort(DIO_Port_type port, u8 value)
{
    switch (port)
    {
    case PA:
        PORTA = value;
        break;
    case PB:
        PORTB = value;
        break;
    case PC:
        PORTC = value;
        break;
    case PD:
        PORTD = value;
        break;
    }
}

void DIO_EditPort_LowerHalf(DIO_Port_type port, u8 value)
{
	switch (port)
	{
	case PA:
		EDIT_FOUR_LBITS(PORTA,value);
		break;
	case PB:
		EDIT_FOUR_LBITS(PORTB,value);
		break;
	case PC:
		EDIT_FOUR_LBITS(PORTC,value);
		break;
	case PD:
        EDIT_FOUR_LBITS(PORTD,value);
		break;
	}
}

void DIO_EditPort_HigherHalf(DIO_Port_type port, u8 value)
{
	switch (port)
	{
	case PA:
		EDIT_FOUR_HBITS(PORTA,value);
		break;
	case PB:
		EDIT_FOUR_HBITS(PORTB,value);
		break;
	case PC:
		EDIT_FOUR_HBITS(PORTC,value);
		break;
	case PD:
		EDIT_FOUR_HBITS(PORTD,value);
		break;
	}
}

u8 DIO_ReadPort(DIO_Port_type port)
{
    u8 value = 0;
    switch (port)
    {
    case PA:
        value = PINA;
        break;
    case PB:
        value = PINB;
        break;
    case PC:
        value = PINC;
        break;
    case PD:
        value = PIND;
        break;
    }
    return value;
}

void DIO_Init(void)
{
    DIO_Pin_type i;
    
    for (i = 0; i < TOTAL_PINS; i++)
    {
        DIO_InitPin(i,PinsStatus[i]);
    }
}