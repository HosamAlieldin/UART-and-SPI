/*
 * Timer.c
 *
 * Created: 11/23/2019 3:04:51 AM
 *  Author: mostafahamoda1995
 */ 

#include "timer.h"
volatile uint32_t Ticks ;
volatile uint32_t i ;
uint32_t Initial_ticks =  0 ;
volatile uint32_t Ignite_Flag_Var  ;
extern volatile uint32_t Distance ;
extern volatile uint8_t Velocity ;
volatile uint32_t Former_Ignite ;
void __vector_11(void)__attribute((signal,used));

void __vector_11 (void)
{
	if(Ticks != 0)
	{
		if(Ticks < (Timer0_OVF_Val))
		{
			/*Initializing the Timer Register*/
			TCNT0 = Timer0_OVF_Val-Ticks;
			Ticks = Ticks - Ticks ;
			PORTB = 0x00 ;
		}
		else if(Ticks >= (Timer0_OVF_Val))
		{
			/*Initializing the Timer Register*/
			TCNT0 = 0x00 ;
			Ticks = Ticks - Timer0_OVF_Val ;
		}
	}
	else if(Ticks == 0)
	{
		Ticks = Initial_ticks ;
		TCNT0 = 0x00 ;
		Ignite_Flag_Var ++ ;
	}
}
void Timer_Stop_0(void)
{
	// Cutting the Source Clock
	CLEAR_BIT(TCCR0,CS02) ;
	CLEAR_BIT(TCCR0,CS01) ;
	CLEAR_BIT(TCCR0,CS00) ;
}
void Timer_Stop_1(void)
{
	// Cutting the Source Clock
	CLEAR_BIT(TCCR1B,CS12) ;
	CLEAR_BIT(TCCR1B,CS11) ;
	CLEAR_BIT(TCCR1B,CS10) ;
}
void Timer_Stop_2(void)
{
	// Cutting the Source Clock
	CLEAR_BIT(TCCR2,CS22) ;
	CLEAR_BIT(TCCR2,CS21) ;
	CLEAR_BIT(TCCR2,CS20) ;
}
/**********************************************************************************************************************************************/
									/*Timer Initialization Function*/
/**********************************************************************************************************************************************/
uint8_t Timer_Init(Timer_Configuration_S_H* Confg_S)
{
	/******************************************************************************************************************************************/
									/*Importing the Values Stored in the Configuration Structure*/
	/******************************************************************************************************************************************/
	uint8_t mode = Confg_S->Mode , timer_psc = Confg_S->Timer_Psc , timer_channel = Confg_S->Timer_Channel , timer_mode = Confg_S->Timer_Mode;
	/*Setting the Pre-Scalar Values*/
	Prescaller_Timer[timer_channel] = timer_psc ;
	if(timer_channel == 0)
	{
		// Wave Form Generation
		CLEAR_BIT(TCCR0,WGM00) ;
		CLEAR_BIT(TCCR0,WGM01) ;
		// Enabling the Interrupt
		SET_BIT(TIMSK,TOIE0) ;
		//sei() ;
	}
	else if(timer_channel == 1)
	{
		/*Clearing WGM10:11 on TCCRA First*/
		CLEAR_BIT(TCCR1A,WGM10) ;
		CLEAR_BIT(TCCR1A,WGM11) ;
		/*Clearing WGM12:13 on TCCRB*/
		CLEAR_BIT(TCCR1B,WGM12) ;
		CLEAR_BIT(TCCR1B,WGM13) ;
		/*Enabling the Overflow Interrupt*/
		SET_BIT(TIMSK,TOIE1) ;
		//sei() ;
	}
	else if(timer_channel == 2)
	{
		// Wave Form Generation
		CLEAR_BIT(TCCR0,WGM00) ;
		CLEAR_BIT(TCCR0,WGM01) ;
		/// Enabling the Interrupt
		SET_BIT(TIMSK,TOIE0) ;
		//sei() ;
	}
	return ERROR_OK ;
}
/**************************************************************************************************************************************/
												/*Creating Timer Start Function */
/**************************************************************************************************************************************/
uint8_t Timer_Start(uint8_t Timer_Channel,uint32_t Required_Time)
{
	/*Declaring the Minimum Tick */
	double  tick_min = 0 ; 
	if(Timer_Channel == 0)
	{
		/*Setting the Pre-Scalar Values*/
		switch (Prescaller_Timer[Timer_Channel])
		{
		case PSC_0 :
		TCCR0 |= PSC_REG_0 ;
		tick_min = (1/F_CPU_Timer) ;
		break ;
		case PSC_8 :
		TCCR0 |= PSC_REG_8 ;
		tick_min = (8/F_CPU_Timer) ;
		break ;
		case PSC_64 :
		TCCR0 |= PSC_REG_64 ;
		tick_min = (64/F_CPU_Timer) ;
		break ;
		case PSC_256 :
		TCCR0 |= PSC_REG_256 ;
		tick_min = (256/F_CPU_Timer) ;
		break ;
		case PSC_1024 :
		TCCR0 |= PSC_REG_1024 ;
		tick_min = (1024/F_CPU_Timer) ;
		break ;
		}
		/*Calculating Total Number of Ticks*/
		Ticks = (Required_Time*1000)/tick_min ;
		Initial_ticks = Ticks ;
		//Ticks = Required_Time ;
		/*counting the Number of Loops*/
		//uint32_t Loop = Ticks / Timer0_OVF ;
		uint32_t Loop = 1 ;
		for(i=0;i<(Loop+1);i++)
		{
		if(Ticks < Timer0_OVF_Val)
		{
			/*Initializing the Timer Register*/
			TCNT0 = Timer0_OVF_Val-Ticks;
			Ticks = Ticks - Ticks ;
			/*polling on the Overflow Register  */
			//while(GET_BIT(TIFR,TOV0_Reg)==0) ;
			/*Clearing the Overflow Bit*/
			//SET_BIT(TIFR,TOV0_Reg) ;
			break ;
		}
		else if(Ticks >= Timer0_OVF_Val)
		{
			/*Initializing the Timer Register*/
			TCNT0 = 0x00 ;
			/*polling on the Overflow Register  */
			//while(GET_BIT(TIFR,TOV0_Reg) == 0) ;
			/*Clearing the Overflow Bit*/
			//SET_BIT(TIFR,TOV0_Reg) ;
			Ticks = Ticks - Timer0_OVF_Val ;
			/*DDRB = 0xFF ;
			if(i%2 == 0)
			{
				PORTB = 0xFF ;
			}
			else
			{
				PORTB  = 0x00 ;
			}*/
		}			
		}
		//Timer_Stop_0() ;
		//PORTB = 0x00 ;
	}
	/*Timer 1 Configuration */
	/*else if(Timer_Channel == 1)
	{
		/*Setting the pre-Scalar
		switch (Prescaller_Timer[Timer_Channel])
		{
		case PSC_0 :
		TCCR1B|= PSC_REG_0 ;
		tick_min = (1/F_CPU_Timer) ;
		break ;
		case PSC_8 :
		TCCR1B |= PSC_REG_8 ;
		tick_min = (8/F_CPU_Timer) ;
		break ;
		case PSC_64 :
		TCCR1B |= PSC_REG_64 ;
		tick_min = (64/F_CPU_Timer) ;
		break ;
		case PSC_256 :
		TCCR1B |= PSC_REG_256 ;
		tick_min = (256/F_CPU_Timer) ;
		break ;
		case PSC_1024 :
		TCCR1B |= PSC_REG_1024 ;
		tick_min = (1024/F_CPU_Timer) ;
		break ;
		}
		/*Calculating Total Number of Ticks
		Ticks=(Required_Time*1000)/tick_min ;
		uint32_t Loop = Ticks / Timer1_OVF ;
		/*Looping on the Timer register
		for(i=0;i<(Loop+1);i++)
			{
				/*Case 1
				if(Ticks<Timer1_OVF)
				{
					/*Timer Counter Register Initialization
					TCNT1 = Timer1_OVF-Ticks ;
					/*Checking on the Overflow Flag
					while(GET_BIT(TIFR,TOV1) == 0) ;
					/*Clearing the Over flow Register*
					SET_BIT(TIFR,TOV0) ;
					break ;
				}
				else if(Ticks >= Timer1_OVF)
				{
					/*Initializing the Counter
					TCNT1 = 0x00 ;
					/*Polling on the Overflow Flag
					while(GET_BIT(TIFR,TOV1) == 0) ;
					/*Checking on the Overflow Flag
					SET_BIT(TIFR,TOV0) ;
					Ticks = Ticks - Timer1_OVF ;
				}
				else
				{
					break ;
				}
			}
			Timer_Stop_1() ;		
	}*/
	else if(Timer_Channel == 2)
	{
		switch (Prescaller_Timer[Timer_Channel])
		{
			case PSC_0 :
			TCCR2 |= PSC_REG_0 ;
			tick_min = (1/F_CPU_Timer) ;
			break ;
			case PSC_8 :
			TCCR2 |= PSC_REG_8 ;
			tick_min = (8/F_CPU_Timer) ;
			break ;
			case PSC_64 :
			TCCR2 |= PSC_64 ;
			tick_min = (64/F_CPU_Timer) ;
			break ;
			case PSC_256 :
			TCCR2 |= PSC_REG_256 ;
			tick_min = (256/F_CPU_Timer) ;
			break ;
			case PSC_1024 :
			TCCR2 |= PSC_REG_1024 ;
			tick_min = (1024/F_CPU_Timer) ;
			break ;
			default:
			tick_min = (1024/F_CPU_Timer) ;
			break;
		}
		/*Calculating Total Number of Ticks*/
		Ticks = (Required_Time*1000) / 	tick_min ;
		uint32_t Loop = Ticks / Timer2_OVF ;
			for(i=0;i<Loop+1;i++)
			{
				if(Ticks < Timer2_OVF)
				{
					/*Timer2 Counter*/
					TCNT2 = Timer2_OVF-Ticks ;
					/*Polling the Overflow Flag*/
					while(GET_BIT(TIFR,TOV2) == 0) ;
					/*Clearing */
					SET_BIT(TIFR,TOV0) ;
					break ;			
				}
				else if(Ticks >= Timer2_OVF)
				{
					TCNT2 = 0x00 ;
					while(GET_BIT(TIFR,TOV2)==0) ;
					SET_BIT(TIFR,TOV0) ;
					Ticks = Ticks - Timer2_OVF ;
				}
				else
				{
					break ;
				}
		}
		Timer_Stop_2() ;
	}
	return ERROR_OK ;
}
/**************************************************************************************************************************************/
/*Creating Timer Stop Function */
/**************************************************************************************************************************************/

uint8_t Timer_Stop(uint8_t Timer_Channel)
{
	switch(Timer_Channel)
	{
	case 0 :
	Timer_Stop_0() ;
	case 1 : 
	Timer_Stop_1() ;
	case 2 :
	Timer_Stop_2() ;
	}
	return ERROR_OK ;
}



