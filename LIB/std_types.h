/**
 * @file StdTypes.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Standard types header file
 * @version 0.1
 * @date 24-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef STDTYPES_H_
#define STDTYPES_H_

/* Null Pointer */
#define NULLPTR ((void *)0)

/* unsigned data types */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

/* signed data types */
typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;

/* float data types */
typedef float f32;
typedef double f64;

/* boolean data types */
typedef enum
{
	FALSE = 0,
	TRUE = 1
} Bool_type;

/* register data type */
typedef union
{
	u8 Data;
	struct
	{
		u8 BIT0 : 1;
		u8 BIT1 : 1;
		u8 BIT2 : 1;
		u8 BIT3 : 1;
		u8 BIT4 : 1;
		u8 BIT5 : 1;
		u8 BIT6 : 1;
		u8 BIT7 : 1;
	} BITS; /* share the same values that is in Data var */
} Reg_8bit;

#endif /* STDTYPES_H_ */