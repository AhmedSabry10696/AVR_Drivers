/**
 * @file LCD_Interface.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief LCD interface header file
 * @version 0.1
 * @date 16-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define  F_CPU 8000000UL
#include <util/delay.h>
#include "DIO_Interface.h"

/* LCD Data bits mode configuration: 8 or 4 */
#define DATA_BITS_MODE 8

/* LCD Data bits */
#if (DATA_BITS_MODE == 8)
	#define LCD_DATA_PORT PD

#elif (DATA_BITS_MODE == 4)
	#define D4  PINA4
	#define D5  PINA5
	#define D6  PINA6
	#define D7  PINA7
#endif

/* LCD control Pins */
#define E	PINB0
#define RW	PINB1
#define RS	PINB2

/* LCD Commands */
#define CURSOR_ON 0x0E
#define CURSOR_OFF 0x0C
#define CURSOR_BLINK 0x0F
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define SET_CURSOR_LOCATION 0x80
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38 

/**
 * @brief initialize lcd 
 * 
 */
extern void LCD_Init(void);

/**
 * @brief clear lcd display
 * 
 */
extern void LCD_Clear(void);

/**
 * @brief display char on lcd
 * 
 * @param data char to display
 */
extern void LCD_WriteChar(u8 ch);

/**
 * @brief display string on lcd
 * 
 * @param str string to display
 */
extern void LCD_WriteString(u8 *str);

/**
 * @brief go to specific row and column in lcd display
 * 
 * @param row 
 * @param col 
 */
extern void LCD_GoTo(u8 row,u8 col);

/**
 * @brief display string at specific row and column
 * 
 * @param row row of beginning to display
 * @param col col of beginning to display 
 * @param str string to display
 */
extern void LCD_WriteStringRowCol(u8 row,u8 col,u8 *str);

/**
 * @brief convert num to string and display it on lcd
 * 
 * @param data integer data to display on lcd
 */
extern void LCD_WriteNum(s64 num);

/**
 * @brief create special char on lcd
 * 
 * @param Pattern 
 * @param Location 
 */
extern void LCD_Create_Char(u8 *Pattern,u8 Location);

/**
 * @brief display binary representation of num
 * 
 * @param num number to display
 */
extern void LCD_WriteBinary(u8 num);

/**
 * @brief write hex of value of the number
 * 
 * @param num decimal number
 */
extern void LCD_WriteHex(u8 num);

#endif /* LCD_INTERFACE_H_ */