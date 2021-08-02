/**
 * @file servo_motor.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Servo motor header file
 * @version 0.1
 * @date 04-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "timer.h"

/**
 * @brief Servo motor initialization f= 50HZ
 * 
 */
extern void SERVO_init(void);

/**
 * @brief Set angle of Servo motor
 * 
 * @param angle 0:180
 */
extern void SERVO_setPosition(u8 angle);

#endif /* SERVO_H_ */
