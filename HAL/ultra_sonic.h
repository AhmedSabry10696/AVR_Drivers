/**
 * @file ultra_sonic.h
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

#include "timer.h"
#include "dio.h"

#define ULTRASONIC1 PINC7
#define ULTRASONIC2 PINC6

typedef DioPin_type Ultrasonic_type;

/**
 * @brief Initialize ultra sonic
 * 
 */
extern void ULTRASONIC_init(void);

/**
 * @brief read ultra sonic
 * 
 * @param ultra ULTRASONIC1/ULTRASONIC2
 * @return u16 distance
 */
extern u16 ULTRASONIC_read(Ultrasonic_type ultra);

/**
 * @brief Ultrasonic start 
 * 
 * @param ultra ULTRASONIC1/ULTRASONIC2
 */
extern void ULTRASONIC_start(Ultrasonic_type ultra);

/**
 * @brief Ultrasonic get read no block
 * 
 * @param distance_ptr distance
 * @return u8 result of operation 1:done 0:fail
 */
extern u8 ULTRASONIC_getReadNoBlock(u16 *distance_ptr);

#endif /* ULTRASONIC_H_ */