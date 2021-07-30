/**
 * @file Timer.h
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

#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"

typedef enum
{
	TIMER0_NORMAL = 0,
	TIMER0_PWM_PHASE_CORRECT,
	TIMER0_CTC,
	TIMER0_FAST_PWM
} TIMER0_Mode_type;
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
} TIMER0_Scaler_type;
typedef enum
{
	OC0_DISCONNECTED = 0,
	OC0_TOGGLE,
	OC0_NON_INVERTING,
	OC0_INVERTING
} TIMER0_OC0_type;

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
} TIMER1_Scaler_type;
typedef enum
{
	TIMER1_NORMAL_MODE = 0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE
} TIMER1_Mode_type;
typedef enum
{
	OCRA_DISCONNECTED = 0,
	OCRA_TOGGLE,
	OCRA_NON_INVERTING,
	OCRA_INVERTING
} TIMER1_OC1A_type;
typedef enum
{
	OCRB_DISCONNECTED = 0,
	OCRB_TOGGLE,
	OCRB_NON_INVERTING,
	OCRB_INVERTING

} TIMER1_OC1B_type;
typedef enum
{
	RISING,
	FALLING
} TIMER1_ICU_Edge_type;

/**
 * @brief Timer0 initialization 
 * 
 * @param mode TIMER0_NORMAL/TIMER0_PWM_PHASE_CORRECT/TIMER0_CTC/TIMER0_FAST_PWM
 * @param scaler TIMER0_STOP/TIMER0_SCALER_1/TIMER0_SCALER_8
    TIMER0_SCALER_64/TIMER0_SCALER_256/TIMER0_SCALER_1024
    EXT_CLK_T0_FALLING/EXT_CLK_T0_RISING
 */
extern void Timer0_Init(TIMER0_Mode_type mode, TIMER0_Scaler_type scaler);
/**
 * @brief Timer0 OC0 pin mode
 * 
 * @param mode OC0_DISCONNECTED/OC0_TOGGLE/OC0_NON_INVERTING/OC0_INVERTING
 */
extern void Timer0_OC0_Mode(TIMER0_OC0_type mode);

/**
 * @brief Set TCNT0 value
 * 
 * @param time 0:255
 */
extern void Timer0_Set(const u8 time);
/**
 * @brief Get TCNT0 value
 * 
 * @return u8 0:255
 */
extern u8 Timer0_Get(void);
/**
 * @brief Set OCR register value
 * 
 * @param time 0:255
 */
extern void Timer0_OCR_Set(const u8 time);

/**
 * @brief Enable interrupt for T0 overflow
 * 
 */
extern void Timer0_OVF_IntEnable(void);
/**
 * @brief Disable interrupt for T0 overflow
 * 
 */
extern void Timer0_OVF_IntDisable(void);
/**
 * @brief Enable interrupt for T0 out compare match
 * 
 */
extern void Timer0_OC_IntEnable(void);
/**
 * @brief Disable interrupt for T0 out compare match
 * 
 */
extern void Timer0_OC_IntDisable(void);

/**
 * @brief set call back function for T0 overflow interrupt
 * 
 * @param LocalFptr address of function to run on interrupt
 */
extern void Timer0_OVF_IntSetCallBack(void (*LocalFptr)(void));
/**
 * @brief Set call back function for T0 out compare match interrupt
 * 
 * @param LocalFptr address of function to run on interrupt
 */
extern void Timer0_OC_IntSetCallBack(void (*LocalFptr)(void));

/**
 * @brief Timer1 initialization
 * 
 * @param mode TIMER1_NORMAL_MODE/TIMER1_CTC_ICR_TOP_MODE/TIMER1_CTC_OCRA_TOP_MODE
	TIMER1_FASTPWM_ICR_TOP_MODE/TIMER1_FASTPWM_OCRA_TOP_MODE
 * @param scaler TIMER1_STOP/TIMER1_SCALER_1/TIMER1_SCALER_8/TIMER1_SCALER_64
	TIMER1_SCALER_256/TIMER1_SCALER_1024/EXT_CLK_T1_FALLING/EXT_CLK_T1_RISING
 */
extern void Timer1_Init(TIMER1_Mode_type mode, TIMER1_Scaler_type scaler);
/**
 * @brief Set oc1a pin mode
 * 
 * @param oc1a_mode OCRA_DISCONNECTED/OCRA_TOGGLE/OCRA_NON_INVERTING/OCRA_INVERTING
 */
extern void Timer1_OCRA_Mode(TIMER1_OC1A_type oc1a_mode);
/**
 * @brief Set oc1b pin mode
 * 
 * @param oc1b_mode OCRB_DISCONNECTED/OCRB_TOGGLE/OCRB_NON_INVERTING/OCRB_INVERTING
 */
extern void Timer1_OCRB_Mode(TIMER1_OC1B_type oc1b_mode);
/**
 * @brief Set edge for input capture unit in timer1
 * 
 * @param edge RISING/FALLING
 */
extern void Timer1_InputCaptureEdge(TIMER1_ICU_Edge_type edge);

/**
 * @brief Set timer1 value
 * 
 * @param time 0:65535
 */
extern void Timer1_Set(const u16 time);
/**
 * @brief Get timer1 value
 * 
 * @return u16 0:65535
 */
extern u16 Timer1_Get(void);
/**
 * @brief Set OCRA register value
 * 
 * @param time 0:65535
 */
extern void Timer1_OCRA_Set(const u16 time);
/**
 * @brief Set OCRB register value
 * 
 * @param time 0:65535
 */
extern void Timer1_OCRB_Set(const u16 time);
/**
 * @brief Set ICR register value
 * 
 * @param time 0:65535
 */
extern void Timer1_ICR_Set(const u16 time);
/**
 * @brief Get ICR1 register value
 * 
 * @return u16 0:65535
 */
extern u16 Timer1_ICR_Get(void);

/**
 * @brief Enable Timer1 overflow interrupt
 * 
 */
extern void Timer1_OVF_IntEnable(void);
/**
 * @brief Disable Timer1 overflow interrupt
 * 
 */
extern void Timer1_OVF_IntDisable(void);
/**
 * @brief Enable OCA interrupt of Timer1
 * 
 */
extern void Timer1_OCA_IntEnable(void);
/**
 * @brief Disable OCA interrupt of Timer1
 * 
 */
extern void Timer1_OCA_IntDisable(void);
/**
 * @brief Enable OCB interrupt for Timer1
 * 
 */
extern void Timer1_OCB_IntEnable(void);
/**
 * @brief Disable OCB interrupt for Timer1
 * 
 */
extern void Timer1_OCB_IntDisable(void);
/**
 * @brief Enable input capture interrupt
 * 
 */
extern void Timer1_ICU_IntEnable(void);
/**
 * @brief Disable input capture interrupt
 * 
 */
extern void Timer1_ICU_IntDisable(void);

/**
 * @brief Set call back function for T1 overflow interrupt 
 * 
 * @param LocalFptr Address of function to run on interrupt 
 */
extern void Timer1_OVF_IntSetCallBack(void (*LocalFptr)(void));
/**
 * @brief Set call back function of OCA interrupt of timer1
 * 
 * @param LocalFptr Address to function to run on OCA interrupt
 */
extern void Timer1_OCA_IntSetCallBack(void (*LocalFptr)(void));
/**
 * @brief Set call back function for OCB interrupt
 * 
 * @param LocalFptr Address of function to run on OCB interrupt
 */
extern void Timer1_OCB_IntSetCallBack(void (*LocalFptr)(void));
/**
 * @brief Set call back function for input capture interrupt
 * 
 * @param LocalFptr address to function to run on input capture interrupt
 */
extern void Timer1_ICU_IntSetCallBack(void (*LocalFptr)(void));

#endif /* TIMER_H_ */