/**
 * @file ultra_sonic.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief UltraSonic driver implementation 
 * @version 0.1
 * @date 04-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ultra_sonic.h"

static volatile u16 t1, t2;
static volatile u8 flag = 3;

/* function to run when input capture unit interrupt fired */
static void ICU_func(void)
{
    if (0 == flag)
    {
        t1 = TIMER1_ICR_get();
        flag = 1;
        TIMER1_inputCaptureEdge(FALLING);
    }
    else if (1 == flag)
    {
        t2 = TIMER1_ICR_get();
        flag = 2;
    }
}

void UlTRASONIC_init(void)
{
    /* max 2^16 tick, tick time = 1 us */
    TIMER1_init(TIMER1_NORMAL_MODE, TIMER1_SCALER_8);
    TIMER1_ICU_intSetCallBack(ICU_func);
}

u16 ULTRASONIC_Read(Ultrasonic_type ultra)
{
    u16 d, time;
    TIMER1_ICU_intEnable();
    flag = 0;
    TIMER1_inputCaptureEdge(RISING);

    /* trigger pin */
    DIO_writePin(ultra, HIGH);
    _delay_us(10);
    DIO_writePin(ultra, LOW);

    while (flag < 2);

    time = t2 - t1;
    d = time / 58;
    
    return d;
}

void ULTRASONIC_start(Ultrasonic_type ultra)
{
    if (3 == flag)
    {
        flag = 0;
        TIMER1_inputCaptureEdge(RISING);
        TIMER1_ICU_intEnable();

        /* trigger pin */
        DIO_writePin(ultra, HIGH);
        _delay_us(10);
        DIO_writePin(ultra, LOW);
    }
}

u8 ULTRASONIC_getReadNoBlock(u16 *distance_ptr)
{
    u16 time;
    if (2 == flag)
    {
        time = t2 - t1;
        *distance_ptr = time / 58;
        flag = 3;
        return 1;
    }
    return 0;
}