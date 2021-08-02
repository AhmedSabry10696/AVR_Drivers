/**
 * @file timer.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Timer driver 
 * @version 0.1
 * @date 28-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "timer.h"

static void (*timer0_ovf_fPtr)(void) = NULLPTR;
static void (*timer0_com_fPtr)(void) = NULLPTR;

static void (*timer1_ovf_fPtr)(void) = NULLPTR;
static void (*timer1_oca_fPtr)(void) = NULLPTR;
static void (*timer1_ocb_fPtr)(void) = NULLPTR;
static void (*timer1_icu_fPtr)(void) = NULLPTR;

void TIMER0_init(Timer0Mode_type mode, Timer0Scaler_type scaler)
{
    switch (mode)
    {
    case TIMER0_NORMAL:
        CLR_BIT(TCCR0, WGM00);
        CLR_BIT(TCCR0, WGM01);
        break;
    case TIMER0_PWM_PHASE_CORRECT:
        SET_BIT(TCCR0, WGM00);
        CLR_BIT(TCCR0, WGM01);
        break;
    case TIMER0_CTC:
        CLR_BIT(TCCR0, WGM00);
        SET_BIT(TCCR0, WGM01);
        break;
    case TIMER0_FAST_PWM:
        SET_BIT(TCCR0, WGM00);
        SET_BIT(TCCR0, WGM01);
        break;
    }

    /* clear LSB three bits for scaler */
    TCCR0 &= 0XF8;

    /* add scaler to TCCR0 register */
    TCCR0 |= scaler;
}

void TIMER0_OC0_mode(Timer0_oc0_type mode)
{
    switch (mode)
    {
    case OC0_DISCONNECTED:
        CLR_BIT(TCCR0, COM00);
        CLR_BIT(TCCR0, COM01);
        break;
    case OC0_TOGGLE:
        SET_BIT(TCCR0, COM00);
        CLR_BIT(TCCR0, COM01);
        break;
    case OC0_NON_INVERTING:
        CLR_BIT(TCCR0, COM00);
        SET_BIT(TCCR0, COM01);
        break;
    case OC0_INVERTING:
        SET_BIT(TCCR0, COM00);
        SET_BIT(TCCR0, COM01);
        break;
    }
}

void TIMER0_set(const u8 time)
{
    TCNT0 = time;
}

u8 TIMER0_get(void)
{
    return TCNT0;
}

void TIMER0_OCR_set(const u8 time)
{
    OCR0 = time;
}

void TIMER0_OVF_intEnable(void)
{
    SET_BIT(TIMSK, TOIE0);
}

void TIMER0_OVF_intDisable(void)
{
    CLR_BIT(TIMSK, TOIE0);
}

void TIMER0_OC_intEnable(void)
{
    SET_BIT(TIMSK, OCIE0);
}

void TIMER0_OC_intDisable(void)
{
    CLR_BIT(TIMSK, OCIE0);
}

void TIMER0_OVF_intSetCallBack(void (*localFptr)(void))
{
    timer0_ovf_fPtr = localFptr;
}

void TIMER0_OC_intSetCallBack(void (*localFptr)(void))
{
    timer0_com_fPtr = localFptr;
}

void TIMER1_init(Timer1Mode_type mode, Timer1Scaler_type scaler)
{
    switch (mode)
    {
    case TIMER1_NORMAL_MODE:
        CLR_BIT(TCCR1A, WGM10);
        CLR_BIT(TCCR1A, WGM11);
        CLR_BIT(TCCR1B, WGM12);
        CLR_BIT(TCCR1B, WGM13);
        break;
    case TIMER1_CTC_ICR_TOP_MODE:
        CLR_BIT(TCCR1A, WGM10);
        CLR_BIT(TCCR1A, WGM11);
        SET_BIT(TCCR1B, WGM12);
        SET_BIT(TCCR1B, WGM13);
        break;
    case TIMER1_CTC_OCRA_TOP_MODE:
        CLR_BIT(TCCR1A, WGM10);
        CLR_BIT(TCCR1A, WGM11);
        SET_BIT(TCCR1B, WGM12);
        CLR_BIT(TCCR1B, WGM13);
        break;
    case TIMER1_FASTPWM_ICR_TOP_MODE:
        CLR_BIT(TCCR1A, WGM10);
        SET_BIT(TCCR1A, WGM11);
        SET_BIT(TCCR1B, WGM12);
        SET_BIT(TCCR1B, WGM13);
        break;
    case TIMER1_FASTPWM_OCRA_TOP_MODE:
        SET_BIT(TCCR1A, WGM10);
        SET_BIT(TCCR1A, WGM11);
        SET_BIT(TCCR1B, WGM12);
        SET_BIT(TCCR1B, WGM13);
        break;
    }

    /* clear LSB three bits for scaler */
    TCCR1B &= 0XF8;

    /* add scaler to TCCR1B register */
    TCCR1B |= scaler;
}

void TIMER1_OCRA_mode(Timer1_oc1a_type oc1a_mode)
{
    switch (oc1a_mode)
    {
    case OCRA_DISCONNECTED:
        CLR_BIT(TCCR1A, COM1A0);
        CLR_BIT(TCCR1A, COM1A1);
        break;
    case OCRA_TOGGLE:
        SET_BIT(TCCR1A, COM1A0);
        CLR_BIT(TCCR1A, COM1A1);
        break;
    case OCRA_NON_INVERTING:
        CLR_BIT(TCCR1A, COM1A0);
        SET_BIT(TCCR1A, COM1A1);
        break;
    case OCRA_INVERTING:
        SET_BIT(TCCR1A, COM1A0);
        SET_BIT(TCCR1A, COM1A1);
        break;
    }
}

void TIMER1_OCRB_mode(Timer1_oc1b_type oc1b_mode)
{
    switch (oc1b_mode)
    {
    case OCRB_DISCONNECTED:
        CLR_BIT(TCCR1A, COM1B0);
        CLR_BIT(TCCR1A, COM1B1);
        break;
    case OCRB_TOGGLE:
        SET_BIT(TCCR1A, COM1B0);
        CLR_BIT(TCCR1A, COM1B1);
        break;
    case OCRB_NON_INVERTING:
        CLR_BIT(TCCR1A, COM1B0);
        SET_BIT(TCCR1A, COM1B1);
        break;
    case OCRB_INVERTING:
        SET_BIT(TCCR1A, COM1B0);
        SET_BIT(TCCR1A, COM1B1);
        break;
    }
}

void TIMER1_inputCaptureEdge(Timer1_icuEdge_type edge)
{
    if (edge == RISING)
        SET_BIT(TCCR1B, ICES1);

    else if (edge == FALLING)
        CLR_BIT(TCCR1B, ICES1);
}

void TIMER1_set(const u16 time)
{
    TCNT1 = time;
}

u16 TIMER1_get(void)
{
    return TCNT1;
}

void TIMER1_OCRA_set(const u16 time)
{
    OCR1A = time;
}

void TIMER1_OCRB_set(const u16 time)
{
    OCR1B = time;
}

void TIMER1_ICR_set(const u16 time)
{
    ICR1 = time;
}

u16 TIMER1_ICR_get(void)
{
    return ICR1;
}

void TIMER1_OVF_intEnable(void)
{
    SET_BIT(TIMSK, TOIE1);
}

void TIMER1_OVF_intDisable(void)
{
    CLR_BIT(TIMSK, TOIE1);
}

void TIMER1_OCA_intEnable(void)
{
    SET_BIT(TIMSK, OCIE1A);
}

void TIMER1_OCA_intDisable(void)
{
    CLR_BIT(TIMSK, OCIE1A);
}

void TIMER1_OCB_intEnable(void)
{
    SET_BIT(TIMSK, OCIE1B);
}

void TIMER1_OCB_intDisable(void)
{
    CLR_BIT(TIMSK, OCIE1B);
}

void TIMER1_ICU_intEnable(void)
{
    SET_BIT(TIMSK, TICIE1);
}

void TIMER1_ICU_intDisable(void)
{
    CLR_BIT(TIMSK, TICIE1);
}

void TIMER1_OVF_intSetCallBack(void (*localFptr)(void))
{
    timer1_ovf_fPtr = localFptr;
}

void TIMER1_OCA_intSetCallBack(void (*localFptr)(void))
{
    timer1_oca_fPtr = localFptr;
}

void TIMER1_OCB_intSetCallBack(void (*localFptr)(void))
{
    timer1_ocb_fPtr = localFptr;
}

void TIMER1_ICU_intSetCallBack(void (*localFptr)(void))
{
    timer1_icu_fPtr = localFptr;
}

ISR(TIMER0_OVF_VECT)
{
    if (timer0_ovf_fPtr != NULLPTR)
    {
        timer0_ovf_fPtr();
    }
}

ISR(TIMER0_COMP_VECT)
{
    if (timer0_com_fPtr != NULLPTR)
    {
        timer0_com_fPtr();
    }
}

ISR(TIMER1_OVF_VECT)
{
    if (timer1_ovf_fPtr != NULLPTR)
    {
        timer1_ovf_fPtr();
    }
}

ISR(TIMER1_COMPA_VECT)
{
    if (timer1_oca_fPtr != NULLPTR)
    {
        timer1_oca_fPtr();
    }
}

ISR(TIMER1_COMPB_VECT)
{
    if (timer1_ocb_fPtr != NULLPTR)
    {
        timer1_ocb_fPtr();
    }
}

ISR(TIMER1_CAPT_VECT)
{
    if (timer1_icu_fPtr != NULLPTR)
    {
        timer1_icu_fPtr();
    }
}
