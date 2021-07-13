/**
 * @file Servo_Motor.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Servo motor driver implementation
 * @version 0.1
 * @date 04-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Servo_Motor.h"

void Servo_Init(void)
{
    Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
    Timer1_OCRB_Mode(OCRB_NON_INVERTING);
    
    /* set top to 20000us f=50HZ */
    Timer1_ICR_Set(20000-1);

    /* angle 0 ton=1ms*/
    Timer1_OCRB_Set(999);
}

void Servo_SetPosition(u8 angle)
{
    if (angle > 180)
    {
        angle -= 180;
    }
    
    u16 temp = ((u32)angle*1000)/180+999;
    Timer1_OCRB_Set(temp);
}