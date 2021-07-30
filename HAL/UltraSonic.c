/**
 * @file UltraSonic.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief UltraSonic driver implementation 
 * @version 0.1
 * @date 04-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "UltraSonic.h"

static volatile u16 t1, t2;
static volatile u8 flag = 3;

static void ICU_Func(void)
{
    if (0 == flag)
    {
        t1 = Timer1_ICR_Get();
        flag = 1;
        Timer1_InputCaptureEdge(FALLING);
    }
    else if (1 == flag)
    {
        t2 = Timer1_ICR_Get();
        flag = 2;
    }
}
void UlTRASONIC_Init(void)
{
    Timer1_Init(TIMER1_NORMAL_MODE, TIMER1_SCALER_8);
    Timer1_ICU_IntSetCallBack(ICU_Func);
}
u16 ULTRASONIC_Read(ULTRASONIC_type ultra)
{
    u16 d, time;
    Timer1_ICU_IntEnable();
    flag = 0;
    Timer1_InputCaptureEdge(RISING);

    /* trigger pin */
    DIO_WritePin(ultra, HIGH);
    _delay_us(10);
    DIO_WritePin(ultra, LOW);

    while (flag < 2)
        ;
    time = t2 - t1;
    d = time / 58;
    return d;
}
void ULTRASONIC_Start(ULTRASONIC_type ultra)
{
    if (3 == flag)
    {
        flag = 0;
        Timer1_InputCaptureEdge(RISING);
        Timer1_ICU_IntEnable();

        /* trigger pin */
        DIO_WritePin(ultra, HIGH);
        _delay_us(10);
        DIO_WritePin(ultra, LOW);
    }
}
u8 ULTRASONIC_GetReadNoBlock(u16 *pdistance)
{
    u16 time;
    if (2 == flag)
    {
        time = t2 - t1;
        *pdistance = time / 58;
        flag = 3;
        return 1;
    }
    return 0;
}