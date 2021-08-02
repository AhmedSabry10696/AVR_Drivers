/**
 * @file   i2c_services.h
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

#include "i2c.h"

/**
 * @brief Master send byte to slave through TWI
 * 
 * @param address slave address 
 * @param data data to send
 * @return u8 TwiError_type
 */
extern TwiError_type TWI_Master_SendByte(u8 address, u8 data);

/**
 * @brief Master read byte from slave through TWI
 * 
 * @param address slave address
 * @param data pointer to store received data
 * @return TwiError_type
 */
extern TwiError_type TWI_masterReceiveByte(u8 address, u8 *data_ptr);

/**
 * @brief Maser send string to slave
 * 
 * @param address slave address
 * @param str string to send
 * @return u8 TwiError_type
 */
extern TwiError_type TWI_masterSendString(u8 address, u8 *str);

#endif /* I2C_SERVICES_H_ */