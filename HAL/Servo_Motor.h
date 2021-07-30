/**
 * @file Servo_Motor.h
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

#include "Timer.h"

/**
 * @brief Servo motor initialization f= 50HZ
 * 
 */
extern void Servo_Init(void);
/**
 * @brief Set angle of Servo motor
 * 
 * @param angle 0:180
 */
extern void Servo_SetPosition(u8 angle);

#endif /* SERVO_H_ */