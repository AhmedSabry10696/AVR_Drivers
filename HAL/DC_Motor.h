/**
 * @file DC_Motor.h
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
#include "DIO_Interface.h"
#include "DC_Motor_Lcfg.h"

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
 * @brief stop DC motor
 * 
 */
extern void DC_Motor_Stop(void);

#endif /* DC_MOTOR_H_ */