/**
 * @file ADC.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief ADC driver implementation
 * @version 0.1
 * @date 20-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ADC_Interface.h"

void ADC_Init(ADC_Ref_Type vref, ADC_Scaler_Type scaler)
{
    /* voltage reference */
    switch (vref)
    {
        case REF_AREF:
            CLEAR_BIT(ADMUX,REFS0);
            CLEAR_BIT(ADMUX,REFS1);
            break;

        case REF_VCC:
            SET_BIT(ADMUX,REFS0);
            CLEAR_BIT(ADMUX,REFS1);
            break;

        case REF_256V:
            SET_BIT(ADMUX,REFS0);
            SET_BIT(ADMUX,REFS1);
            break;
    }
    
    /* clock initialize */
    ADCSRA = ADCSRA & 0xF8;
    ADCSRA = ADCSRA | scaler;

    /* left adjustment */
    CLEAR_BIT(ADMUX,ADLAR);

    /* enable ADC */
    SET_BIT(ADCSRA,ADEN);
}

u16 ADC_Read(ADC_Channel_Type ch)
{
    u16 read = 0;
    /* channel selection */
    ADMUX = ADMUX & 0xE0;
    ADMUX = ADMUX | (ch&0x1F);

    /* ADC start conversion */
    SET_BIT(ADCSRA,ADSC);

    /* polling till conversion complete */
    while (1 == READ_BIT(ADCSRA,ADSC));

    /* get first 10 bits */
    read = ADC & 0x03FF;

    return read;
}
