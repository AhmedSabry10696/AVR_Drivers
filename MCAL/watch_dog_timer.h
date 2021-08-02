/**
 * @file watch_dog_timer.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Watch dog timer header file
 * @version 0.1
 * @date 15-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef WDT_H_
#define WDT_H_

#include "std_types.h"
#include "memory_map.h"
#include "utils.h"

typedef enum
{
    TIME_OUT_16ms = 0,
    TIME_OUT_32ms,
    TIME_OUT_65ms,
    TIME_OUT_130ms,
    TIME_OUT_260ms,
    TIME_OUT_520ms,
    TIME_OUT_1000ms,
    TIME_OUT_2100ms
} TimeOut_type;

/**
 * @brief set watch dog timer value 
 * 
 * @param time time to set watch dog timer with
 *  TIME_OUT_16ms/TIME_OUT_32ms/TIME_OUT_65ms/TIME_OUT_130ms
 *  TIME_OUT_260ms/TIME_OUT_520ms/TIME_OUT_1000ms/TIME_OUT_2100ms 
 */
extern void WDT_set(const TimeOut_type time);

/**
 * @brief Stop watch dog timer
 * 
 */
extern void WDT_stop(void);

#endif /* WDT_H_ */