/**
 * @file spi.h
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

#include "std_types.h"
#include "utils.h"
#include "memory_map.h"

typedef enum
{
    LSB_FIRST = 0,
    MSB_FIRST
} DataOrder_type;

typedef enum
{
    SLAVE = 0,
    MASTER
} Spi_type;

typedef enum
{
    LEADING_EDGE_RISING = 0,
    LEADING_EDGE_FALLING
} ClockPolarity_type;

typedef enum
{
    SETUP_LEADING = 0,
    SETUP_TRAILING
} ClockPhase_type;

typedef enum
{
    FCPU_DIV_2 = 0,
    FCPU_DIV_4,
    FCPU_DIV_8,
    FCPU_DIV_16,
    FCPU_DIV_32,
    FCPU_DIV_64,
    FCPU_DIV_128
} ClockSpeed_type;

typedef struct
{
    DataOrder_type data_order;
    Spi_type type;
    ClockPolarity_type clock_pol;
    ClockPhase_type clock_phase;
    ClockSpeed_type clock_speed;
} SpiConfig;

extern const SpiConfig spi;

/**
 * @brief SPI Init based on SPI_Config.c file 
 * 
 */
extern void SPI_init(void);

/**
 * @brief SPI send data from master
 * 
 * @param data data to send 
 * @return u8 received data from slave
 */
extern u8 SPI_sendReceive(u8 data);

/**
 * @brief write data into slave buffer so that when 
 * master send any data this data transmitted to master
 *
 * @param data data to write in slave buffer
 */
extern void SPI_sendNoBlock(u8 data);

/**
 * @brief return received data in slave buffer (call in isr)
 * 
 * @return u8 received data
 */
extern u8 SPI_receiveNoBlock(void);

/**
 * @brief check if there is data received from master then return it
 * @note if slave code is too long received data may be missing 
 *  
 * @param data_ptr pointer to write data if(data received)
 * @return u8 result if there is data {1} or not{0}
 */
extern u8 SPI_receivePeriodic(u8 *data_ptr);

/**
 * @brief SPI interrupt enable
 * 
 */
extern void SPI_intEnable(void);

/**
 * @brief SPI interrupt disable
 * 
 */
extern void SPI_intDisable(void);

/**
 * @brief SET call back function of SPI transmission complete interrupt 
 * 
 * @param localFptr address of function to call when int occurred
 */
extern void SPI_STC_intSetCallBack(void (*localFptr)(void));

#endif /* SPI_H_ */