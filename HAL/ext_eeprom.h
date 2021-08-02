/**
 * @file ext_eeprom.h
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

/**
 * @brief EEPROM initialization
 * 
 */
void EEPROM_init(void);

/**
 * @brief Write byte in EEPROM
 * 
 * @param address address to write data in
 * @param data data to write at address in EEPROM
 * @return EEPROM_Error_type ERROR/SUCCESS
 */
EEPROM_Error_type EEPROM_writeByte(u16 address, u8 data);

/**
 * @brief read byte from specified address in EEPROM
 * 
 * @param address address to read from
 * @param data_ptr pointer to save byte
 * @return EEPROM_Error_type ERROR/SUCCESS
 */
EEPROM_Error_type EEPROM_readByte(u16 address, u8 *data_ptr);

#endif /* EXT_EEPROM_H_ */
