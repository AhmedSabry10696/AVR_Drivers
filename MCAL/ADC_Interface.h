/**
 * @file ADC_Interface.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief ADC interface header file
 * @version 0.1
 * @date 20-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"

typedef enum
{
    REF_AREF,
    REF_VCC,
    REF_256V
}ADC_Ref_Type;

typedef enum
{
    ADC_Scaler_2 = 1,
    ADC_Scaler_4,
    ADC_Scaler_8,
    ADC_Scaler_16,
    ADC_Scaler_32,
    ADC_Scaler_64,
    ADC_Scaler_128
}ADC_Scaler_Type;

typedef enum
{
    CH_0,
    CH_1,
    CH_2,
    CH_3,
    CH_4,
    CH_5,
    CH_6,
    CH_7
}ADC_Channel_Type;

/**
 * @brief ADC Initialization
 * 
 * @param vref voltage ref selection
 * @param scaler prescaller selection
 */
extern void ADC_Init(ADC_Ref_Type vref, ADC_Scaler_Type scaler);

/**
 * @brief ADC read channel
 * 
 * @param ch ADC channel selection
 * @return u16 ADC reading
 */
extern u16 ADC_Read(ADC_Channel_Type ch);

#endif /* ADC_INTERFACE_H_ */