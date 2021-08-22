/**
 * @file servo_motor.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Servo motor driver implementation
 * @version 0.1
 * @date 04-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "servo_motor.h"

void SERVO_init(void)
{
    TIMER1_init(TIMER1_FASTPWM_ICR_TOP_MODE, TIMER1_SCALER_8);
    TIMER1_OCRB_mode(OCRB_NON_INVERTING);

    /* set top to 20000us f = 50 HZ */
    TIMER1_ICR_set(20000 - 1);

    /* angle 0 ton = 1000 us (1 ms) */
    TIMER1_OCRB_set(999);
}

/*********************************
 * 000 angle -----> 1000 OCRB
 * 180 angle -----> 2000 OCRB
 ********************************/   
void SERVO_setPosition(u8 angle)
{
    if (angle > 180)
    {
        angle -= 180;
    }

    u16 temp = ((u32)angle * 1000) / 180 + 999;
    TIMER1_OCRB_set(temp);
}
