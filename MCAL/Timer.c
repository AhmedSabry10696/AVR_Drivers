/**
 * @file Timer.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Timer driver 
 * @version 0.1
 * @date 28-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Timer.h"

static void (*TIMER0_OVF_IntFptr)(void) = NULLPTR;
static void (*TIMER0_COM_IntFptr)(void) = NULLPTR;

static void (*Timer1_OVF_IntFptr)(void) = NULLPTR;
static void (*Timer1_OCA_IntFptr)(void) = NULLPTR;
static void (*Timer1_OCB_IntFptr)(void) = NULLPTR;
static void (*Timer1_ICU_IntFptr)(void) = NULLPTR;

void Timer0_Init(TIMER0_Mode_type mode,TIMER0_Scaler_type scaler)
{
	switch (mode)
	{
		case TIMER0_NORMAL:
            CLEAR_BIT(TCCR0,WGM00);
            CLEAR_BIT(TCCR0,WGM01);
            break;
		case TIMER0_PWM_PHASE_CORRECT:
            SET_BIT(TCCR0,WGM00);
            CLEAR_BIT(TCCR0,WGM01);
            break;
		case TIMER0_CTC:
            CLEAR_BIT(TCCR0,WGM00);
            SET_BIT(TCCR0,WGM01);
            break;
		case TIMER0_FAST_PWM:
            SET_BIT(TCCR0,WGM00);
            SET_BIT(TCCR0,WGM01);
            break;
	}

    /* clear LSB three bits for scaler */
	TCCR0 &= 0XF8;
	
    /* add scaler to TCCR0 register */
    TCCR0 |= scaler;
}
void Timer0_OC0_Mode(TIMER0_OC0_type mode)
{
	switch (mode)
	{
		case OC0_DISCONNECTED:
            CLEAR_BIT(TCCR0,COM00);
            CLEAR_BIT(TCCR0,COM01);
            break;
		case OC0_TOGGLE:
            SET_BIT(TCCR0,COM00);
            CLEAR_BIT(TCCR0,COM01);
            break;
		case OC0_NON_INVERTING:
            CLEAR_BIT(TCCR0,COM00);
            SET_BIT(TCCR0,COM01);
            break;
		case OC0_INVERTING:
            SET_BIT(TCCR0,COM00);
            SET_BIT(TCCR0,COM01);
            break;
	}
}

void Timer0_Set(u8 time)
{
    TCNT0 = time;
}
u8   Timer0_Get(void)
{
    return TCNT0;
}
void Timer0_OCR_Set(u8 time)
{
    OCR0 = time;
}

void Timer0_OVF_IntEnable(void)
{
    SET_BIT(TIMSK,TOIE0);
}
void Timer0_OVF_IntDisable(void)
{
    CLEAR_BIT(TIMSK,TOIE0);
}
void Timer0_OC_IntEnable(void)
{
    SET_BIT(TIMSK,OCIE0);
}
void Timer0_OC_IntDisable(void)
{
    CLEAR_BIT(TIMSK,OCIE0);
}

void Timer0_OVF_IntSetCallBack(void(*LocalFptr)(void))
{
    TIMER0_OVF_IntFptr = LocalFptr;
}
void Timer0_OC_IntSetCallBack(void(*LocalFptr)(void))
{
    TIMER0_COM_IntFptr = LocalFptr;
}

void Timer1_Init(TIMER1_Mode_type mode,TIMER1_Scaler_type scaler)
{
    switch (mode)
	{
		case TIMER1_NORMAL_MODE:
            CLEAR_BIT(TCCR1A,WGM10);
            CLEAR_BIT(TCCR1A,WGM11);
            CLEAR_BIT(TCCR1B,WGM12);
            CLEAR_BIT(TCCR1B,WGM13);
            break;
		case TIMER1_CTC_ICR_TOP_MODE:
            CLEAR_BIT(TCCR1A,WGM10);
            CLEAR_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13);
            break;
		case TIMER1_CTC_OCRA_TOP_MODE:
            CLEAR_BIT(TCCR1A,WGM10);
            CLEAR_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            CLEAR_BIT(TCCR1B,WGM13);
            break;
		case TIMER1_FASTPWM_ICR_TOP_MODE:
            CLEAR_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13);
            break;
		case TIMER1_FASTPWM_OCRA_TOP_MODE:
            SET_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13);
            break;
	}

    /* clear LSB three bits for scaler */
	TCCR1B &= 0XF8;

    /* add scaler to TCCR1B register */
	TCCR1B|=scaler;
}
void Timer1_OCRA_Mode(TIMER1_OC1A_type oc1a_mode)
{
	switch (oc1a_mode)
	{
		case OCRA_DISCONNECTED:
            CLEAR_BIT(TCCR1A,COM1A0);
            CLEAR_BIT(TCCR1A,COM1A1);
            break;
		case OCRA_TOGGLE:
            SET_BIT(TCCR1A,COM1A0);
            CLEAR_BIT(TCCR1A,COM1A1);
            break;
		case OCRA_NON_INVERTING:
            CLEAR_BIT(TCCR1A,COM1A0);
            SET_BIT(TCCR1A,COM1A1);
            break;
		case OCRA_INVERTING:
            SET_BIT(TCCR1A,COM1A0);
            SET_BIT(TCCR1A,COM1A1);
            break;
	}
}
void Timer1_OCRB_Mode(TIMER1_OC1B_type oc1b_mode)
{
    switch (oc1b_mode)
	{
		case OCRB_DISCONNECTED:
            CLEAR_BIT(TCCR1A,COM1B0);
            CLEAR_BIT(TCCR1A,COM1B1);
            break;
		case OCRB_TOGGLE:
            SET_BIT(TCCR1A,COM1B0);
            CLEAR_BIT(TCCR1A,COM1B1);
            break;
		case OCRB_NON_INVERTING:
            CLEAR_BIT(TCCR1A,COM1B0);
            SET_BIT(TCCR1A,COM1B1);
            break;
		case OCRB_INVERTING:
            SET_BIT(TCCR1A,COM1B0);
            SET_BIT(TCCR1A,COM1B1);
            break;
	}
}
void Timer1_InputCaptureEdge(TIMER1_ICU_Edge_type edge)
{
    if(edge == RISING)
        SET_BIT(TCCR1B,ICES1);
	
    else if(edge == FALLING)
        CLEAR_BIT(TCCR1B,ICES1);
}

void Timer1_Set(u16 time)
{
    TCNT1 = time;
}
u16  Timer1_Get(void)
{
    return TCNT1;
}
void Timer1_OCRA_Set(u16 time)
{
    OCR1A = time;
}
void Timer1_OCRB_Set(u16 time)
{
    OCR1B = time;
}
void Timer1_ICR_Set(u16 time)
{
    ICR1 = time;
}
u16 Timer1_ICR_Get(void)
{
    return ICR1;
}

void Timer1_OVF_IntEnable(void)
{
    SET_BIT(TIMSK,TOIE1);
}
void Timer1_OVF_IntDisable(void)
{
    CLEAR_BIT(TIMSK,TOIE1);
}
void Timer1_OCA_IntEnable(void)
{
    SET_BIT(TIMSK,OCIE1A);
}
void Timer1_OCA_IntDisable(void)
{
    CLEAR_BIT(TIMSK,OCIE1A);
}
void Timer1_OCB_IntEnable(void)
{
    SET_BIT(TIMSK,OCIE1B);
}
void Timer1_OCB_IntDisable(void)
{
    CLEAR_BIT(TIMSK,OCIE1B);
}
void Timer1_ICU_IntEnable(void)
{
    SET_BIT(TIMSK,TICIE1);
}
void Timer1_ICU_IntDisable(void)
{
    CLEAR_BIT(TIMSK,TICIE1);
}

void Timer1_OVF_IntSetCallBack(void(*LocalFptr)(void))
{
    Timer1_OVF_IntFptr = LocalFptr;
}
void Timer1_OCA_IntSetCallBack(void(*LocalFptr)(void))
{
    Timer1_OCA_IntFptr = LocalFptr;
}
void Timer1_OCB_IntSetCallBack(void(*LocalFptr)(void))
{
    Timer1_OCB_IntFptr = LocalFptr;
}
void Timer1_ICU_IntSetCallBack(void(*LocalFptr)(void))
{
    Timer1_ICU_IntFptr = LocalFptr;
}

ISR(TIMER0_OVF_VECT)
{
	if (TIMER0_OVF_IntFptr != NULLPTR)
	{
		TIMER0_OVF_IntFptr();
	}
}
ISR(TIMER0_COMP_VECT)
{
	if (TIMER0_COM_IntFptr != NULLPTR)
	{
		TIMER0_COM_IntFptr();
	}
}
ISR(TIMER1_OVF_VECT)
{
	if(Timer1_OVF_IntFptr!=NULLPTR)
	{
		Timer1_OVF_IntFptr();
	}
}
ISR(TIMER1_COMPA_VECT)
{
	if(Timer1_OCA_IntFptr!=NULLPTR)
	{
		Timer1_OCA_IntFptr();
	}
}
ISR(TIMER1_COMPB_VECT)
{
	if(Timer1_OCB_IntFptr!=NULLPTR)
	{
		Timer1_OCB_IntFptr();
	}
}
ISR(TIMER1_CAPT_VECT)
{
	if(Timer1_ICU_IntFptr!=NULLPTR)
	{
		Timer1_ICU_IntFptr();
	}
}
