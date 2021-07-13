/**
 * @file Uart_Config.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Uart configuration file
 * @version 0.1
 * @date 13-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "Uart.h"

/**
 * @brief   Configuration struct for Uart with FCPU= 8 MHZ
 * 
 * @parity  NO_PARITY,EVEN_PARITY,ODD_PARITY 
 * 
 * @stop    ONE_STOP_BIT,TWO_STOP_BIT
 * 
 * @data    FIVE_BIT_DATA,SIX_BIT_DATA,SEVEN_BIT_DATA,
 *          EIGHT_BIT_DATA,NINE_BIT_DATA
 *
 * @baud    BAUD_2400,BAUD_4800,BAUD_9600,
 *          BAUD_14400,BAUD_19200,BAUD_28800,
 *          BAUD_38400,BAUD_75600,BAUD_76800,
 *          BAUD_115200,BAUD_230400,BAUD_250000,
 *          BAUD_500000,BAUD_1000000
 */
const Uart_Config uart = 
{
    NO_PARITY,
    ONE_STOP_BIT,
    EIGHT_BIT_DATA,
    BAUD_9600
};