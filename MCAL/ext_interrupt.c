/**
 * @file ext_interrupt.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief External Interrupt Driver
 * @version 0.1
 * @date 24-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ext_interrupt.h"

/* pointers to functions take void and return void */
static void (*int0_fPtr)(void) = NULLPTR;
static void (*int1_fPtr)(void) = NULLPTR;
static void (*int2_fPtr)(void) = NULLPTR;

void EXI_enable(ExInterruptSource_type interrupt)
{
    switch (interrupt)
    {
    case EX_INT0:
        SET_BIT(GICR, INT0);
        break;
    case EX_INT1:
        SET_BIT(GICR, INT1);
        break;
    case EX_INT2:
        SET_BIT(GICR, INT2);
        break;
    }
}

void EXI_disable(ExInterruptSource_type interrupt)
{
    switch (interrupt)
    {
    case EX_INT0:
        CLR_BIT(GICR, INT0);
        break;
    case EX_INT1:
        CLR_BIT(GICR, INT1);
        break;
    case EX_INT2:
        CLR_BIT(GICR, INT2);
        break;
    }
}

void EXI_triggerEdge(ExInterruptSource_type interrupt, TriggerEdge_type edge)
{
    switch (interrupt)
    {
    case EX_INT0:
        switch (edge)
        {
        case LOW_LEVEL:
            CLR_BIT(MCUCR, ISC00);
            CLR_BIT(MCUCR, ISC01);
            break;
        case ANY_LOGIC_CHANGE:
            SET_BIT(MCUCR, ISC00);
            CLR_BIT(MCUCR, ISC01);
            break;
        case FALLING_EDGE:
            CLR_BIT(MCUCR, ISC00);
            SET_BIT(MCUCR, ISC01);
            break;
        case RISING_EDGE:
            SET_BIT(MCUCR, ISC00);
            SET_BIT(MCUCR, ISC01);
            break;
        }
        break;

    case EX_INT1:
        switch (edge)
        {
        case LOW_LEVEL:
            CLR_BIT(MCUCR, ISC10);
            CLR_BIT(MCUCR, ISC11);
            break;
        case ANY_LOGIC_CHANGE:
            SET_BIT(MCUCR, ISC10);
            CLR_BIT(MCUCR, ISC11);
            break;
        case FALLING_EDGE:
            CLR_BIT(MCUCR, ISC10);
            SET_BIT(MCUCR, ISC11);
            break;
        case RISING_EDGE:
            SET_BIT(MCUCR, ISC10);
            SET_BIT(MCUCR, ISC11);
            break;
        }
        break;
    
    case EX_INT2:
        switch (edge)
        {
        case FALLING_EDGE:
            CLR_BIT(MCUCSR, ISC2);
            break;
        case RISING_EDGE:
            SET_BIT(MCUCSR, ISC2);
            break;
        default:
            CLR_BIT(MCUCSR, ISC2);
        }
        break;
    }
}

void EXI_setCallBack(ExInterruptSource_type interrupt, void (*localPtr)(void))
{
    switch (interrupt)
    {
    case EX_INT0:
        int0_fPtr = localPtr;
        break;
    case EX_INT1:
        int1_fPtr = localPtr;
        break;
    case EX_INT2:
        int2_fPtr = localPtr;
        break;
    }
}

ISR(INT0_VECT)
{
    if (int0_fPtr != NULLPTR)
    {
        int0_fPtr();
    }
}

ISR(INT1_VECT)
{
    if (int1_fPtr != NULLPTR)
    {
        int1_fPtr();
    }
}

ISR(INT2_VECT)
{
    if (int2_fPtr != NULLPTR)
    {
        int2_fPtr();
    }
}
