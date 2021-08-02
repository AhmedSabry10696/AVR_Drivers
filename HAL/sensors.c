/**
 * @file sensors.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Sensors driver implementation
 * @version 0.1
 * @date 21-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "sensors.h"

u16 POT_voltRead(void)
{
    u16 adc = ADC_read(POT);
    u16 volt = ((u32)adc * 5000) / 1024;

    return volt;
}

/* 10 mv/1 C */
u16 LM35_tempRead(void)
{
    u16 adc = ADC_read(LM35);
    u16 volt = ((u32)adc * 5000) / 1024;
    u16 temp = volt;

    return temp;
}

/* 
    15 kpa  :  115 kpa
    0.2 v   :  4.7 v
    55 adc  :  976 adc
*/
u16 MPX4110_pressureRead(void)
{
    u16 adc = ADC_read(MPX4110);
    u16 pres = (((adc - 55) * (u32)1000) / 921) + 150;
    return pres;
}
