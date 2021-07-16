/**
 * @file Timer_Services.h
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Timer1 Services header file
 * @version 0.1
 * @date 03-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TIMER_SERVICES_H_
#define TIMER_SERVICES_H_

#include "Timer.h"

/**
 * @brief Init timer1 as fast pwm and scaler = 8 
 *        non inerting OCRA , OCRB disconnected
 *        ICR1 TOP
 */
extern void PWM_Init(void);
/**
 * @brief set duty cycle for PWM
 * @note  must specify frequency before calling this function
 * @param duty 0:100
 */
extern void PWM_Duty(const u16 duty);
/**
 * @brief Set PWM frequency in HZ
 * 
 * @param freq required frequency in HZ
 */
extern void PWM_Freq_HZ(const u16 freq);
/**
 * @brief Set PWM frequency in KHZ
 * 
 * @param freq required frequency in KHZ
 */
extern void PWM_Freq_KHZ(const u16 freq);

/**
 * @brief Set interrupt time in us and call function at this time
 * 
 * @param time time in us
 * @param LocalFptr address of function to call at this time
 */
extern void Timer1_SetIntTime_us (const u16 time,void(*LocalFptr)(void));
/**
 * @brief Set interrupt time in ms and call function at this time
 * 
 * @param time time in ms
 * @param LocalFptr address of function to call at this time
 */
extern void Timer1_SetIntTime_ms (const u16 time,void(*LocalFptr)(void));
/**
 * @brief Set interrupt time in s and call function at this time
 * 
 * @param time time in seconds
 * @param LocalFptr address of function to call at this time
 */
extern void Timer1_SetIntTime_s (const u16 time,void(*LocalFptr)(void));

/**
 * @brief measure PWM frequency and duty cycle (blocked)
 * 
 * @param Pfreq address to store PWM frequency
 * @param Pduty address to store PWM duty
 */
extern void PWM_Measure(u32* Pfreq,u8* Pduty);
/**
 * @brief Init ICU to start measure PWM (no block)
 * 
 */
extern void PMW_StartMeasure(void);
/**
 * @brief Get PWM frequency and duty cycle (no block)
 * 
 * @param Pfreq address to store PWM frequency
 * @param Pduty address to store PWM duty cycle
 * @return u8 result 0: if ICU not finished yet 1:if ICU finished
 */
extern u8 PWM_GetRead(u32 *Pfreq, u8 *Pduty);

#endif /* TIMER_SERVICES_H_ */