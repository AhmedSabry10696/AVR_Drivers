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

#endif /* MEMMAP_H_ */