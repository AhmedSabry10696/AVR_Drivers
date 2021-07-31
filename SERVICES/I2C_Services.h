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
 * @param address slave address 
 * @param data data to send
 * @return u8 tWI_Error_type
 */
extern TWI_Error_type TWI_Master_SendByte(u8 address, u8 data);

/**
 * @brief Master read byte from slave through TWI
 * 
 * @param address slave address
 * @param data pointer to store received data
 * @return tWI_Error_type
 */
extern TWI_Error_type TWI_Master_ReceiveByte(u8 address, u8 *data);

/**
 * @brief Maser send string to slave
 * 
 * @param address slave address
 * @param str string to send
 * @return u8 tWI_Error_type
 */
extern TWI_Error_type TWI_Master_SendString(u8 address, u8 *str);

#endif /* I2C_SERVICES_H_ */