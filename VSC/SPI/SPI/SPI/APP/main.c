/*
 * main.c
 *
 *  Created on: Dec 20, 2019
 *      Author: hosam
 */
#include "uc1.h"
#include <util/delay.h>
static uint8_t gu8_speed;
uint8_t state = SYSTEM_IDLE;
uint8_t gu8_flag1 , gu8_flag2 ;

void __vector_1(void)__attribute((signal,used));

void __vector_3(void)__attribute((signal,used));

/* speed up int1*/
void __vector_1 (void)
{
	gu8_flag1 = 1;
}
/* speed down int2*/
void __vector_3(void)
{
	gu8_flag2=1;
}

int main()
{
	system_init();
	DIO_Init_Pin(PC4,HIGH); //configure PA0 as input pin
	while (1)
	{
		if(state == SYSTEM_IDLE)
		{
			UART_recieveByte(&gu8_speed);
			if (gu8_speed == 'A')
			{
				DIO_Pin_Write(PC4,HIGH);
			}
			state = SPEED_RECEIEVE;
		}
		if (state == SPEED_RECEIEVE)
		{
			_delay_ms(50);
			SPI_sendByte(gu8_speed);
			state = NEW_SPEED;
		}
		else if ( state == NEW_SPEED)
		{
			if (gu8_flag1 ==1)
			{
				gu8_speed+=1;
				state = SPEED_RECEIEVE;
				gu8_flag1 =0;
			}
			if (gu8_flag2 ==1)
			{
				gu8_speed-=1;
				state = SPEED_RECEIEVE;
				gu8_flag2 =0;
			}
		}
	}
	return 0;
}
