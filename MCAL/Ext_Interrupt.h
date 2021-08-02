/**
 * @file ext_interrupt.h
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

#include "std_types.h"
#include "memory_map.h"
#include "utils.h"

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
 * @param interrupt EX_INT0 - EX_INT1 - EX_INT2
 */
extern void EXI_enable(ExInterruptSource_type interrupt);

/**
 * @brief External Interrupt Disable
 * 
 * @param interrupt EX_INT0 - EX_INT1 - EX_INT2
 */
extern void EXI_disable(ExInterruptSource_type interrupt);

/**
 * @brief External Interrupt configure edge
 * 
 * @param interrupt EX_INT0 - EX_INT1 - EX_INT2
 * @param edge 	LOW_LEVEL - ANY_LOGIC_CHANGE - FALLING_EDGE - RISING_EDGE
 */
extern void EXI_triggerEdge(ExInterruptSource_type interrupt, TriggerEdge_type edge);

/**
 * @brief External Interrupt Set callback function
 * 
 * @param interrupt EX_INT0 - EX_INT1 - EX_INT2
 * @param localPtr void function(void) to be performed when interrupt fired 
 */
extern void EXI_setCallBack(ExInterruptSource_type interrupt, void (*localPtr)(void));

#endif /* EXT_INTERRUPT_H_ */