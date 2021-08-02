/**
 * @file dio.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief DIO driver
 * @version 0.1
 * @date 25-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "dio.h"

void DIO_initPin(DioPin_type pin, DioPinStatus_type status)
{
    u8 pin_num = pin % 8;
    DioPort_type port = pin / 8;

    switch (status)
    {
    case OUTPUT:
        switch (port)
        {
        case PA:
            SET_BIT(DDRA, pin_num);
            break;
        case PB:
            SET_BIT(DDRB, pin_num);
            break;
        case PC:
            SET_BIT(DDRC, pin_num);
            break;
        case PD:
            SET_BIT(DDRD, pin_num);
            break;
        }
        break;

    case INFREE:
        switch (port)
        {
        case PA:
            CLR_BIT(DDRA, pin_num);
            break;
        case PB:
            CLR_BIT(DDRB, pin_num);
            break;
        case PC:
            CLR_BIT(DDRC, pin_num);
            break;
        case PD:
            CLR_BIT(DDRD, pin_num);
            break;
        }
        break;

    case INPULLUP:
        switch (port)
        {
        case PA:
            CLR_BIT(DDRA, pin_num);
            SET_BIT(PORTA, pin_num);
            break;
        case PB:
            CLR_BIT(DDRB, pin_num);
            SET_BIT(PORTB, pin_num);
            break;
        case PC:
            CLR_BIT(DDRC, pin_num);
            SET_BIT(PORTC, pin_num);
            break;
        case PD:
            CLR_BIT(DDRD, pin_num);
            SET_BIT(PORTD, pin_num);
            break;
        }
        break;
    }
}

void DIO_writePin(DioPin_type pin, DioVoltage_type volt)
{
    u8 pin_num = pin % 8;
    DioPort_type port = pin / 8;

    if (HIGH == volt)
    {
        switch (port)
        {
        case PA:
            SET_BIT(PORTA, pin_num);
            break;
        case PB:
            SET_BIT(PORTB, pin_num);
            break;
        case PC:
            SET_BIT(PORTC, pin_num);
            break;
        case PD:
            SET_BIT(PORTD, pin_num);
            break;
        }
    }
    else if (LOW == volt)
    {
        switch (port)
        {
        case PA:
            CLR_BIT(PORTA, pin_num);
            break;
        case PB:
            CLR_BIT(PORTB, pin_num);
            break;
        case PC:
            CLR_BIT(PORTC, pin_num);
            break;
        case PD:
            CLR_BIT(PORTD, pin_num);
            break;
        }
    }
}

void DIO_togglePin(DioPin_type pin)
{
    u8 pin_num = pin % 8;
    DioPort_type port = pin / 8;

    switch (port)
    {
    case PA:
        TOG_BIT(PORTA, pin_num);
        break;
    case PB:
        TOG_BIT(PORTB, pin_num);
        break;
    case PC:
        TOG_BIT(PORTC, pin_num);
        break;
    case PD:
        TOG_BIT(PORTD, pin_num);
        break;
    }
}

DioVoltage_type DIO_readPin(DioPin_type pin)
{
    u8 pin_num = pin % 8;
    DioPort_type port = pin / 8;
    DioVoltage_type volt = LOW;

    switch (port)
    {
    case PA:
        volt = READ_BIT(PINA, pin_num);
        break;
    case PB:
        volt = READ_BIT(PINB, pin_num);
        break;
    case PC:
        volt = READ_BIT(PINC, pin_num);
        break;
    case PD:
        volt = READ_BIT(PIND, pin_num);
        break;
    }
    return volt;
}

void DIO_writePort(DioPort_type port, const u8 value)
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

void DIO_editPort_lowNibble(DioPort_type port, u8 value)
{
    switch (port)
    {
    case PA:
        EDIT_LOW_NIBBLE(PORTA, value);
        break;
    case PB:
        EDIT_LOW_NIBBLE(PORTB, value);
        break;
    case PC:
        EDIT_LOW_NIBBLE(PORTC, value);
        break;
    case PD:
        EDIT_LOW_NIBBLE(PORTD, value);
        break;
    }
}

void DIO_editPort_highNibble(DioPort_type port, u8 value)
{
    switch (port)
    {
    case PA:
        EDIT_HIGH_NIBBLE(PORTA, value);
        break;
    case PB:
        EDIT_HIGH_NIBBLE(PORTB, value);
        break;
    case PC:
        EDIT_HIGH_NIBBLE(PORTC, value);
        break;
    case PD:
        EDIT_HIGH_NIBBLE(PORTD, value);
        break;
    }
}

u8 DIO_readPort(DioPort_type port)
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

void DIO_init(void)
{
    DioPin_type i;

    for (i = 0; i < TOTAL_PINS; i++)
    {
        DIO_initPin(i, pins_status[i]);
    }
}
