/**
 * @file uart_stack.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Uart stack driver implementation
 * @version 0.1
 * @date 15-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "uart_stack.h"

static u8 stack[STACK_SIZE];
static u8 sp;

StackStatus_type UART_push(const u8 data)
{
    if (sp == STACK_SIZE)
    {
        return STACK_FULL;
    }

    stack[sp] = data;
    sp++;
    return DONE;
}

StackStatus_type UART_pop(u8 *data_ptr)
{
    if (0 == sp)
    {
        return STACK_EMPTY;
    }

    sp--;
    *data_ptr = stack[sp];
    return DONE;
}
