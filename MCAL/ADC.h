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

#ifndef ADC_H_
#define ADC_H_

#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"

typedef enum
{
    REF_AREF,
    REF_AVCC,
    REF_256V
}ADC_VoltRef_Type;

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
 * @brief 
 * 
 * @param vref   REF_AREF - REF_AVCC - REF_256V
 * @param scaler ADC_Scaler_2 : ADC_Scaler_128
 */
extern void ADC_Init(ADC_VoltRef_Type vref, ADC_Scaler_Type scaler);

/**
 * @brief ADC read channel
 * 
 * @param ch CH_0 : CH_7
 * @return u16 ADC reading value 0 : 1023
 */
extern u16 ADC_Read(ADC_Channel_Type ch);

/**
 * @brief ADC Start conversion
 * 
 * @param ch CH_0 : CH_7
 */
extern void ADC_StartConversion(ADC_Channel_Type ch);

/**
 * @brief get value of ADC register
 * 
 * @return u16 ADC read after conversion completed 0:1023
 */
extern u16 ADC_GetReadNoBlock(void);

/**
 * @brief Get adc read if completed
 * 
 * @param pdata pointer to store adc value 0:1023
 * @return u8 (1) if get adc value, (0) if adc not finished yet
 */
extern u8 ADC_GetRead_Periodic(u16* pdata);

/**
 * @brief Enable ADC interrupt on conversion complete
 * 
 */
extern void ADC_IntEnable(void);

/**
 * @brief Disable ADC interrupt on conversion complete
 * 
 */
extern void ADC_IntDisable(void);

/**
 * @brief set address of the function to run when adc interrupt fired
 * 
 * @param LocalPtr address of the function
 */
extern void ADC_IntSetCallBack(void(*LocalPtr)(void));


#endif /* ADC_H_ */