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

#include "StdTypes.h"
#include "Uart.h"
#include "Uart_Stack.h"

static volatile u8 full_flag =0,flag = 0;

static void RX_Func(void)
{
    u8 data = Uart_ReceiveNoBlock();
    
    if(Uart_Push(data) == STACK_FULL)
    {
        full_flag = 1;
    }
}

static void EX_Func(void)
{
    flag = 1;
}

int main(void)
{
    DIO_Init();
    LCD_Init();
    u8 data;
    
    while (1)
    {
        if(1 == full_flag)
        {
            Uart_SendString("stack is full");
            LCD_GoTo(1,0);
            LCD_WriteString("stack is full");
            full_flag = 0;
        }
        if(1 == flag)
        {
            if(DONE == Uart_Pop(&data))
            {
                LCD_WriteChar(data);
                LCD_WriteString("     ");
            }
            else
            {
                LCD_GoTo(1,0);
                LCD_WriteString("Stack Empty");
            }
            flag = 0;
        }
    }
    
}