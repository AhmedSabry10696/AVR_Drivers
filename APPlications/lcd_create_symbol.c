/**
 * @file lcd_create_symbol.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Man and arrow symbol to create in lcd
 * @version 0.1
 * @date 03-08-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "lcd.h"

u8 MAN[] = {
	0x0E,
	0x0E,
	0x04,
	0x1F,
	0x0E,
	0x0E,
	0x0A,
	0x0A
};

u8 ARROW[] = {
	0x00,
	0x00,
	0x02,
	0x1F,
	0x02,
	0x00,
	0x00,
	0x00
};                  
