/**
 * @file timer_services.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Timer services functions implementation
 * @version 0.1
 * @date 03-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "timer_services.h"

/* for input capture unit and timer1 overflow */
static volatile u32 t1, t2, t3;
static volatile u8 flag = 0, c = 0;

/* for Timer1_SetIntTime_s function and Timer_func */
static u32 overflow_count = 0;
static void (*timer_fPtr)(void);

void PWM_init(void)
{
    TIMER1_init(TIMER1_FASTPWM_ICR_TOP_MODE, TIMER1_SCALER_8);
    TIMER1_OCRA_mode(OCRA_NON_INVERTING);
    TIMER1_OCRB_mode(OCRB_DISCONNECTED);
}

void PWM_duty(const u16 duty)
{
    if (duty <= 100)
    {
        u16 top = TIMER1_ICR_get();
        u16 Ton = ((u32)duty * (top + 1)) / 100;
        if (Ton > 1)
        {
            TIMER1_OCRA_set(Ton - 1);
        }
        else
        {
            TIMER1_OCRA_set(0);
        }
    }
}

void PWM_freq_HZ(const u16 freq)
{
    if (freq != 0)
    {
        /* calculate period T = 1000000/f us */
        u16 Ttotal = (u32)1000000 / freq;

        if (Ttotal >= 1)
        {
            /* update top to period T */
            TIMER1_ICR_set(Ttotal - 1);
        }
        else
        {
            TIMER1_ICR_set(0);
        }
    }
}

void PWM_freq_KHZ(const u16 freq)
{
    if (freq != 0)
    {
        /* calculate period T= 1000/f us */
        u16 Ttotal = 1000 / freq;

        if (Ttotal >= 1)
        {
            /* update top value to T */
            TIMER1_ICR_set(Ttotal - 1);
        }
        else
        {
            TIMER1_ICR_set(0);
        }
    }
}

static void TIMER_func(void)
{
    static u32 c = 0;
    c++;
    if (c == overflow_count)
    {
        c = 0;
        timer_fPtr();
    }
}

void TIMER1_setIntTime_us(const u16 time, void (*localFptr)(void))
{
    TIMER1_init(TIMER1_CTC_OCRA_TOP_MODE, TIMER1_SCALER_8);
    TIMER1_OCRA_mode(OCRA_DISCONNECTED);
    TIMER1_OCRB_mode(OCRB_DISCONNECTED);

    TIMER1_OCRA_set(time - 1);

    TIMER1_OCA_intSetCallBack(localFptr);
    TIMER1_OCA_intEnable();
}

void Timer1_setIntTime_ms(const u16 time, void (*localFptr)(void))
{
    TIMER1_init(TIMER1_CTC_OCRA_TOP_MODE, TIMER1_SCALER_8);
    TIMER1_OCRA_mode(OCRA_DISCONNECTED);
    TIMER1_OCRB_mode(OCRB_DISCONNECTED);

    TIMER1_OCRA_set((time * 1000) - 1);

    TIMER1_OCA_intSetCallBack(localFptr);
    TIMER1_OCA_intEnable();
}

void Timer1_setIntTime_s(const u16 time, void (*localFptr)(void))
{
    TIMER1_init(TIMER1_CTC_OCRA_TOP_MODE, TIMER1_SCALER_8);

    /* interrupt every 1ms */
    TIMER1_OCRA_set(999);

    /* calculate number of overflows and set global var */
    overflow_count = time * 1000;

    /* set timer_fPtr with the address of the function to call as specified time */
    timer_fPtr = localFptr;

    /* set callback of compare match with another Timer_func to reach to overflow_count */
    TIMER1_OCA_intSetCallBack(TIMER_func);
    TIMER1_OCA_intEnable();
}

static void TIMER_ovf_func(void)
{
    c++;
}

static void TIMER_icu_func(void)
{
    if (0 == flag)
    {
        t1 = TIMER1_ICR_get() + ((u32)c * 65536);
        TIMER1_inputCaptureEdge(FALLING);
        flag = 1;
    }
    else if (1 == flag)
    {
        t2 = TIMER1_ICR_get() + ((u32)c * 65536);
        TIMER1_inputCaptureEdge(RISING);
        flag = 2;
    }
    else if (2 == flag)
    {
        t3 = TIMER1_ICR_get() + ((u32)c * 65536);
        TIMER1_ICU_intDisable();
        flag = 3;
    }
}

void PWM_measure(u32 *freq_ptr, u8 *duty_ptr)
{
    u32 Ton, Toff;

    TIMER1_set(0);
    TIMER1_ICU_intSetCallBack(TIMER_icu_func);
    TIMER1_OVF_intSetCallBack(TIMER_ovf_func);
    TIMER1_inputCaptureEdge(RISING);
    TIMER1_ICU_intEnable();
    TIMER1_OVF_intEnable();
    flag = 0;

    while (flag < 3)
        ;

    Ton = t2 - t1;
    Toff = t3 - t2;

    *duty_ptr = (Ton * 100) / (Ton + Toff);
    *freq_ptr = (u32)1000000 / (Toff + Ton);
}

void PMW_startMeasure(void)
{
    if (0 == flag)
    {
        TIMER1_set(0);
        TIMER1_ICU_intSetCallBack(TIMER_icu_func);
        TIMER1_OVF_intSetCallBack(TIMER_ovf_func);
        TIMER1_inputCaptureEdge(RISING);
        TIMER1_ICU_intEnable();
        TIMER1_OVF_intEnable();
    }
}

u8 PWM_getRead(u32 *freq_ptr, u8 *duty_ptr)
{
    u32 Ton, Toff;

    if (3 == flag)
    {
        Ton = t2 - t1;
        Toff = t3 - t2;

        *duty_ptr = (Ton * 100) / (Ton + Toff);
        *freq_ptr = (u32)1000000 / (Toff + Ton);
        flag = 0;
        return 1;
    }
    return 0;
}