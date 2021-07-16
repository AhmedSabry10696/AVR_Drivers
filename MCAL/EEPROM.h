/**
 * @file EEPROM.h
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

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

/**
 * @brief EEPROM write byte at specific address
 * 
 * @param address to write at
 * @param data to write in address
 */
extern void EEPROM_Write(const u16 address,const u8 data);

/**
 * @brief read byte from specific address
 * 
 * @param address to read from
 * @return u8 byte from address
 */
extern u8 EEPROM_Read(const u16 address);

#endif /* EEPROM_H_ */