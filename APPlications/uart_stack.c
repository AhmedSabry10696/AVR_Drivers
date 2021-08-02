/**
 * @file Uart_Stack.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Uart stack app
 * @version 0.1
 * @date 15-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "std_types.h"
#include "uart.h"
#include "uart_stack.h"

static volatile u8 full_flag =0,flag = 0;

static void RX_func(void)
{
    u8 data = UART_receiveNoBlock();
    
    if(UART_push(data) == STACK_FULL)
    {
        full_flag = 1;
    }
}

static void EX_func(void)
{
    flag = 1;
}

int main(void)
{
    DIO_init();
    LCD_init();
    u8 data;
    
    while (1)
    {
        if(1 == full_flag)
        {
            UART_sendString("stack is full");
            LCD_goTo(1,0);
            LCD_writeString("stack is full");
            full_flag = 0;
        }
        if(1 == flag)
        {
            if(DONE == UART_pop(&data))
            {
                LCD_writeChar(data);
                LCD_writeString("     ");
            }
            else
            {
                LCD_goTo(1,0);
                LCD_writeString("Stack Empty");
            }
            flag = 0;
        }
    }
    
}
