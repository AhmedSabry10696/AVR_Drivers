/**
 * @file Ext_Interrupt.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief External Interrupt header file
 * @version 0.1
 * @date 24-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

/**
 * @brief External Interrupt sources 
 * 
 */
typedef enum
{
	EX_INT0 = 0,
	EX_INT1,
	EX_INT2
} ExInterruptSource_type;

/**
 * @brief External Interrupt Events
 * 
 */
typedef enum
{
	LOW_LEVEL = 0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE,
} TriggerEdge_type;

/**
 * @brief External Interrupt Enable
 * 
 * @param Interrupt EX_INT0 - EX_INT1 - EX_INT2
 */
extern void EXI_Enable(ExInterruptSource_type Interrupt);

/**
 * @brief External Interrupt Disable
 * 
 * @param Interrupt EX_INT0 - EX_INT1 - EX_INT2
 */
extern void EXI_Disable(ExInterruptSource_type Interrupt);

/**
 * @brief External Interrupt configure edge
 * 
 * @param Interrupt EX_INT0 - EX_INT1 - EX_INT2
 * @param Edge 	LOW_LEVEL - ANY_LOGIC_CHANGE - FALLING_EDGE - RISING_EDGE
 */
extern void EXI_TriggerEdge(ExInterruptSource_type Interrupt, TriggerEdge_type Edge);

/**
 * @brief External Interrupt Set callback function
 * 
 * @param Interrupt EX_INT0 - EX_INT1 - EX_INT2
 * @param LocalPtr void function(void) to be performed when interrupt fired 
 */
extern void EXI_SetCallBack(ExInterruptSource_type Interrupt, void (*LocalPtr)(void));

#endif /* EXT_INTERRUPT_H_ */