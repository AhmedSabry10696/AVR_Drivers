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

/***************************
 * 0000 mv -----> 0000 ADC 
 * 5000 mv -----> 1023 ADC
 ***************************/
u16 POT_voltRead(void)
{
    u16 adc = ADC_read(POT);
    u16 volt = ((u32)adc * 5000) / 1024;

    return volt;
}

/************* 10 mv/c **************
 * 002.0 C -----> 40   mv (008 ADC) 
 * 150.0 C -----> 1500 mv (308 ADC)
 ************************************/
u16 LM35_tempRead(void)
{
    u16 adc = ADC_read(LM35);
    u16 volt = ((u32)adc * 5000) / 1024;
    u16 temp = volt;

    return temp;
}

/*************************************
 * 015.0 kpa -----> 0200 mv (055 ADC) 
 * 115.0 kpa -----> 4700 mv (976 ADC)
 ************************************/
u16 MPX4110_pressureRead(void)
{
    u16 adc = ADC_read(MPX4110);
    u16 pres = (((adc - 55) * (u32)1000) / 921) + 150;
    return pres;
}
