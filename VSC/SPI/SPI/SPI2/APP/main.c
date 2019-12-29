/*
 * main.c
 *
 *  Created on: Dec 20, 2019
 *      Author: hosam
 */


#include "uc2.h"
#include <util/delay.h>
#include <avr/io.h>
void __vector_1(void)__attribute((signal,used));
extern uint32_t Ignite_Flag_Var ;
volatile uint8_t Flag = 0 ;
volatile uint8_t flag2 =0;
volatile uint32_t Distance ;
volatile uint8_t Velocity = 0 ;
static uint8_t Velocity1 = 0 ;
volatile uint8_t Velocity2 = 0 ;

void __vector_1 (void)
{

	if(flag2 == 0)
	{
	flag2++;
	}else
	{
		Distance = Distance + (Velocity2*Delta_t*Ignite_Flag_Var)/1000 ;
		PORTC = Ignite_Flag_Var ;
		UART_sendByte((char)Distance) ;
		Velocity1 = 0 ;
		Velocity2 = 0 ;
		TCNT0=0;
		//Distance = 0 ;
	}
}


int main()
{
	DDRC = 0xFF ;
	DIO_Init_Pin(PC4,HIGH);
	system_init() ;
	while (1)
	{

		if(Velocity1 == 0)
		{
			SPI_receiveByte(&Velocity1);
			if (Velocity1 == 'A')
			{
				DIO_Pin_Write(PC4,HIGH);
			}
			Velocity2 = Velocity1 ;
			Timer_Start(0,Delta_t) ;
		}
		else
		{
			SPI_receiveByte(&Velocity1);
			Distance = Distance + (Velocity2*Delta_t*Ignite_Flag_Var)/1000 ;
			Ignite_Flag_Var = 0 ;
			Velocity2 = Velocity1 ;
		}

	}

	return 0;
}
