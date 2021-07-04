/**
 * @file Timer_Services.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Timer services functions implementation
 * @version 0.1
 * @date 03-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Timer_Services.h"

static volatile u16 t1,t2,t3,flag=0,C;
static u32 NofOverFlow=0;
static void(*fptr_timer)(void);

/*
void PWM_Init(void)
{
    Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
    Timer1_OCRA_Mode(OCRA_NON_INVERTING);
    Timer1_OCB_Mode(OCRB_DISCONNECTED);
}
*/
void PWM_Duty(u16 duty)
{
    if (duty <= 100)
	{
		u16 Ton = ((u32)duty*(ICR1+1))/100;
		if (Ton > 1)
		{
            Timer1_OCRA_Set(Ton-1);
		}
		else
        {
            Timer1_OCRA_Set(0);
        }
	}
}
void PWM_Freq_HZ(u16 freq)
{
    if (freq != 0)
	{
        /* calculate period T = 1000000/f us */
		u16 Ttotal=(u32)1000000/freq;

		if (Ttotal >= 1)
		{
            /* update top to period T */
            Timer1_ICR_Set(Ttotal-1);
		}
		else 
        {
            Timer1_ICR_Set(0);
        }
	}
}
void PWM_Freq_KHZ(u16 freq)
{
    if (freq != 0)
	{
        /* calculate period T= 1000/f us */
		u16 Ttotal = 1000/freq;
		
        if (Ttotal >= 1)
		{
            /* update top value to T */
            Timer1_ICR_Set(Ttotal-1);
		}
		else 
        {
            Timer1_ICR_Set(0);
        }
	}
}

static void Timer_func(void)
{
	static u32 c = 0;
	c++;
	if (c == NofOverFlow)
	{
		c=0;
		fptr_timer();
	}
}
void Timer1_SetIntTime_us (u16 time,void(*LocalFptr)(void))
{
    Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_8);
    Timer1_OCRA_Mode(OCRA_DISCONNECTED);
    Timer1_OCRB_Mode(OCRB_DISCONNECTED);
    
    Timer1_OCRA_Set(time-1);
    
    Timer1_OCA_IntSetCallBack(LocalFptr);
    Timer1_OCA_IntEnable();
}
void Timer1_SetIntTime_ms (u16 time,void(*LocalFptr)(void))
{
    Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_8);
    Timer1_OCRA_Mode(OCRA_DISCONNECTED);
    Timer1_OCRB_Mode(OCRB_DISCONNECTED);
    
    Timer1_OCRA_Set((time*1000)-1);
    
    Timer1_OCA_IntSetCallBack(LocalFptr);
    Timer1_OCA_IntEnable();
}
void Timer1_SetIntTime_s (u16 time,void(*LocalFptr)(void))
{
	Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_8);

    /* interrupt every 1ms */
    Timer1_OCRA_Set(999);
	NofOverFlow = time*1000;
	fptr_timer = LocalFptr;
	Timer1_OCA_IntSetCallBack(Timer_func);
	Timer1_OCA_IntEnable();
}

void PWM_Measure(u32* Pfreq,u8* Pduty)
{
    u16 Ton,Toff;
	
	//TCNT1=0;
	Timer1_ICU_IntSetCallBack(Func_ICU);
	Timer1_InputCaptureEdge(RISING);
	Timer1_ICU_InterruptEnable();
	Timer1_OVF_InterruptEnable();
	Timer1_OVF_SetCallBack(Func_OV);
	flag=0;

	Ton=t2-t1+c2*TOP;
	Toff=t3-t2+(c3-c2)*TOP;

	*Pduty=((u32)Ton*100)/((u32)Ton+Toff);
	*Pfreq=(u32)1000000/((u32)Toff+Ton);
}
void PWM_Measure2(u32* Pfreq,u8* Pduty)
{
    u16 Ton,Toff;
	flag = 0;
	
    TCNT1=0;
    /* PIND6 high */
	while (DIO_ReadPin(PIND6));
    /* PIND6 low */
	while (!DIO_ReadPin(PIND6));
	
    TCNT1=0;
	while (DIO_ReadPin(PIND6));
	Ton = TCNT1;
	
    TCNT1=0;
	while (!DIO_ReadPin(PIND6));
	Toff=TCNT1;

    /* calculate duty and frequency */
	*Pduty=((u32)Ton*100)/(Ton+Toff);
	*Pfreq=(u32)1000000/((u32)Toff+Ton);
}

static void Func_ICU(void);