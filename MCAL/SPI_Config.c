/**
 * @file SPI_Config.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief SPI configuration file
 * @version 0.1
 * @date 26-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "SPI.h"

/**
 * @brief spi configuration struct 

 * @data_order LSB_FIRST/MSB_FIRST

 * @type SLAVE/MASTER

 * @clock_pol LEADING_EDGE_RISING/LEADING_EDGE_FALLING

 * @clock_phase SETUP_LEADING/SETUP_TRAILING

 * @clock_speed FCPU_DIV_2/FCPU_DIV_4/FCPU_DIV_8/FCPU_DIV_16/
                FCPU_DIV_32/FCPU_DIV_64/FCPU_DIV_128
*/

/**
 * @note PINS CONFIG for SPI in DIO_Config.c
 * 
 * @master MISO {input by default}, MOSI/SCK/SS is user defined {DIO_Config.c}
 * 
 * @slave MOSI/SCK/SS {input by default}, MISO is user defined {DIO_Config.c}
 */

const SPI_Config spi =
{
    LSB_FIRST,
    MASTER,
    LEADING_EDGE_RISING,
    SETUP_LEADING,
    FCPU_DIV_8
};