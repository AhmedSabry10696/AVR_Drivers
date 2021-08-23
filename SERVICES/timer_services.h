/**
 * @file timer_services.h
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

#include "timer.h"

/**
 * @brief Init timer1 as fast pwm and scaler = 8 
 *        non inverting OCRA , OCRB disconnected
 *        ICR1 TOP
 */
extern void PWM_init(void);

/**
 * @brief set duty cycle for PWM
 * @note  must specify frequency before calling this function
 * @param duty 0:100
 */
extern void PWM_duty(const u16 duty);

/**
 * @brief Set PWM frequency in HZ
 * 
 * @param freq required frequency in HZ
 */
extern void PWM_freq_HZ(const u16 freq);

/**
 * @brief Set PWM frequency in KHZ
 * 
 * @param freq required frequency in KHZ
 */
extern void PWM_freq_KHZ(const u16 freq);

/**
 * @brief Set interrupt time in us and call function at this time
 * 
 * @param time time in us
 * @param localFptr address of function to call at this time
 */
extern void Timer1_setIntTime_us(const u16 time, void (*localFptr)(void));

/**
 * @brief Set interrupt time in ms and call function at this time
 * 
 * @param time time in ms
 * @param localFptr address of function to call at this time
 */
extern void Timer1_setIntTime_ms(const u16 time, void (*localFptr)(void));

/**
 * @brief Set interrupt time in s and call function at this time
 * 
 * @param time time in seconds
 * @param localFptr address of function to call at this time
 */
extern void Timer1_setIntTime_s(const u16 time, void (*localFptr)(void));

/**
 * @brief measure PWM frequency and duty cycle (blocked)
 * 
 * @param Pfreq address to store PWM frequency
 * @param Pduty address to store PWM duty
 */
extern void PWM_measure(u32 *freq_ptr, u8 *duty_ptr);

/**
 * @brief Init ICU to start measure PWM (no block)
 * 
 */
extern void PMW_startMeasure(void);

/**
 * @brief Get PWM frequency and duty cycle (no block)
 * 
 * @param freq_ptr address to store PWM frequency
 * @param duty_ptr address to store PWM duty cycle
 * @return u8 result 0: if ICU not finished yet 1:if ICU finished
 */
extern u8 PWM_getRead(u32 *freq_ptr, u8 *duty_ptr);

#endif /* TIMER_SERVICES_H_ */
