/**
 * @file DC_Motor_Interface.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief DC Motor header file
 * @version 0.1
 * @date 26-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "StdTypes.h"
#include "DIO.h"
#include "Timer.h"

/* motor connections */
#define IN1 PIND0
#define IN2 PIND1 
#define EN  PINB3

/**
 * @brief drive DC motor to rotate in clock wise directions
 * 
 */
extern void DC_Motor_CW(void);

/**
 * @brief drive DC motor to rotate in counter clock wise direction 
 * 
 */
extern void DC_Motor_CCW(void);

/**
 * @brief Init Timer0 to generate pwm 
 */
extern void DC_Motor_Speed_Init(void);
/**
 * @brief Set DC motor speed 
 * 
 * @param speed 0:100
 */
extern void DC_Motor_Speed(u8 speed);

/**
 * @brief stop DC motor
 * 
 */
extern void DC_Motor_Stop(void);

#endif /* DC_MOTOR_H_ */