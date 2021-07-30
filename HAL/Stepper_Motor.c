/**
 * @file Stepper_Motor.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Stepper motor driver
 * @version 0.1
 * @date 26-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Stepper_Motor.h"

void Stepper_BiPolarFull_CW(void)
{
    DIO_WritePin(COIL1A, HIGH);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, HIGH);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, HIGH);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, HIGH);
    _delay_ms(DELAY);
}

void Stepper_BiPolarFull_CCW(void)
{
    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, HIGH);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, HIGH);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, HIGH);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, HIGH);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);
}

void Stepper_UniPolarFull_CW(void)
{
    DIO_WritePin(COIL1A, HIGH);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, HIGH);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, HIGH);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, HIGH);
    _delay_ms(DELAY);
}

void Stepper_UniPolarFull_CCW(void)
{
    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, HIGH);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, HIGH);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, HIGH);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, HIGH);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);
}

void Stepper_UniPolarHalf_CW(void)
{
    DIO_WritePin(COIL1A, HIGH);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, HIGH);
    DIO_WritePin(COIL1B, HIGH);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, HIGH);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, HIGH);
    DIO_WritePin(COIL2A, HIGH);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, HIGH);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, HIGH);
    DIO_WritePin(COIL2B, HIGH);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, HIGH);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, HIGH);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, HIGH);
    _delay_ms(DELAY);
}

void Stepper_UniPolarHalf_CCW(void)
{
    DIO_WritePin(COIL1A, HIGH);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, HIGH);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, HIGH);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, HIGH);
    DIO_WritePin(COIL2B, HIGH);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, HIGH);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, HIGH);
    DIO_WritePin(COIL2A, HIGH);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, LOW);
    DIO_WritePin(COIL1B, HIGH);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, HIGH);
    DIO_WritePin(COIL1B, HIGH);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_WritePin(COIL1A, HIGH);
    DIO_WritePin(COIL1B, LOW);
    DIO_WritePin(COIL2A, LOW);
    DIO_WritePin(COIL2B, LOW);
    _delay_ms(DELAY);
}