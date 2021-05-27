/**
 * @file Segment_Config.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Segment configuration file
 * @version 0.1
 * @date 27-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SEGMENT_LCFG_H_
#define SEGMENT_LCFG_H_

#include "DIO_Interface.h"

/**
 * @brief define BCD: LOW_PINS if segment used with decoder in low 4 pins in the port
 *        define BCD: HIGH_PINS if segment used with decoder in high 4 pins in the port  
 *        remove BCD: if segment used with out decoder  
 */
#define  BCD    HIGH_PINS

/* 7 segment port */
#define SEGMENT_PORT    PB

/**
 * @brief define SEGMENT_TYPE: COM_CATHODE with common cathode 7 segment
 *        define SEGMENT_TYPE: COM_ANODE with common anode 7 segment
 * 
 */
#define SEGMENT_TYPE    COM_ANODE

#endif /* SEGMENT_LCFG_H_ */