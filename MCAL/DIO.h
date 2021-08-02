/**
 * @file dio.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief DIO Interface header file
 * @version 0.1
 * @date 25-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef DIO_H_
#define DIO_H_

#include "std_types.h"
#include "memory_map.h"
#include "utils.h"

typedef enum
{
	PINA0 = 0,
	PINA1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,

	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,

	PINC0,
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,

	PIND0,
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,

	TOTAL_PINS = 32
} DioPin_type;

typedef enum
{
	OUTPUT,
	INFREE,
	INPULLUP
} DioPinStatus_type;

typedef enum
{
	PA = 0,
	PB,
	PC,
	PD
} DioPort_type;

typedef enum
{
	LOW = 0,
	HIGH
} DioVoltage_type;

/**
 * @brief Initialize any pin as output or input with or without pull up resistor
 * 
 * @param pin pin number PINA0:PINA7 PINB0:PINB7 PINC0:PINC7 PIND0:PIND7
 * @param status OUTPUT - INFREE - INPULLUP
 */
extern void DIO_initPin(DioPin_type pin, DioPinStatus_type status);

/**
 * @brief set any pin value to high or low
 * 
 * @param pin pin number PINA0:PINA7 PINB0:PINB7 PINC0:PINC7 PIND0:PIND7
 * @param volt HIGH - LOW
 */
extern void DIO_writePin(DioPin_type pin, DioVoltage_type volt);

/**
 * @brief toggle any pin state
 * 
 * @param pin pin number PINA0:PINA7 PINB0:PINB7 PINC0:PINC7 PIND0:PIND7
 */
extern void DIO_togglePin(DioPin_type pin);

/**
 * @brief read any pin value
 * 
 * @param pin pin number PINA0:PINA7 PINB0:PINB7 PINC0:PINC7 PIND0:PIND7
 * @return DioVoltage_type HIGH - LOW
 */
extern DioVoltage_type DIO_readPin(DioPin_type pin);

/**
 * @brief set any port value
 * 
 * @param port PA - PB - PC - PD 
 * @param value unsigned char value 0:255
 */
extern void DIO_writePort(DioPort_type port, const u8 value);

/**
 * @brief Edit four lower pins in port without affecting upper four pins
 * 
 * @param port PA - PB - PC - PD
 * @param value 0:F
 */
extern void DIO_editPort_lowNibble(DioPort_type port, u8 value);

/**
 * @brief Edit four higher pins in port without affecting lower four pins
 * 
 * @param port PA - PB - PC - PD
 * @param value 0:F
 */
extern void DIO_editPort_highNibble(DioPort_type port, u8 value);

/**
 * @brief read any port value
 * 
 * @param port PA - PB - PC - PD
 * @return u8 port value 0:255
 */
extern u8 DIO_readPort(DioPort_type port);

/**
 * @brief Init all DIO in the controller
 * 
 */
extern void DIO_init(void);

/* array in dio_config.c file contains all pins direction */
extern const DioPinStatus_type pins_status[TOTAL_PINS];

#endif /* DIO_H_ */