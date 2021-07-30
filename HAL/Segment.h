
#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "StdTypes.h"
#include "DIO.h"

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
extern void SEGMENT_Display(u8 num);

#endif /* SEGMENT_H_ */