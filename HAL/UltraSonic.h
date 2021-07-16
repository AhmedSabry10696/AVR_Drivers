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
#include <util/delay.h>

#include "Timer.h"
#include "DIO.h"

#define ULTRASONIC1 PINC7
#define ULTRASONIC2 PINC6

typedef DIO_Pin_type ULTRASONIC_type;

/**
 * @brief Initialize ultra sonic
 * 
 */
extern void ULTRASONIC_Init(void);

/**
 * @brief read ultra sonic
 * 
 * @param ultra ULTRASONIC1/ULTRASONIC2
 * @return u16 distance
 */
extern u16 ULTRASONIC_Read(ULTRASONIC_type ultra);

/**
 * @brief Ultrasonic start 
 * 
 * @param ultra ULTRASONIC1/ULTRASONIC2
 */
extern void ULTRASONIC_Start(ULTRASONIC_type ultra);

/**
 * @brief Ultrasonic get read no block
 * 
 * @param pdistance distance
 * @return u8 result of operation 1:done 0:fail
 */
extern u8 ULTRASONIC_GetReadNoBlock(u16 *pdistance);

#endif /* ULTRASONIC_H_ */