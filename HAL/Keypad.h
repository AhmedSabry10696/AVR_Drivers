/**
 * @file Keypad.h
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

#include "DIO_Interface.h"

#define FIRST_INPUT  PINA0
#define FIRST_OUTPUT PINA4 

#define ROW 4 
#define COL 4
#define NO_KEY  '.'


extern u8 KEYPAD_GeyKey(void);

#endif /* KEYPAD_H_ */