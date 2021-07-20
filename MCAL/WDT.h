/**
 * @file WDT.h
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

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

typedef enum
{
    TimeOut_16ms=0,
    TimeOut_32ms,
    TimeOut_65ms,
    TimeOut_130ms,
    TimeOut_260ms,
    TimeOut_520ms,
    TimeOut_1000ms,
    TimeOut_2100ms 
}TimeOut_type;

extern void WDT_Set(const TimeOut_type time);
extern void WDT_Stop(void);

#endif