/**
 * @file i2c.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief I2C header file
 * @version 0.1
 * @date 28-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"
#include "utils.h"
#include "memory_map.h"

typedef enum
{
	TWI_OK,
	TWI_SC_ERROR,
	TWI_RSC_ERROR,
	TWI_MT_SLA_W_ERROR,
	TWI_MR_SLA_R_ERROR,
	TWI_MT_Data_ERROR,
	TWI_MR_Data_ERROR
} TwiError_type;

/* I2C Status Bits in the TWSR Register */
/* start condition transmitted */
#define TW_START 0x08
/* repeated start condition transmitted */
#define TW_REP_START 0x10
/* SLA+W transmitted, ACK received */
#define TW_MT_SLA_W_ACK 0x18
/* SLA+W transmitted, NACK received */
#define TW_MT_SLA_NACK 0x20
/* data transmitted, ACK received */
#define TW_MT_DATA_ACK 0x28
/* data transmitted, NACK received */
#define TW_MT_DATA_NACK 0x30
/* arbitration lost in SLA+W or NACK */
#define TW_MT_ARB_LOST 0x38
/* arbitration lost in SLA+R or data */
#define TW_MR_ARB_LOST 0x38
/* SLA+R transmitted, ACK received */
#define TW_MT_SLA_R_ACK 0x40
/* SLA+R transmitted, NACK received */
#define TW_MR_SLA_NACK 0x48
/* data received, ACK returned */
#define TW_MR_DATA_ACK 0x50
/* data received, NACK returned */
#define TW_MR_DATA_NACK 0x58
/* SLA+R received, ACK returned */
#define TW_ST_SLA_ACK 0xA8
/* arbitration lost in SLA+RW, SLA+R received, ACK returned */
#define TW_ST_ARB_LOST_SLA_ACK 0xB0
/* data transmitted, ACK received */
#define TW_ST_DATA_ACK 0xB8
/* data transmitted, NACK received */
#define TW_ST_DATA_NACK 0xC0
/* last data byte transmitted, ACK received */
#define TW_ST_LAST_DATA 0xC8
/* SLA+W received, ACK returned */
#define TW_SR_SLA_ACK 0x60
/* arbitration lost in SLA+RW, SLA+W received, ACK returned */
#define TW_SR_ARB_LOST_SLA_ACK 0x68
/* general call received, ACK returned */
#define TW_SR_GCALL_ACK 0x70
/* arbitration lost in SLA+RW, general call received, ACK returned */
#define TW_SR_ARB_LOST_GCALL_ACK 0x78
/* data received, ACK returned */
#define TW_SR_DATA_ACK 0x80
/* data received, NACK returned */
#define TW_SR_DATA_NACK 0x88
/* general call data received, ACK returned */
#define TW_SR_GCALL_DATA_ACK 0x90
/* general call data received, NACK returned */
#define TW_SR_GCALL_DATA_NACK 0x98
/* stop or repeated start condition received while selected */
#define TW_SR_STOP 0xA0
/* no state information available */
#define TW_NO_INFO 0xF8
/* illegal start or stop condition */
#define TW_BUS_ERROR 0x00

#define TW_STATUS_MASK 0xF8
#define TW_STATUS (TWSR & TW_STATUS_MASK)

#define TW_R 1
#define TW_W 0

/**
 * @brief TWI Initialization with clk {400 KHZ}
 * 
 * @param address slave address {7 bit address}
 */
extern void TWI_init(u8 address);

/**
 * @brief TWI send start condition
 * 
 * @return TWI_Error_type TWI_OK/TWI_SC_ERROR
 */
extern TwiError_type TWI_start(void);

/**
 * @brief TWI send repeated start condition 
 * 
 * @return TWI_Error_type TWI_OK/TWI_RSC_ERROR
 */
extern TwiError_type TWI_repStart(void);

/**
 * @brief TWI send slave address with write request
 * 
 * @param address slave addres {7 bit}
 * @return TWI_Error_type TWI_OK/TWI_MT_SLA_W_ERROR
 */
extern TwiError_type TWI_write_SLA_write(u8 address);

/**
 * @brief TWI send slave address with read request
 * 
 * @param address slave addres {7 bit}
 * @return TWI_Error_type TWI_OK/TWI_MR_SLA_R_ERROR
 */
extern TwiError_type TWI_write_SLA_read(u8 address);

/**
 * @brief TWI master send byte
 * 
 * @param data byte to send
 * @return TWI_Error_type TWI_OK/TWI_MT_Data_ERROR
 */
extern TwiError_type TWI_writeByte(u8 data);

/**
 * @brief TWI master read byte
 * 
 * @param data pointer to received data
 * @return TWI_Error_type TWI_OK/TWI_MR_Data_ERROR
 */
extern TwiError_type TWI_readByte(u8 *data_ptr);

/**
 * @brief TWI send stop condition
 * 
 */
extern void TWI_stop(void);

/**
 * @brief TWI listen for the flag {polling}
 * 
 */
extern void TWI_listen(void);

/**
 * @brief TWI interrupt enable
 * 
 */
extern void TWI_intEnable(void);

/**
 * @brief TWI interrupt disable
 * 
 */
void TWI_intDisable(void);

/**
 * @brief TWI interrupt set call back
 * 
 * @param LocalFptr pointer to function to call when interrupt occurred
 */
extern void TWI_intSetCallBack(void (*localFptr)(void));

#endif /* I2C_H_ */
