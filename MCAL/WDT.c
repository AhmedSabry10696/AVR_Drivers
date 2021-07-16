/**
 * @file WDT.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief watch dog timer driver
 * @version 0.1
 * @date 15-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "WDT.h"

void WDT_Set(const TimeOut_type time)
{
    u8 wdt_value = 0x08;
    wdt_value |= time;
    
    WDTCR |= (1<<WDTOE)|(1<<WDE);
    WDTCR = wdt_value;
}
void WDT_Stop(void)
{
    WDTCR = (1<<WDTOE)|(1<<WDE);

    cli();
    /* with in only 4 cycles write 0 */
    WDTCR = 0;
    sei();
}