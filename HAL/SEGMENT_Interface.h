
#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "StdTypes.h"
#include "DIO_Interface.h"

#define LOW_PINS    0
#define HIGH_PINS   1

#define COM_ANODE   0
#define COM_CATHODE 1

extern void SEGMENT_Display_Digit(u8 num);

#endif /* SEGMENT_H_ */