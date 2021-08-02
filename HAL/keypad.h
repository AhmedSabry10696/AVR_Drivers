/**
 * @file keypad.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief keypad header file
 * @version 0.1
 * @date 17-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "dio.h"

/* keypad connections */
#define FIRST_INPUT PINA0
#define FIRST_OUTPUT PINA4

/* number of rows and cols */
#define ROW 4
#define COL 4

#define NO_KEY '.'

/**
 * @brief get the pressed key from keypad
 * 
 * @return u8 pressed key or NO_KEY ('.') if no button pressed 
 */
extern u8 KEYPAD_getKey(void);

#endif /* KEYPAD_H_ */
