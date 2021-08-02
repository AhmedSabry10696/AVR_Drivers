/**
 * @file memory_map.h
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

#include "std_types.h"

/*******************************************************************************************/
/************************************** DIO Registers **************************************/
/*******************************************************************************************/
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

/*******************************************************************************************/
/************************************** ADC Registers **************************************/
/*******************************************************************************************/
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

/*******************************************************************************************/
/**************************** External Interrupt Registers *********************************/
/*******************************************************************************************/
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

/*******************************************************************************************/
/******************************* Interrupt Service Routines ********************************/
/*******************************************************************************************/
#define _VECTOR(N) __vector_ ## N

/* ISR runs with global interrupts initially enabled */
/* infinitely recursive interrupts: UART interrupts or level-triggered external interrupts */
#define ISR_NOBLOCK   __attribute__((interrupt))

/* ISR is created with no prologue or epilogue code dev have to context save and reti at end */
#define ISR_NAKED     __attribute__((naked))

/* ISR Macro with variable arguments (variadic function) */
#define ISR(vector,...) void vector (void) __attribute__ ((signal))__VA_ARGS__;\
void vector (void)

/*******************************************************************************************/
/******************************* Inline Assembly Macros ************************************/
/*******************************************************************************************/
# define sei()  __asm__ __volatile__ ("sei" ::)
# define cli()  __asm__ __volatile__ ("cli" ::)
# define ret()  __asm__ __volatile__ ("ret" ::)
# define reti() __asm__ __volatile__ ("reti" ::)

/*******************************************************************************************/
/******************************** Interrupt Vector Table ***********************************/
/*******************************************************************************************/
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

/*******************************************************************************************/
/********************************** Timers Registers ***************************************/
/*******************************************************************************************/
#define TWCR    (*((volatile u8*)0x56))
#define TWINT   7
#define TWEA    6
#define TWSTA   5
#define TWSTO   4
#define TWWC    3
#define TWEN    2
#define TWIE    0

#define SPMCR   (*((volatile u8*)0x57))
#define SPMIE   7
#define RWWSB   6
#define RWWSRE  4
#define BLBSET  3
#define PGWRT   2
#define PGERS   1
#define SPMEN   0

#define TIFR    (*((volatile u8*)0x58))
#define OCF2    7
#define TOV2    6
#define ICF1    5
#define OCF1A   4
#define OCF1B   3
#define TOV1    2
#define OCF0    1
#define TOV0    0

#define TIMSK   (*((volatile u8*)0x59))
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

/*******************************************************************************************/
/*********************************** Timer0 Registers **************************************/
/*******************************************************************************************/
#define TCNT0   (*((volatile u8*)0x52))
#define OCR0    (*((volatile u8*)0x5C))

#define TCCR0   (*((volatile u8*)0x53))
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

/*******************************************************************************************/
/*********************************** Timer1 Registers **************************************/
/*******************************************************************************************/
#define ICR1    (*((volatile u16*)0x46))
#define ICR1L   (*((volatile u8*)0x46))
#define ICR1H   (*((volatile u8*)0x47))

#define OCR1B   (*((volatile u16*)0x48))
#define OCR1BL  (*((volatile u8*)0x48))
#define OCR1BH  (*((volatile u8*)0x49))

#define OCR1A   (*((volatile u16*)0x4A))
#define OCR1AL  (*((volatile u8*)0x4A))
#define OCR1AH  (*((volatile u8*)0x4B))

#define TCNT1   (*((volatile u16*)0x4C))
#define TCNT1L  (*((volatile u8*)0x4C))
#define TCNT1H  (*((volatile u8*)0x4D))

#define TCCR1B  (*((volatile u8*)0x4E))
#define ICNC1   7
#define ICES1   6
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0

#define TCCR1A  (*((volatile u8*)0x4F))
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0

#define OSCCAL  (*((volatile u8*)0x51))

/*******************************************************************************************/
/************************************ Timer2 Registers *************************************/
/*******************************************************************************************/
#define OCR2    (*((volatile u8*)0x43))
#define TCNT2   (*((volatile u8*)0x44))

#define TCCR2   (*((volatile u8*)0x45))
#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0

#define ASSR    (*(volatile u8*)0x42)
#define AS2     3
#define TCN2UB  2
#define OCR2UB  1
#define TCR2UB  0

/*******************************************************************************************/
/****************************** Watch Dog Timer Registers **********************************/
/*******************************************************************************************/
#define WDTCR   (*((volatile u8*)0x41))
#define WDTOE   4
#define WDE     3
#define WDP2    2
#define WDP1    1
#define WDP0    0

/*******************************************************************************************/
/************************************ Uart Registers ***************************************/
/*******************************************************************************************/
#define UDR     (*(volatile u8*)0x2C)
#define UCSRA   (*(volatile u8*)0x2B)
#define RXC     7
#define TXC     6
#define UDRE    5
#define FE      4
#define DOR     3
#define UPE     2
#define U2X     1
#define MPCM    0

#define UCSRB   (*(volatile u8*)0x2A)
#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ    2
#define UCSZ2   2
#define RXB8    1
#define TXB8    0

#define UCSRC   (*(volatile u8*)0x40)
#define URSEL   7
#define UMSEL   6
#define UPM1    5
#define UPM0    4
#define USBS    3
#define UCSZ1   2
#define UCSZ0   1
#define UCPOL   0

#define UBRRH   (*(volatile u8*)0x40)
#define UBRRL   (*(volatile u8*)0x29)

/*******************************************************************************************/
/************************************** SPI Registers **************************************/
/*******************************************************************************************/
#define SPCR    (*(volatile u8*)0x2D)
#define SPIE    7
#define SPE     6
#define DORD    5
#define MSTR    4
#define CPOL    3
#define CPHA    2
#define SPR1    1
#define SPR0    0

#define SPSR    (*(volatile u8*)0x2E)
#define SPIF    7
#define WCOL    6
#define SPI2X   0

#define SPDR    (*(volatile u8*)0x2F)

/*******************************************************************************************/
/*********************************** EEPROM Registers **************************************/
/*******************************************************************************************/
#define EECR	(*(volatile u8*)0x3C)
#define EERIE   3
#define EEMWE   2
#define EEWE    1
#define EERE    0

#define EEDR	(*(volatile u8*)0x3D)
#define EEAR	(*(volatile u16*)0x3E)
#define EEARL	(*(volatile u8*)0x3E)
#define EEARH	(*(volatile u8*)0x3F)

/*******************************************************************************************/
/************************************** I2C Registers **************************************/
/*******************************************************************************************/
#define TWBR    (*(volatile u8*)0x20)
#define TWSR    (*(volatile u8*)0x21)
#define TWS7    7
#define TWS6    6
#define TWS5    5
#define TWS4    4
#define TWS3    3
#define TWPS1   1
#define TWPS0   0

#define TWAR    (*(volatile u8*)0x22)
#define TWA6    7
#define TWA5    6
#define TWA4    5
#define TWA3    4
#define TWA2    3
#define TWA1    2
#define TWA0    1
#define TWGCE   0

#define TWDR    (*(volatile u8*)0x23)

/*******************************************************************************************/
/************************************* Memory Map End **************************************/
/*******************************************************************************************/

#endif /* MEMMAP_H_ */