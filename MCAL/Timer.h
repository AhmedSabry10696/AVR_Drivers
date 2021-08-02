/**
 * @file timer.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Timer header file
 * @version 0.1
 * @date 28-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"
#include "utils.h"
#include "memory_map.h"

typedef enum
{
	TIMER0_NORMAL = 0,
	TIMER0_PWM_PHASE_CORRECT,
	TIMER0_CTC,
	TIMER0_FAST_PWM
} Timer0Mode_type;

typedef enum
{
	TIMER0_STOP = 0,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
	EXT_CLK_T0_FALLING,
	EXT_CLK_T0_RISING
} Timer0Scaler_type;

typedef enum
{
	OC0_DISCONNECTED = 0,
	OC0_TOGGLE,
	OC0_NON_INVERTING,
	OC0_INVERTING
} Timer0_oc0_type;

typedef enum
{
	TIMER1_STOP = 0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXT_CLK_T1_FALLING,
	EXT_CLK_T1_RISING
} Timer1Scaler_type;

typedef enum
{
	TIMER1_NORMAL_MODE = 0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE
} Timer1Mode_type;

typedef enum
{
	OCRA_DISCONNECTED = 0,
	OCRA_TOGGLE,
	OCRA_NON_INVERTING,
	OCRA_INVERTING
} Timer1_oc1a_type;

typedef enum
{
	OCRB_DISCONNECTED = 0,
	OCRB_TOGGLE,
	OCRB_NON_INVERTING,
	OCRB_INVERTING
} Timer1_oc1b_type;

typedef enum
{
	RISING,
	FALLING
} Timer1_icuEdge_type;

/**
 * @brief Timer0 initialization 
 * 
 * @param mode TIMER0_NORMAL/TIMER0_PWM_PHASE_CORRECT/TIMER0_CTC/TIMER0_FAST_PWM
 * @param scaler TIMER0_STOP/TIMER0_SCALER_1/TIMER0_SCALER_8
    TIMER0_SCALER_64/TIMER0_SCALER_256/TIMER0_SCALER_1024
    EXT_CLK_T0_FALLING/EXT_CLK_T0_RISING
 */
extern void TIMER0_init(Timer0Mode_type mode, Timer0Scaler_type scaler);
/**
 * @brief Timer0 OC0 pin mode
 * 
 * @param mode OC0_DISCONNECTED/OC0_TOGGLE/OC0_NON_INVERTING/OC0_INVERTING
 */
extern void TIMER0_OC0_mode(Timer0_oc0_type mode);

/**
 * @brief Set TCNT0 value
 * 
 * @param time 0:255
 */
extern void TIMER0_set(const u8 time);
/**
 * @brief Get TCNT0 value
 * 
 * @return u8 0:255
 */
extern u8 TIMER0_get(void);
/**
 * @brief Set OCR register value
 * 
 * @param time 0:255
 */
extern void TIMER0_OCR_set(const u8 time);

/**
 * @brief Enable interrupt for T0 overflow
 * 
 */
extern void TIMER0_OVF_intEnable(void);
/**
 * @brief Disable interrupt for T0 overflow
 * 
 */
extern void TIMER0_OVF_intDisable(void);
/**
 * @brief Enable interrupt for T0 out compare match
 * 
 */
extern void TIMER0_OC_intEnable(void);
/**
 * @brief Disable interrupt for T0 out compare match
 * 
 */
extern void TIMER0_OC_intDisable(void);

/**
 * @brief set call back function for T0 overflow interrupt
 * 
 * @param localFptr address of function to run on interrupt
 */
extern void TIMER0_OVF_intSetCallBack(void (*localFptr)(void));
/**
 * @brief Set call back function for T0 out compare match interrupt
 * 
 * @param localFptr address of function to run on interrupt
 */
extern void TIMER0_OC_intSetCallBack(void (*localFptr)(void));

/**
 * @brief Timer1 initialization
 * 
 * @param mode TIMER1_NORMAL_MODE/TIMER1_CTC_ICR_TOP_MODE/TIMER1_CTC_OCRA_TOP_MODE
	TIMER1_FASTPWM_ICR_TOP_MODE/TIMER1_FASTPWM_OCRA_TOP_MODE
 * @param scaler TIMER1_STOP/TIMER1_SCALER_1/TIMER1_SCALER_8/TIMER1_SCALER_64
	TIMER1_SCALER_256/TIMER1_SCALER_1024/EXT_CLK_T1_FALLING/EXT_CLK_T1_RISING
 */
extern void TIMER1_init(Timer1Mode_type mode, Timer1Scaler_type scaler);
/**
 * @brief Set oc1a pin mode
 * 
 * @param oc1a_mode OCRA_DISCONNECTED/OCRA_TOGGLE/OCRA_NON_INVERTING/OCRA_INVERTING
 */
extern void TIMER1_OCRA_mode(Timer1_oc1a_type oc1a_mode);
/**
 * @brief Set oc1b pin mode
 * 
 * @param oc1b_mode OCRB_DISCONNECTED/OCRB_TOGGLE/OCRB_NON_INVERTING/OCRB_INVERTING
 */
extern void TIMER1_OCRB_mode(Timer1_oc1b_type oc1b_mode);
/**
 * @brief Set edge for input capture unit in timer1
 * 
 * @param edge RISING/FALLING
 */
extern void TIMER1_inputCaptureEdge(Timer1_icuEdge_type edge);

/**
 * @brief Set timer1 value
 * 
 * @param time 0:65535
 */
extern void TIMER1_set(const u16 time);
/**
 * @brief Get timer1 value
 * 
 * @return u16 0:65535
 */
extern u16 TIMER1_get(void);
/**
 * @brief Set OCRA register value
 * 
 * @param time 0:65535
 */
extern void TIMER1_OCRA_set(const u16 time);
/**
 * @brief Set OCRB register value
 * 
 * @param time 0:65535
 */
extern void TIMER1_OCRB_set(const u16 time);
/**
 * @brief Set ICR register value
 * 
 * @param time 0:65535
 */
extern void TIMER1_ICR_set(const u16 time);
/**
 * @brief Get ICR1 register value
 * 
 * @return u16 0:65535
 */
extern u16 TIMER1_ICR_get(void);

/**
 * @brief Enable Timer1 overflow interrupt
 * 
 */
extern void TIMER1_OVF_intEnable(void);
/**
 * @brief Disable Timer1 overflow interrupt
 * 
 */
extern void TIMER1_OVF_intDisable(void);
/**
 * @brief Enable OCA interrupt of Timer1
 * 
 */
extern void TIMER1_OCA_intEnable(void);
/**
 * @brief Disable OCA interrupt of Timer1
 * 
 */
extern void TIMER1_OCA_intDisable(void);
/**
 * @brief Enable OCB interrupt for Timer1
 * 
 */
extern void TIMER1_OCB_intEnable(void);
/**
 * @brief Disable OCB interrupt for Timer1
 * 
 */
extern void TIMER1_OCB_intDisable(void);
/**
 * @brief Enable input capture interrupt
 * 
 */
extern void TIMER1_ICU_intEnable(void);
/**
 * @brief Disable input capture interrupt
 * 
 */
extern void TIMER1_ICU_intDisable(void);

/**
 * @brief Set call back function for T1 overflow interrupt 
 * 
 * @param localFptr Address of function to run on interrupt 
 */
extern void TIMER1_OVF_intSetCallBack(void (*localFptr)(void));
/**
 * @brief Set call back function of OCA interrupt of timer1
 * 
 * @param localFptr Address to function to run on OCA interrupt
 */
extern void TIMER1_OCA_intSetCallBack(void (*localFptr)(void));
/**
 * @brief Set call back function for OCB interrupt
 * 
 * @param localFptr Address of function to run on OCB interrupt
 */
extern void TIMER1_OCB_intSetCallBack(void (*localFptr)(void));
/**
 * @brief Set call back function for input capture interrupt
 * 
 * @param localFptr address to function to run on input capture interrupt
 */
extern void TIMER1_ICU_intSetCallBack(void (*localFptr)(void));

#endif /* TIMER_H_ */