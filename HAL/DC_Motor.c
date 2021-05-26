/**
 * @file DC_Motor.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief DC Motor driver implementation
 * @version 0.1
 * @date 26-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "DC_Motor.h"

void DC_Motor_CW(void)
{
    DIO_WritePin(EN,HIGH);
    DIO_WritePin(IN1,HIGH);
    DIO_WritePin(IN2,LOW);
}

void DC_Motor_CCW(void)
{
    DIO_WritePin(EN,HIGH);
    DIO_WritePin(IN1,LOW);
    DIO_WritePin(IN2,HIGH);
}

void DC_Motor_Stop(void)
{
    DIO_WritePin(EN,LOW);
}