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

/* pointer to function for Timer overflow interrupt */
static void (*TIMER0_OVF_IntFptr)(void) = NULLPTR;

/* pointer to function for Timer compare match interrupt */
static void (*TIMER0_COM_IntFptr)(void) = NULLPTR;

void TIMER0_Init(TIMER0_Mode_Type mode,TIMER0_Scaler_Type scaler,TIMER0_OC0_Type oc0)
{
    switch (mode)
    {
        case TIMER0_Normal:
            switch (oc0)
            {
                case OC0_Disconnected:
                    TCCR0 = 0x80;
                    break;
                case OC0_Toggle_OnCompMatch:
                    TCCR0 = 0x90;
                    break;
                case OC0_Clear_OnCompMatch:
                    TCCR0 = 0xA0;
                    break;
                case OC0_Set_OnCompMatch:
                    TCCR0 = 0xB0;
                    break;
            }
            break;
        case TIMER0_PWM_PHASE_CORRECT:
            break;
        case TIMER0_CTC:
            switch (oc0)
            {
                case OC0_Disconnected:
                    TCCR0 = 0x88;
                    break;
                case OC0_Toggle_OnCompMatch:
                    TCCR0 = 0x98;
                    break;
                case OC0_Clear_OnCompMatch:
                    TCCR0 = 0xA8;
                    break;
                case OC0_Set_OnCompMatch:
                    TCCR0 = 0xB8;
                    break;
            }
            break;
        case TIMER0_FAST_PWM:
            break;
    }

    TCCR0 |= scaler;
}

void TIMER0_OvfIntEnable(void)
{
    SET_BIT(TIMSK,TOIE0);
}

void TIMER0_OvfIntDisable(void)
{
    CLEAR_BIT(TIMSK,TOIE0);
}

void TIMER0_ComIntEnable(void)
{
    SET_BIT(TIMSK,OCIE0);
}

void TIMER0_ComIntDisable(void)
{
    CLEAR_BIT(TIMSK,OCIE0);
}

void TIMER0_OvfIntSetCallBack(void(*LocalPtr)(void))
{
    TIMER0_OVF_IntFptr = LocalPtr;
}

void TIMER0_ComIntSetCallBack(void(*LocalPtr)(void))
{
    TIMER0_COM_IntFptr = LocalPtr;
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