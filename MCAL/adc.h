/**
 * @file adc.h
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

#include "std_types.h"
#include "utils.h"
#include "memory_map.h"

typedef enum
{
    REF_AREF,
    REF_AVCC,
    REF_256V
} AdcVoltRef_type;

typedef enum
{
    ADC_SCALER_2 = 1,
    ADC_SCALER_4,
    ADC_SCALER_8,
    ADC_SCALER_16,
    ADC_SCALER_32,
    ADC_SCALER_64,
    ADC_SCALER_128
} AdcScaler_type;

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
} Adc_channel_type;

/**
 * @brief 
 * 
 * @param vref   REF_AREF - REF_AVCC - REF_256V
 * @param scaler ADC_Scaler_2 : ADC_Scaler_128
 */
extern void ADC_init(AdcVoltRef_type vref, AdcScaler_type scaler);

/**
 * @brief ADC read channel
 * 
 * @param ch CH_0 : CH_7
 * @return u16 ADC reading value 0 : 1023
 */
extern u16 ADC_read(Adc_channel_type ch);

/**
 * @brief ADC Start conversion
 * 
 * @param ch CH_0 : CH_7
 */
extern void ADC_startConversion(Adc_channel_type ch);

/**
 * @brief Get adc read if completed
 * 
 * @param read_ptr pointer to store adc value 0:1023
 * @return u8 (1) if get adc value, (0) if adc not finished yet
 */
extern u8 ADC_getReadPeriodic(u16 *read_ptr);

/**
 * @brief get value of ADC register
 * 
 * @return u16 ADC read after conversion completed 0:1023
 */
extern u16 ADC_getReadNoBlock(void);

/**
 * @brief Enable ADC interrupt on conversion complete
 * 
 */
extern void ADC_intEnable(void);

/**
 * @brief Disable ADC interrupt on conversion complete
 * 
 */
extern void ADC_intDisable(void);

/**
 * @brief set address of the function to run when adc interrupt fired
 * 
 * @param localPtr address of the function
 */
extern void ADC_intSetCallBack(void (*localPtr)(void));

#endif /* ADC_H_ */
