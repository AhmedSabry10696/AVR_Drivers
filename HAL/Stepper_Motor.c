/**
 * @file stepper_motor.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Stepper motor driver
 * @version 0.1
 * @date 26-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "stepper_motor.h"

void STEPPER_biPolarFull_cw(void)
{
    DIO_writePin(COIL1A, HIGH);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, HIGH);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, HIGH);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, HIGH);
    _delay_ms(DELAY);
}

void STEPPER_biPolarFull_ccw(void)
{
    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, HIGH);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, HIGH);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, HIGH);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, HIGH);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);
}

void STEPPER_uniPolarFull_cw(void)
{
    DIO_writePin(COIL1A, HIGH);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, HIGH);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, HIGH);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, HIGH);
    _delay_ms(DELAY);
}

void Stepper_uniPolarFull_ccw(void)
{
    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, HIGH);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, HIGH);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, HIGH);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, HIGH);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);
}

void STEPPER_uniPolarHalf_cw(void)
{
    DIO_writePin(COIL1A, HIGH);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, HIGH);
    DIO_writePin(COIL1B, HIGH);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, HIGH);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, HIGH);
    DIO_writePin(COIL2A, HIGH);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, HIGH);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, HIGH);
    DIO_writePin(COIL2B, HIGH);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, HIGH);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, HIGH);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, HIGH);
    _delay_ms(DELAY);
}

void STEPPER_uniPolarHalf_ccw(void)
{
    DIO_writePin(COIL1A, HIGH);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, HIGH);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, HIGH);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, HIGH);
    DIO_writePin(COIL2B, HIGH);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, HIGH);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, HIGH);
    DIO_writePin(COIL2A, HIGH);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, LOW);
    DIO_writePin(COIL1B, HIGH);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, HIGH);
    DIO_writePin(COIL1B, HIGH);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);

    DIO_writePin(COIL1A, HIGH);
    DIO_writePin(COIL1B, LOW);
    DIO_writePin(COIL2A, LOW);
    DIO_writePin(COIL2B, LOW);
    _delay_ms(DELAY);
}