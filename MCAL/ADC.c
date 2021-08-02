/**
 * @file adc.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief ADC driver implementation
 * @version 0.1
 * @date 20-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "adc.h"

/* pointer to function to use it in callback function */
static void (*adc_fPtr)(void) = NULLPTR;

/* to prevent start conversion before the previous is finished */
static u8 reading_flag = 1;

void ADC_init(AdcVoltRef_type vref, AdcScaler_type scaler)
{
    /* voltage reference */
    switch (vref)
    {
    case REF_AREF:
        CLR_BIT(ADMUX, REFS0);
        CLR_BIT(ADMUX, REFS1);
        break;

    case REF_AVCC:
        SET_BIT(ADMUX, REFS0);
        CLR_BIT(ADMUX, REFS1);
        break;

    case REF_256V:
        SET_BIT(ADMUX, REFS0);
        SET_BIT(ADMUX, REFS1);
        break;
    }

    /* clock initialize */
    ADCSRA = ADCSRA & 0xF8;
    ADCSRA = ADCSRA | scaler;

    /* left adjustment */
    CLR_BIT(ADMUX, ADLAR);

    /* enable ADC */
    SET_BIT(ADCSRA, ADEN);
}

u16 ADC_read(Adc_channel_type ch)
{
    u16 read = 0;
    /* channel selection */
    ADMUX = ADMUX & 0xE0;
    ADMUX = ADMUX | (ch & 0x1F);

    /* ADC start conversion */
    SET_BIT(ADCSRA, ADSC);

    /* polling till conversion complete */
    while (1 == READ_BIT(ADCSRA, ADSC));

    /* get first 10 bits */
    read = ADC & 0x03FF;

    return read;
}

void ADC_startConversion(Adc_channel_type ch)
{
    if (reading_flag == 1)
    {
        /* Channel selection */
        ADMUX = ADMUX & 0xE0;
        ADMUX = ADMUX | (ch & 0x1F);

        /* ADC start conversion */
        SET_BIT(ADCSRA, ADSC);
        reading_flag = 0;
    }
}

u16 ADC_getReadNoBlock(void)
{
    return ADC;
}

u8 ADC_getReadPeriodic(u16 *read_ptr)
{
    /* if conversion completed */
    if (0 == READ_BIT(ADCSRA, ADSC))
    {
        *read_ptr = ADC;
        reading_flag = 1;
        return 1;
    }
    return 0;
}

void ADC_intEnable(void)
{
    SET_BIT(ADCSRA, ADIE);
}

void ADC_intDisable(void)
{
    CLR_BIT(ADCSRA, ADIE);
}

void ADC_intSetCallBack(void (*localPtr)(void))
{
    adc_fPtr = localPtr;
}

ISR(ADC_VECT)
{
    if (adc_fPtr != NULLPTR)
    {
        adc_fPtr();
    }
}