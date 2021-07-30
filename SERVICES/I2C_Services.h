/**
 * @file I2C_Services.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief 
 * @version 0.1
 * @date 30-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef I2C_SERVICES_H_
#define I2C_SERVICES_H_

#include "I2C.h"

/**
 * @brief Master send byte to slave through TWI
 * 
 * @param SlaveAddress slave address 
 * @param data data to send
 * @return u8 result of operation 1{done}, 0{failed}
 */
extern u8 TWI_Master_WriteByte(u8 SlaveAddress, u8 data);

/**
 * @brief Master read byte from slave through TWI
 * 
 * @param SlaveAddress slave address
 * @param data pointer to store received data
 * @return u8 result of operation 1{done}, 0{failed}
 */
extern u8 TWI_Master_ReadByte(u8 SlaveAddress, u8 *data);

/**
 * @brief Slave read byte from master when its address match address on bus
 *        and there is also write request from master.
 * @param data pointer to store received data from master
 * @return u8 result of operation 1{done}, 0{failed}
 */
extern u8 TWI_Slave_ReadByte(u8 *data);

/**
 * @brief Slave write byte to master when its address match address on bus
 *        and there is also read request from master.  
 * @param data data to send
 * @return u8 result of operation 1{done}, 0{failed}
 */
extern u8 TWI_Slave_WriteByte(u8 data);

/**
 * @brief Maser send string to slave
 * 
 * @param SlaveAddress slave address
 * @param str string to send
 * @return u8 result of operation 1{done}, 0{failed}
 */
extern u8 TWI_Master_WriteString(u8 SlaveAddress, u8 *str);

#endif /* I2C_SERVICES_H_ */