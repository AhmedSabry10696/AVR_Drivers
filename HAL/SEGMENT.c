/**
 * @file Segment.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief 7 segment driver implementation
 * @version 0.1
 * @date 27-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Segment.h"
#include "Segment_Config.h"

#ifndef BCD
static u8 Seg_Nums[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6f, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
#endif

void SEGMENT_Display(u8 num)
{
#ifndef BCD
#if (COM_CATHODE == SEGMENT_TYPE)
	DIO_WritePort(SEGMENT_PORT, Seg_Nums[num % 16]);

#elif (COM_ANODE == SEGMENT_TYPE)
	DIO_WritePort(SEGMENT_PORT, ~(Seg_Nums[num % 16]));
#endif
#else
#if (LOW_PINS == BCD)
	DIO_EditPort_LowerHalf(SEGMENT_PORT, num);
#elif (HIGH_PINS == BCD)
	DIO_EditPort_HigherHalf(SEGMENT_PORT, num);
#elif (FULL_PORT == BCD)
	u8 digit = num % 10;
	DIO_EditPort_LowerHalf(SEGMENT_PORT, digit);
	num /= 10;
	digit = num % 10;
	DIO_EditPort_HigherHalf(SEGMENT_PORT, digit);
#endif
#endif
}