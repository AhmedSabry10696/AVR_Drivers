/**
 * @file Sensors.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Sensors driver implementation
 * @version 0.1
 * @date 21-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Sensors.h"

u16 POT_VoltRead(void)
{
    u16 adc = ADC_Read(POT);
    u16 volt = ((u32)adc*5000)/1024;

    return volt;
}

u16 LM35_TempRead(void)
{
    u16 adc = ADC_Read(LM35);
    u16 volt = ((u32)adc*5000)/1024;
    u16 temp = volt;
    return temp;
}