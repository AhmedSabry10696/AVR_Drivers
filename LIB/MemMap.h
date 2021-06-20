/**
 * @file MemMap.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Memory map for Atmega32 micro controller
 * @version 0.1
 * @date 24-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MEMMAP_H_
#define MEMMAP_H_

#include "StdTypes.h"

/********** DIO Registers **************/
#define PINA    (*((volatile u8 *)0x39))
#define DDRA    (*((volatile u8 *)0x3A))
#define PORTA   (*((volatile u8 *)0x3B))

#define PINB    (*((volatile u8 *)0x36))
#define DDRB    (*((volatile u8 *)0x37))
#define PORTB   (*((volatile u8 *)0x38))

#define PINC    (*((volatile u8 *)0x33))
#define DDRC    (*((volatile u8 *)0x34))
#define PORTC   (*((volatile u8 *)0x35))

#define PIND    (*((volatile u8 *)0x30))
#define DDRD    (*((volatile u8 *)0x31))
#define PORTD   (*((volatile u8 *)0x32))
/****************************************/

/*********** ADC Registers *************/
#define SFIOR   (*((volatile u8 *)0x50))
#define ADTS0   5
#define ADTS1   6
#define ADTS2   7

#define ADMUX   (*((volatile u8 *)0x27))
#define ADLAR   5
#define REFS0   6
#define REFS1   7

#define ADCSRA  (*((volatile u8 *)0x26))
#define ADPS0   0
#define ADPS1   1
#define ADPS2   2
#define ADIE    3
#define ADIF    4
#define ADATE   5
#define ADSC    6
#define ADEN    7

#define ADCH    (*((volatile u8 *)0x25))
#define ADCL    (*((volatile u8 *)0x24))
#define ADC     (*((volatile u16*)0x24))
/****************************************/

#endif /* MEMMAP_H_ */