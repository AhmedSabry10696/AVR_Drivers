/**
 * @file Stepper_Motor.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Stepper motor header file
 * @version 0.1
 * @date 26-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef STEPPER_MOTOR_H_
#define STEPPER_MOTOR_H_

#define F_CPU 8000000UL
#include <util/delay.h>

#include "StdTypes.h"
#include "DIO.h"

#define DELAY 100

/* stepper motor control pins */
#define COIL1A PINC0
#define COIL1B PINC1
#define COIL2A PINC2
#define COIL2B PINC3

/**
 * @brief rotate stepper 4 steps in clock wise direction
 * @note  full stepping one phase on
 */
extern void Stepper_BiPolarFull_CW(void);

/**
 * @brief rotate stepper 4 steps in anti clock wise direction
 * @note  full stepping one phase on
 */
extern void Stepper_BiPolarFull_CCW(void);

/**
 * @brief rotate stepper 4 steps in clock wise direction
 * @note  full stepping one phase on
 */
extern void Stepper_UniPolarFull_CW(void);

/**
 * @brief rotate stepper 4 steps in anti clock wise direction
 * @note  full stepping one phase on
 */
extern void Stepper_UniPolarFull_CCW(void);

/**
 * @brief rotate stepper 4 steps in clock wise direction
 * @note  half stepping
 */
extern void Stepper_UniPolarHalf_CW(void);

/**
 * @brief rotate stepper 4 steps in anti clock wise direction
 * @note  half stepping
 */
extern void Stepper_UniPolarHalf_CCW(void);

#endif /* STEPPER_MOTOR_H_ */
