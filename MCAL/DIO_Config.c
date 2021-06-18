/**
 * @file DIO_Config.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief DIO configuration file
 * @version 0.1
 * @date 25-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "DIO_Interface.h"

const DIO_PinStatus_type PinsStatus[TOTAL_PINS] = 
{
    /* PORTA PINS 0:7*/
    INPULLUP,
    INPULLUP,
    INPULLUP,
    INPULLUP,
    OUTPUT,
    OUTPUT,
    OUTPUT,
    OUTPUT,

    /* PORTB PINS 0:7*/
    OUTPUT,
    OUTPUT,
    OUTPUT,
    OUTPUT,
    OUTPUT,
    OUTPUT,
    OUTPUT,
    OUTPUT,

    /* PORTC PINS 0:7*/    
    OUTPUT,
    OUTPUT,
    OUTPUT,
    OUTPUT,
    OUTPUT,
    OUTPUT,
    OUTPUT,
    OUTPUT,

    /* PORTD PINS 0:7*/
    OUTPUT,
    OUTPUT,
    OUTPUT,
    OUTPUT,
    OUTPUT,
    OUTPUT,
    OUTPUT,
    OUTPUT
};