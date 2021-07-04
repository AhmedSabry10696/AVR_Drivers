/**
 * @file UltraSonic.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief UltraSonic header file
 * @version 0.1
 * @date 04-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define F_CPU 8000000UL
#include "Timer.h"
#include "DIO_Interface.h"
#include <util/delay.h>

#define ULTRASONIC1 PINC7
#define ULTRASONIC2 PINC6
typedef DIO_Pin_type ULTRASONIC_type;

extern void ULTRASONIC_Init(void);
extern u16 ULTRASONIC_Read(ULTRASONIC_type ultra);
extern void ULTRASONIC_Start(ULTRASONIC_type ultra);
extern u8 ULTRASONIC_GetReadNoBlock(u16 *pdistance);

#endif /* ULTRASONIC_H_ */