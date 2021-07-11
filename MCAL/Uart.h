/**
 * @file Uart.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief uart header file
 * @version 0.1
 * @date 10-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UART_H_
#define UART_H_

#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"

/**
 * @brief uart init
 * 
 */
extern void Uart_Init(void);

/**
 * @brief uart send byte
 * 
 * @param data byte to send
 */
extern void Uart_Send(u8 data);

/**
 * @brief uart receive byte
 * 
 * @return u8 received byte
 */
extern u8 Uart_Receive(void);


#endif /* UART_H_ */