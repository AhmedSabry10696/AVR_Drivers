/**
 * @file dc_motor.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief DC Motor driver implementation
 * @version 0.1
 * @date 26-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "dc_motor.h"

void DC_motor_cw(void)
{
    DIO_writePin(IN1, HIGH);
    DIO_writePin(IN2, LOW);
}

void DC_motor_ccw(void)
{
    DIO_writePin(IN1, LOW);
    DIO_writePin(IN2, HIGH);
}

void DC_motorSpeedInit(void)
{
    TIMER0_init(TIMER0_FAST_PWM, TIMER0_SCALER_8);
    TIMER0_OC0_mode(OC0_NON_INVERTING);
}

void DC_motorSpeed(u8 speed)
{
    u8 temp = (255 * speed) / 100;
    TIMER0_OCR_set(temp);
}

void DC_motorStop(void)
{
    DIO_writePin(EN, LOW);
    DIO_writePin(IN1, LOW);
    DIO_writePin(IN2, LOW);
}
