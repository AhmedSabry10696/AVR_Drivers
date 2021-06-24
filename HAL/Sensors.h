/**
 * @file Sensors.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Sensors header file 
 * @version 0.1
 * @date 21-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include "ADC_Interface.h"

#define POT     CH_0
#define LM35    CH_1
#define MPX4110 CH_2

/**
 * @brief POT voltage read
 * 
 * @return u16 Voltage output
 */
extern u16 POT_VoltRead(void);

/**
 * @brief Temp sensor read
 * 
 * @return u16 Temp reading
 */
extern u16 LM35_TempRead(void);

#endif /* SENSORS_H_ */