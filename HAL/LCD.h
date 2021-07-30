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

#ifndef LCD_H_
#define LCD_H_

#define F_CPU 8000000UL
#include <util/delay.h>
#include "DIO.h"

/* LCD Data bits mode configuration: 8 or 4 */
#define DATA_BITS_MODE 8

/* LCD Data bits */
#if (8 == DATA_BITS_MODE)
#define LCD_DATA_PORT PD

#elif (4 == DATA_BITS_MODE)
#define D4 PINA4
#define D5 PINA5
#define D6 PINA6
#define D7 PINA7
#endif

/* LCD control Pins */
#define E PINA7
#define RW PINA6
#define RS PINA5

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
extern void LCD_WriteChar(const u8 ch);

/**
 * @brief display string on lcd
 * 
 * @param str string to display
 */
extern void LCD_WriteString(const u8 *str);

/**
 * @brief go to specific row and column in lcd display
 * 
 * @param row 
 * @param col 
 */
extern void LCD_GoTo(u8 row, u8 col);

/**
 * @brief display string at specific row and column
 * 
 * @param row row of beginning to display
 * @param col col of beginning to display 
 * @param str string to display
 */
extern void LCD_WriteStringRowCol(u8 row, u8 col, const u8 *str);

/**
 * @brief convert num to string and display it on lcd
 * 
 * @param data integer data to display on lcd
 */
extern void LCD_WriteNum(s32 num);

/**
 * @brief create special char on lcd
 * 
 * @param Pattern array contains the pattern of special char
 * @param Location location to store this pattern in lcd
 */
extern void LCD_Create_Char(const u8 *Pattern, const u8 Location);

/**
 * @brief display binary representation of num
 * 
 * @param num number to display
 */
extern void LCD_WriteBinary(u16 num);

/**
 * @brief write hex of value of the number
 * 
 * @param num decimal number
 */
extern void LCD_WriteHex(u16 num);

/**
 * @brief display float numbers on lcd
 * 
 * @param num float number to display
 */
extern void LCD_WriteFloat(f32 num);

/**
 * @brief clear cells on lcd and return again to row and col
 * 
 * @param row row to start from
 * @param col col to start from
 * @param cell numbers of cells to clear
 */
extern void LCD_ClearCells(u8 row, u8 col, u8 cell);

#endif /* LCD_H_ */