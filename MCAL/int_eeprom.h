/**
 * @file int_eeprom.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief EEPROM header file
 * @version 0.1
 * @date 15-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_types.h"
#include "memory_map.h"
#include "utils.h"

/**
 * @brief EEPROM write byte at specific address
 * 
 * @param address to write at
 * @param data to write in address
 */
extern void EEPROM_write(const u16 address, const u8 data);

/**
 * @brief read byte from specific address
 * 
 * @param address to read from
 * @return u8 byte from address
 */
extern u8 EEPROM_read(const u16 address);

/**
 * @brief Enable eeprom ready interrupt
 * 
 */
extern void EEPROM_intEnable(void);

/**
 * @brief disable eeprom ready interrupt
 * 
 */
extern void EEPROM_intDisable(void);

/**
 * @brief Set callback function for eeprom ready interrupt
 * 
 * @param localFptr pointer to function to run when eeprom ready interrupt fired
 */
extern void EEPROM_intSetCallback(void (*localFptr)(void));

#endif /* EEPROM_H_ */