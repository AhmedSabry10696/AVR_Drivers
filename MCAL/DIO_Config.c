/**
 * @file DIO_Config.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief DIO configuration file
 * @version 0.1
 * @date 25-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "DIO.h"

const DIO_PinStatus_type PinsStatus[TOTAL_PINS] = 
{
    /* PORTA PINS 0:7*/
    OUTPUT, /* ADC0 */
    OUTPUT, /* ADC1 */
    OUTPUT, /* ADC2 */
    OUTPUT, /* ADC3 */
    OUTPUT, /* ADC4 */
    OUTPUT, /* ADC5 */
    OUTPUT, /* ADC6 */
    OUTPUT, /* ADC7 */

    /* PORTB PINS 0:7*/
    OUTPUT, /* XCK/T0 {usart}/{T0 pin ext clock/counter} */
    OUTPUT, /* T1     {T1 pin ext clock/counter} */
    OUTPUT, /* INT2   {external interrupt 2} */
    OUTPUT, /* OC0    {output compare pin T0} */
    OUTPUT, /* SS     {SPI} */
    OUTPUT, /* MOSI   {SPI} */
    INFREE, /* MISO   {SPI} */ 
    OUTPUT, /* SCK    {SPI} */

    /* PORTC PINS 0:7*/    
    INFREE, /* SCL {I2C} */
    INFREE, /* SDA {I2C} */
    OUTPUT, /* TCK */
    OUTPUT, /* TMS */
    OUTPUT, /* TDO */
    OUTPUT, /* TDI */
    OUTPUT, /* TOSC1  {T2} */
    OUTPUT, /* TOSC2  {T2} */

    /* PORTD PINS 0:7*/
    OUTPUT, /* RXD  {uart INFREE} */
    OUTPUT, /* TXD  {uart OUTPUT} */
    OUTPUT, /* INT0 {external interrupt 0} */
    OUTPUT, /* INT1 {external interrupt 1} */
    OUTPUT, /* OC1B {output compare B T1} */ 
    OUTPUT, /* OC1A {output compare A T1} */
    OUTPUT, /* ICP1 {input capture pin T1} */
    OUTPUT  /* OC2  {output compare pin T2} */
};