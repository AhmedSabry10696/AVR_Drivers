/**
 * @file uart_stack.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Uart stack header file
 * @version 0.1
 * @date 15-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UART_STACK_H_
#define UART_STACK_H_

#include "std_types.h"

#define STACK_SIZE 5

typedef enum
{
    STACK_FULL = 0,
    STACK_EMPTY = 0,
    DONE
} StackStatus_type;

/**
 * @brief push one byte into uart stack
 * 
 * @param data byte to push
 * @return StackStatus_type STACK_FULL/DONE
 */
extern StackStatus_type UART_push(const u8 data);

/**
 * @brief pop one byte from stack
 * 
 * @param data_ptr pointer to write poped byte
 * @return StackStatus_type STACK_EMPTY/DONE
 */
extern StackStatus_type UART_pop(u8 *data_ptr);

#endif /* UART_STACK_H_ */
