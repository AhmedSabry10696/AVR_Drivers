/**
 * @file Uart_Services.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Uart services header file
 * @version 0.1
 * @date 12-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

#include "Uart.h"

/**
 * @brief uart send string
 * 
 * @param str string to send
 */
extern void Uart_SendString(const u8 *str);

/**
 * @brief uart receive string
 * 
 * @param str received string
 */
extern void Uart_ReceiveString(u8 *str);

/**
 * @brief uart send long number
 * 
 * @param num number to send
 */
extern void Uart_SendLong(u32 num);

/**
 * @brief uart receive long number
 * 
 * @return u32 received long number
 */
extern u32 Uart_ReceiveLong(void);

/**
 * @brief Uart Send string Async.
 * 
 * @param str string to send
 */
extern void Uart_SendStringAsyn(const u8 *str);

/**
 * @brief Uart receive string Async
 * 
 * @param str buffer to store received string
 */
extern void Uart_ReceiveStringAsyn(u8 *str);

#endif /* UART_SERVICES_H_ */