/**
 * @file Timer_Services.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Timer services functions implementation
 * @version 0.1
 * @date 03-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Timer_Services.h"

/* for input capture unit and timer1 overflow */
static volatile u32 t1, t2, t3;
static volatile u8 flag = 0, c = 0;

/* for Timer1_SetIntTime_s function and Timer_func */
static u32 NofOverFlow = 0;
static void (*fptr_timer)(void);

void PWM_Init(void)
{
    Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE, TIMER1_SCALER_8);
    Timer1_OCRA_Mode(OCRA_NON_INVERTING);
    Timer1_OCRB_Mode(OCRB_DISCONNECTED);
}
void PWM_Duty(const u16 duty)
{
    if (duty <= 100)
    {
        u16 top = Timer1_ICR_Get();
        u16 Ton = ((u32)duty * (top + 1)) / 100;
        if (Ton > 1)
        {
            Timer1_OCRA_Set(Ton - 1);
        }
        else
        {
            Timer1_OCRA_Set(0);
        }
    }
}
void PWM_Freq_HZ(const u16 freq)
{
    if (freq != 0)
    {
        /* calculate period T = 1000000/f us */
        u16 Ttotal = (u32)1000000 / freq;

        if (Ttotal >= 1)
        {
            /* update top to period T */
            Timer1_ICR_Set(Ttotal - 1);
        }
        else
        {
            Timer1_ICR_Set(0);
        }
    }
}
void PWM_Freq_KHZ(const u16 freq)
{
    if (freq != 0)
    {
        /* calculate period T= 1000/f us */
        u16 Ttotal = 1000 / freq;

        if (Ttotal >= 1)
        {
            /* update top value to T */
            Timer1_ICR_Set(Ttotal - 1);
        }
        else
        {
            Timer1_ICR_Set(0);
        }
    }
}

static void Timer_func(void)
{
    static u32 c = 0;
    c++;
    if (c == NofOverFlow)
    {
        c = 0;
        fptr_timer();
    }
}
void Timer1_SetIntTime_us(const u16 time, void (*LocalFptr)(void))
{
    Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE, TIMER1_SCALER_8);
    Timer1_OCRA_Mode(OCRA_DISCONNECTED);
    Timer1_OCRB_Mode(OCRB_DISCONNECTED);

    Timer1_OCRA_Set(time - 1);

    Timer1_OCA_IntSetCallBack(LocalFptr);
    Timer1_OCA_IntEnable();
}
void Timer1_SetIntTime_ms(const u16 time, void (*LocalFptr)(void))
{
    Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE, TIMER1_SCALER_8);
    Timer1_OCRA_Mode(OCRA_DISCONNECTED);
    Timer1_OCRB_Mode(OCRB_DISCONNECTED);

    Timer1_OCRA_Set((time * 1000) - 1);

    Timer1_OCA_IntSetCallBack(LocalFptr);
    Timer1_OCA_IntEnable();
}
void Timer1_SetIntTime_s(const u16 time, void (*LocalFptr)(void))
{
    Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE, TIMER1_SCALER_8);

    /* interrupt every 1ms */
    Timer1_OCRA_Set(999);

    /* calculate number of overflows and set global var */
    NofOverFlow = time * 1000;

    /* set fptr_timer with the address of the function to call as specified time */
    fptr_timer = LocalFptr;

    /* set callback of compare match with another Timer_func to reach to NofOverFlow */
    Timer1_OCA_IntSetCallBack(Timer_func);
    Timer1_OCA_IntEnable();
}

static void Func_OV(void)
{
    c++;
}
static void Func_ICU(void)
{
    if (0 == flag)
    {
        t1 = Timer1_ICR_Get() + ((u32)c * 65536);
        Timer1_InputCaptureEdge(FALLING);
        flag = 1;
    }
    else if (1 == flag)
    {
        t2 = Timer1_ICR_Get() + ((u32)c * 65536);
        Timer1_InputCaptureEdge(RISING);
        flag = 2;
    }
    else if (2 == flag)
    {
        t3 = Timer1_ICR_Get() + ((u32)c * 65536);
        Timer1_ICU_IntDisable();
        flag = 3;
    }
}
void PWM_Measure(u32 *Pfreq, u8 *Pduty)
{
    u32 Ton, Toff;

    Timer1_Set(0);
    Timer1_ICU_IntSetCallBack(Func_ICU);
    Timer1_OVF_IntSetCallBack(Func_OV);
    Timer1_InputCaptureEdge(RISING);
    Timer1_ICU_IntEnable();
    Timer1_OVF_IntEnable();
    flag = 0;

    while (flag < 3)
        ;

    Ton = t2 - t1;
    Toff = t3 - t2;

    *Pduty = (Ton * 100) / (Ton + Toff);
    *Pfreq = (u32)1000000 / (Toff + Ton);
}
void PMW_StartMeasure(void)
{
    if (0 == flag)
    {
        Timer1_Set(0);
        Timer1_ICU_IntSetCallBack(Func_ICU);
        Timer1_OVF_IntSetCallBack(Func_OV);
        Timer1_InputCaptureEdge(RISING);
        Timer1_ICU_IntEnable();
        Timer1_OVF_IntEnable();
    }
}
u8 PWM_GetRead(u32 *Pfreq, u8 *Pduty)
{
    u32 Ton, Toff;

    if (3 == flag)
    {
        Ton = t2 - t1;
        Toff = t3 - t2;

        *Pduty = (Ton * 100) / (Ton + Toff);
        *Pfreq = (u32)1000000 / (Toff + Ton);
        flag = 0;
        return 1;
    }
    return 0;
}