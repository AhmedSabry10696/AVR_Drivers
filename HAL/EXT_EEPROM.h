/**
 * @file EXT_EEPROM.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief External EEPROM header file
 * @version 0.1
 * @date 30-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef EXT_EEPROM_H_
#define EXT_EEPROM_H_

#include "i2c.h"

typedef enum
{
    ERROR = 0,
    SUCCESS
} EEPROM_Error_type;

void EEPROM_Init(void);
EEPROM_Error_type EEPROM_Write_Byte(u16 address, u8 data);
EEPROM_Error_type EEPROM_Read_Byte(u16 address, u8 *data);

#endif /* EXT_EEPROM_H_ */