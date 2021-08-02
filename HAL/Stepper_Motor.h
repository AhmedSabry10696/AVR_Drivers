/**
 * @file stepper_motor.h
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

#include "std_types.h"
#include "dio.h"

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
extern void STEPPER_biPolarFull_cw(void);

/**
 * @brief rotate stepper 4 steps in anti clock wise direction
 * @note  full stepping one phase on
 */
extern void STEPPER_biPolarFull_ccw(void);

/**
 * @brief rotate stepper 4 steps in clock wise direction
 * @note  full stepping one phase on
 */
extern void STEPPER_uniPolarFull_cw(void);

/**
 * @brief rotate stepper 4 steps in anti clock wise direction
 * @note  full stepping one phase on
 */
extern void STEPPER_uniPolarFull_ccw(void);

/**
 * @brief rotate stepper 4 steps in clock wise direction
 * @note  half stepping
 */
extern void STEPPER_uniPolarHalf_cw(void);

/**
 * @brief rotate stepper 4 steps in anti clock wise direction
 * @note  half stepping
 */
extern void STEPPER_uniPolarHalf_ccw(void);

#endif /* STEPPER_MOTOR_H_ */
