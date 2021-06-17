/**
 * @file Utils.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Utils header file
 * @version 0.1
 * @date 24-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UTILS_H_
#define UTILS_H_

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) (REG= (REG>>num)|(REG<<(8-num)))

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) (REG= (REG<<num)|(REG>>(8-num)))

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) (REG&(1<<BIT))

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1<<BIT)))

/* Get specific bit in any register */
#define READ_BIT(REG,BIT) ((REG>>BIT)&0x01)

/* Edit four lower bits in a register without affecting others bits */
#define EDIT_FOUR_LBITS(REG,VALUE) (REG= (REG&0xF0)|(VALUE&0x0F));

/* Edit four higher bits in a register without affecting others bits */
#define EDIT_FOUR_HBITS(REG,VALUE) (REG= (REG&0x0F)|((VALUE<<4)&0xF0));

#endif /* UTILS_H_ */