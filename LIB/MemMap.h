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

/********External Interrupt REG*********/
#define MCUCR   (*((volatile u8 *)0x55))
#define ISC00   0
#define ISC01   1
#define ISC10   2
#define ISC11   3

#define MCUCSR  (*((volatile u8 *)0x54))
#define ISC2    6

#define GICR    (*((volatile u8 *)0x5B))
#define INT2    5
#define INT0    6
#define INT1    7

#define GIFR    (*((volatile u8 *)0x5A))
#define INTF2   5
#define INTF0   6
#define INTF1   7

/**************** Interrupt service routine ********************/

/* ISR runs with global interrupts initially enabled */
/* infinitely recursive interrupts: UART interrupts or level-triggered external interrupts */
#define ISR_NOBLOCK   __attribute__((interrupt))

/* ISR is created with no prologue or epilogue code */
#define ISR_NAKED     __attribute__((naked))

#define ISR(vector,...) void vector (void) __attribute__ ((signal))__VA_ARGS__ ;\
void vector (void)

/************ Interrupt functions ************/
# define sei()  __asm__ __volatile__ ("sei" ::)
# define cli()  __asm__ __volatile__ ("cli" ::)
# define reti() __asm__ __volatile__ ("reti" ::)
# define ret()  __asm__ __volatile__ ("ret" ::)

/********** Interrupt Vector Table ***********/
/* External Interrupt Request 0 */
#define INT0_VECT __vector_1
/* External Interrupt Request 1 */
#define INT1_VECT __vector_2
/* External Interrupt Request 2 */
#define INT2_VECT __vector_3
/* Timer/Counter2 Compare Match */
#define TIMER2_COMP_VECT __vector_4
/* Timer/Counter2 Overflow */
#define TIMER2_OVF_VECT __vector_5
/* Timer/Counter1 Capture Event */
#define TIMER1_CAPT_VECT __vector_6
/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPA_VECT __vector_7
/* Timer/Counter1 Compare Match B */
#define TIMER1_COMPB_VECT __vector_8
/* Timer/Counter1 Overflow */
#define TIMER1_OVF_VECT __vector_9
/* Timer/Counter0 Compare Match */
#define TIMER0_COMP_VECT __vector_10
/* Timer/Counter0 Overflow */
#define TIMER0_OVF_VECT __vector_11
/* Serial Transfer Complete */
#define SPI_STC_VECT __vector_12
/* USART, Rx Complete */
#define USART_RXC_VECT __vector_13
/* USART Data Register Empty */
#define USART_UDRE_VECT __vector_14
/* USART, Tx Complete */
#define USART_TXC_VECT __vector_15
/* ADC Conversion Complete */
#define ADC_VECT __vector_16
/* EEPROM Ready */
#define EE_RDY_VECT __vector_17
/* Analog Comparator */
#define ANA_COMP_VECT __vector_18
/* 2-wire Serial Interface */
#define TWI_VECT __vector_19
/* Store Program Memory Ready */
#define SPM_RDY_VECT __vector_20
/* Bad Interrupt Vector */
#define BAD_VECT __vector_default
/*******************************************/


#endif /* MEMMAP_H_ */