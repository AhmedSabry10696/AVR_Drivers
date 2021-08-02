/**
 * @file uart.h
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

#include "std_types.h"
#include "utils.h"
#include "memory_map.h"

typedef enum
{
    NO_PARITY = 0,
    EVEN_PARITY,
    ODD_PARITY
} Parity_type;

typedef enum
{
    ONE_STOP_BIT = 0,
    TWO_STOP_BIT
} StopBit_type;

typedef enum
{
    FIVE_BIT_DATA = 0,
    SIX_BIT_DATA,
    SEVEN_BIT_DATA,
    EIGHT_BIT_DATA,
    NINE_BIT_DATA
} DataSize_type;

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
} BaudRate_type;

typedef struct
{
    Parity_type parity;
    StopBit_type stop;
    DataSize_type data;
    BaudRate_type baud;
} UartConfig;

/**
 * @brief Uart init based on Uart_config.c file
 * 
 */
extern void UART_init(void);

/**
 * @brief UART transmitter enable
 * 
 */
extern void UART_TX_enable(void);

/**
 * @brief UART transmitter disable
 * 
 */
extern void UART_TX_disable(void);

/**
 * @brief UART receiver enable
 * 
 */
extern void UART_RX_enable(void);

/**
 * @brief UART receiver disable
 * 
 */
extern void UART_RX_disable(void);

/**
 * @brief UART send one byte
 * 
 * @param data byte to send
 */
extern void UART_send(const u8 data);

/**
 * @brief UART receive one byte
 * 
 * @return u8 received byte
 */
extern u8 UART_receive(void);

/**
 * @brief UART received one byte using periodic check(no block)
 * 
 * @param data_ptr pointer to store received byte
 * @return u8 result 0 if no data received/ 1 if data received
 */
extern u8 UART_receivePeriodicCheck(u8 *data_ptr);

/**
 * @brief UART write data in the buffer
 * 
 * @param data data to write in the buffer
 */
extern void UART_sendNoBlock(const u8 data);

/**
 * @brief UART read the value in the buffer
 * 
 * @return u8 the value in the buffer
 */
extern u8 UART_receiveNoBlock(void);

/**
 * @brief UART TXC interrupt enable
 * 
 */
extern void UART_TXC_intEnable(void);

/**
 * @brief UART TXC interrupt disable
 * 
 */
extern void UART_TXC_intDisable(void);

/**
 * @brief UART RXC interrupt enable 
 * 
 */
extern void UART_RXC_intEnable(void);

/**
 * @brief UART RXC interrupt disable 
 * 
 */
extern void UART_RXC_intDisable(void);

/**
 * @brief UART buffer empty interrupt enable 
 * 
 */
extern void UART_DEMPTY_intEnable(void);

/**
 * @brief UART buffer empty interrupt disable
 * 
 */
extern void UART_DEMPTY_intDisable(void);

/**
 * @brief UART TXC interrupt set callback 
 * 
 * @param localFptr address of function to run when TXC interrupt occur
 */
extern void UART_TXC_intSetCallBack(void (*localFptr)(void));

/**
 * @brief UART RXC interrupt set call back
 * 
 * @param localFptr address of function to run when RXC interrupt occur.
 */
extern void UART_RXC_intSetCallBack(void (*localFptr)(void));

/**
 * @brief UART buffer empty interrupt set call back
 * 
 * @param localFptr address of function to run when buffer empty interrupt occur.
 */
extern void UART_DEMPTY_intSetCallBack(void (*localFptr)(void));

/**
 * @brief UART configuration struct
 * 
 */
extern const UartConfig uart;

#endif /* UART_H_ */
