/**
 * @file uart_services.h
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

#include "uart.h"

/**
 * @brief uart send string
 * 
 * @param str string to send
 */
extern void UART_sendString(const u8 *str);

/**
 * @brief uart receive string
 * 
 * @param str received string
 */
extern void UART_receiveString(u8 *str);

/**
 * @brief uart send long number
 * 
 * @param num number to send
 */
extern void UART_sendLong(u32 num);

/**
 * @brief uart receive long number
 * 
 * @return u32 received long number
 */
extern u32 UART_receiveLong(void);

/**
//  * @brief Uart Send string Asyn.
 * 
 * @param str string to send
 */
extern void UART_sendStringAsyn(u8 *str);

/**
 * @brief Uart receive string Asyn
 * 
 * @param str buffer to store received string
 */
extern void UART_receiveStringAsyn(u8 *str);

#endif /* UART_SERVICES_H_ */
