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
}TIMER0_Mode_type;

typedef enum
{
    TIMER0_STOP = 0,
    TIMER0_SCALER_1,
    TIMER0_SCALER_8,
    TIMER0_SCALER_64,
    TIMER0_SCALER_256,
    TIMER0_SCALER_1024,
    External_Clk_T0_FALLING,
    External_Clk_T0_RISING
}TIMER0_Scaler_type;

typedef enum 
{
    OC0_DISCONNECTED = 0,
    OC0_TOGGLE,
    OC0_NON_INVERTING,
    OC0_INVERTING
}TIMER0_OC0_type;

extern void Timer0_Init(TIMER0_Mode_type mode,TIMER0_Scaler_type scaler);
extern void Timer0_OC0_Mode(TIMER0_OC0_type mode);

extern void Timer0_OVF_IntEnable(void);
extern void Timer0_OVF_IntDisable(void);
extern void Timer0_OVF_IntSetCallBack(void(*LocalFptr)(void));

extern void Timer0_OC_IntEnable(void);
extern void Timer0_OC_IntDisable(void);
extern void Timer0_OC_IntSetCallBack(void(*LocalFptr)(void));

typedef enum
{
	TIMER1_STOP=0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXTERNAL0_FALLING,
	EXTERNAL0_RISING
}TIMER1_Scaler_type;

typedef enum
{
	TIMER1_NORMAL_MODE=0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE
}TIMER1_Mode_type;

typedef enum
{
	OCRA_DISCONNECTED=0,
	OCRA_TOGGLE,
	OCRA_NON_INVERTING,
	OCRA_INVERTING
}TIMER1_OC1A_type;

typedef enum
{
	OCRB_DISCONNECTED=0,
	OCRB_TOGGLE,
	OCRB_NON_INVERTING,
	OCRB_INVERTING

}TIMER1_OC1B_type;

typedef enum
{
	RISING,
	FALLING
}TIMER1_ICU_Edge_type;

extern void Timer1_Init(TIMER1_Mode_type mode,TIMER1_Scaler_type scaler);
extern void Timer1_OCRA1Mode(TIMER1_OC1A_type oc1a_mode);
extern void Timer1_OCRB1Mode(TIMER1_OC1B_type oc1b_mode);

extern void Timer1_OVF_IntEnable(void);
extern void Timer1_OVF_IntDisable(void);
extern void Timer1_OVF_IntSetCallBack(void(*LocalFptr)(void));

extern void Timer1_OCA_IntEnable(void);
extern void Timer1_OCA_IntDisable(void);
extern void Timer1_OCA_IntSetCallBack(void(*LocalFptr)(void));

extern void Timer1_OCB_IntEnable(void);
extern void Timer1_OCB_IntDisable(void);
extern void Timer1_OCB_IntSetCallBack(void(*LocalFptr)(void));

extern void Timer1_InputCaptureEdge(TIMER1_ICU_Edge_type edge);

extern void Timer1_ICU_IntEnable(void);
extern void Timer1_ICU_IntDisable(void);
extern void Timer1_ICU_IntSetCallBack(void(*LocalFptr)(void));

#endif /* TIMER_H_ */