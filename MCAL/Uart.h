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


typedef enum
{
    NO_PARITY=0,
    EVEN_PARITY,
    ODD_PARITY
}Parity_type;
typedef enum
{
    ONE_STOP_BIT=0,
    TWO_STOP_BIT
}Stop_Bit_type;
typedef enum
{
    FIVE_BIT_DATA = 0,
    SIX_BIT_DATA,
    SEVEN_BIT_DATA,
    EIGHT_BIT_DATA,
    NINE_BIT_DATA
}Data_size_type;
typedef enum 
{
    BAUD_2400 = 0,
    BAUD_4800,
    BAUD_9600,
    BAUD_14400,
    BAUD_19200,
    BAUD_28800,
    BAUD_38400,
    BAUD_57600,
    BAUD_76800,
    BAUD_115200,
    BAUD_230400,
    BAUD_250000,
    BAUD_500000,
    BAUD_1000000
}BaudRate_type;
typedef struct
{
    Parity_type parity;
    Stop_Bit_type stop;
    Data_size_type data;
    BaudRate_type baud;
}Uart_Config;

extern void Uart_Init(void);
/**
 * @brief Uart transmitter enable
 * 
 */
extern void Uart_TX_Enable(void);
/**
 * @brief Uart transmitter disable
 * 
 */
extern void Uart_TX_Disable(void);
/**
 * @brief Uart receiver enable
 * 
 */
extern void Uart_RX_Enable(void);
/**
 * @brief Uart receiver disable
 * 
 */
extern void Uart_RX_Disable(void);
/**
 * @brief Uart send one byte
 * 
 * @param data byte to send
 */
extern void Uart_Send(const u8 data);
/**
 * @brief Uart receive one byte
 * 
 * @return u8 received byte
 */
extern u8 Uart_Receive(void);
/**
 * @brief Uart received one byte using periodic check(no block)
 * 
 * @param pdata pointer to store received byte
 * @return u8 result 0 if no data received/ 1 if data received
 */
extern u8 Uart_Receive_PeriodicCheck(u8 *pdata);
/**
 * @brief Uart write data in the buffer
 * 
 * @param data data to write in the buffer
 */
extern void Uart_SendNoBlock(const u8 data);
/**
 * @brief Uart read the value in the buffer
 * 
 * @return u8 the value in the buffer
 */
extern u8 Uart_ReceiveNoBlock(void);
/**
 * @brief Uart TXC interrupt enable
 * 
 */
extern void Uart_TXC_IntEnable(void);
/**
 * @brief Uart TXC interrupt disable
 * 
 */
extern void Uart_TXC_IntDisable(void);
/**
 * @brief Uart RXC interrupt enable 
 * 
 */
extern void Uart_RXC_IntEnable(void);
/**
 * @brief Uart RXC interrupt disable 
 * 
 */
extern void Uart_RXC_IntDisable(void);
/**
 * @brief Uart buffer empty interrupt enable 
 * 
 */
extern void Uart_DEMPTY_IntEnable(void);
/**
 * @brief Uart buffer empty interrupt disable
 * 
 */
extern void Uart_DEMPTY_IntDisable(void);
/**
 * @brief Uart TXC interrupt set callback 
 * 
 * @param LocalFptr address of function to run when TXC interrupt occur
 */
extern void Uart_TXC_IntSetCallBack(void(*LocalFptr)(void));
/**
 * @brief Uart RXC interrupt set call back
 * 
 * @param LocalFptr address of function to run when RXC interrupt occur.
 */
extern void Uart_RXC_IntSetCallBack(void(*LocalFptr)(void));
/**
 * @brief Uart buffer empty interrupt set call back
 * 
 * @param LocalFptr address of function to run when buffer empty interrupt occur.
 */
extern void Uart_DEMPTY_IntSetCallBack(void(*LocalFptr)(void));

/**
 * @brief Uart configuration struct
 * 
 */
extern const Uart_Config uart;

#endif /* UART_H_ */