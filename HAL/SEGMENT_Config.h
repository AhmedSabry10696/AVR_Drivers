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
 * @brief 	define BCD: LOW_PINS if segment used with decoder in low 4 pins in the port
 *        	define BCD: HIGH_PINS if segment used with decoder in high 4 pins in the port
			define BCD: FULL_PORT if you are using 2 BCD segment 4 lower pins for digit1 and higher 4 pins for digit2
 *        	remove BCD: if segment used without decoder  
 */
#define  BCD	FULL_PORT

/* 7 segment port:  PA / PB / PC / PD */
#define SEGMENT_PORT    PC

/**
 * @brief	define SEGMENT_TYPE: COM_CATHODE with common cathode 7 segment
 *  		define SEGMENT_TYPE: COM_ANODE with common anode 7 segment
 *			remove when using BCD segment	
 */
#ifndef BCD
	#define SEGMENT_TYPE	COM_ANODE
#endif

#endif /* SEGMENT_LCFG_H_ */