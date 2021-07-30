/**
 * @file SPI.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief SPI driver header file
 * @version 0.1
 * @date 26-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SPI_H_
#define SPI_H_

#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"

typedef enum
{
    LSB_FIRST = 0,
    MSB_FIRST
} Data_Order_type;
typedef enum
{
    SLAVE = 0,
    MASTER
} SPI_type;
typedef enum
{
    LEADING_EDGE_RISING = 0,
    LEADING_EDGE_FALLING
} Clock_Polarity_type;
typedef enum
{
    SETUP_LEADING = 0,
    SETUP_TRAILING
} Clock_Phase_type;
typedef enum
{
    FCPU_DIV_2 = 0,
    FCPU_DIV_4,
    FCPU_DIV_8,
    FCPU_DIV_16,
    FCPU_DIV_32,
    FCPU_DIV_64,
    FCPU_DIV_128
} Clock_Speed_type;
typedef struct
{
    Data_Order_type data_order;
    SPI_type type;
    Clock_Polarity_type clock_pol;
    Clock_Phase_type clock_phase;
    Clock_Speed_type clock_speed;
} SPI_Config;
extern const SPI_Config spi;

/**
 * @brief SPI Init based on SPI_Config.c file 
 * 
 */
extern void SPI_Init(void);

/**
 * @brief SPI send data from master
 * 
 * @param data data to send 
 * @return u8 received data from slave
 */
extern u8 SPI_Send_Receive(u8 data);

/**
 * @brief write data into slave buffer so that when 
 * master send any data this data transmitted to master
 *
 * @param data data to write in slave buffer
 */
extern void SPI_Send_NoBlock(u8 data);

/**
 * @brief return received data in slave buffer (call in isr)
 * 
 * @return u8 received data
 */
extern u8 SPI_Receive_NoBlock(void);

/**
 * @brief check if there is data received from master then return it
 * @note if slave code is too long received data may be missing 
 *  
 * @param pdata pointer to write data if(data received)
 * @return u8 result if there is data {1} or not{0}
 */
extern u8 SPI_Receive_Periodic(u8 *pdata);

/**
 * @brief SPI interrupt enable
 * 
 */
extern void SPI_Int_Enable(void);

/**
 * @brief SPI interrupt disable
 * 
 */
extern void SPI_Int_Disable(void);

/**
 * @brief SET call back function of SPI transmission complete interrupt 
 * 
 * @param LocalFptr address of function to call when int occurred
 */
extern void SPI_STC_IntSetCallBack(void (*LocalFptr)(void));

#endif /* SPI_H_ */