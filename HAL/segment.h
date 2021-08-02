/**
 * @file segment.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief  7 segment header file
 * @version 0.1
 * @date 02-08-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "std_types.h"
#include "dio.h"

#define LOW_PINS    0
#define HIGH_PINS   1
#define FULL_PORT   2

#define COM_ANODE   0
#define COM_CATHODE 1

/**
 * @brief display number on seven segment
 * 
 * @param num (0:F) when using only 1 segment and (0:99) when using 2 segment 
 */
extern void SEGMENT_display(u8 num);

#endif /* SEGMENT_H_ */
