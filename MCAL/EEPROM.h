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

extern void EEPROM_Write(u16 address,u8 data);
extern u8 EEPROM_Read(u16 address);

#endif /* EEPROM_H_ */