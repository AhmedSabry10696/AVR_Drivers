/**
 * @file Ext_Interrupt.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief External Interrupt Driver
 * @version 0.1
 * @date 24-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Ext_Interrupt.h"

/* pointers to functions take void and return void */
static void (*INT0_Fptr) (void) = NULLPTR;
static void (*INT1_Fptr) (void) = NULLPTR;
static void (*INT2_Fptr) (void) = NULLPTR;

void EXI_Enable(ExInterruptSource_type Interrupt)
{
	switch(Interrupt)
    {
		case EX_INT0:
		    SET_BIT(GICR,INT0);
		    break;
        case EX_INT1:
		    SET_BIT(GICR,INT1);
		    break;
		case EX_INT2:
		    SET_BIT(GICR,INT2);
		    break;
	}
}

void EXI_Disable(ExInterruptSource_type Interrupt)
{
	switch(Interrupt)
    {
		case EX_INT0:
		    CLEAR_BIT(GICR,INT0);
		    break;
		case EX_INT1:
		    CLEAR_BIT(GICR,INT1);
		    break;
		case EX_INT2:
		    CLEAR_BIT(GICR,INT2);
		    break;
	}
}

void EXI_TriggerEdge(ExInterruptSource_type Interrupt,TriggerEdge_type Edge)
{
	switch(Interrupt)
    {
		case EX_INT0:
            switch(Edge)
            {
                case LOW_LEVEL:
                    CLEAR_BIT(MCUCR,ISC00);
                    CLEAR_BIT(MCUCR,ISC01);
                    break;
                case ANY_LOGIC_CHANGE:
                    SET_BIT(MCUCR,ISC00);
                    CLEAR_BIT(MCUCR,ISC01);
                    break;
                case FALLING_EDGE:
                    CLEAR_BIT(MCUCR,ISC00);
                    SET_BIT(MCUCR,ISC01);
                    break;
                case RISING_EDGE:
                    SET_BIT(MCUCR,ISC00);
                    SET_BIT(MCUCR,ISC01);
                    break;
            }
            break;
		case EX_INT1:
            switch(Edge)
            {
                case LOW_LEVEL:
                    CLEAR_BIT(MCUCR,ISC10);
                    CLEAR_BIT(MCUCR,ISC11);
                    break;
                case ANY_LOGIC_CHANGE:
                    SET_BIT(MCUCR,ISC10);
                    CLEAR_BIT(MCUCR,ISC11);
                    break;
                case FALLING_EDGE:
                    CLEAR_BIT(MCUCR,ISC10);
                    SET_BIT(MCUCR,ISC11);
                    break;
                case RISING_EDGE:
                    SET_BIT(MCUCR,ISC10);
                    SET_BIT(MCUCR,ISC11);
                    break;
            }
		    break;
		case EX_INT2:
            switch(Edge)
            {
                case FALLING_EDGE:
                    CLEAR_BIT(MCUCSR,ISC2);
                    break;
                case RISING_EDGE:
                    SET_BIT(MCUCSR,ISC2);
                    break;
                default:
                    CLEAR_BIT(MCUCSR,ISC2);
            }
            break;
	}
}

void EXI_SetCallBack(ExInterruptSource_type Interrupt,void(*LocalPtr)(void))
{
	switch(Interrupt)
    {
		case EX_INT0:
		    INT0_Fptr=LocalPtr;
		    break;
		case EX_INT1:
		    INT1_Fptr=LocalPtr;
		    break;
		case EX_INT2:
		    INT2_Fptr=LocalPtr;
		    break;
	}
}

ISR(INT0_VECT)
{
	if (INT0_Fptr!=NULLPTR)
	{
		INT0_Fptr();
	}
}

ISR(INT1_VECT)
{
	if (INT1_Fptr!=NULLPTR)
	{
		INT1_Fptr();
	}
}

ISR(INT2_VECT)
{
	if (INT2_Fptr!=NULLPTR)
	{
		INT2_Fptr();
	}
}