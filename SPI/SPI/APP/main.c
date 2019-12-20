/*
 * main.c
 *
 *  Created on: Dec 20, 2019
 *      Author: hosam
 */

#include "..\Mcal\DIO\dio.h"
#include "..\Mcal\spi\spi.h"

#define SWITCH_PRESSED 1
#define SWITCH_NOT_PRESSED 0

int main()
{
	SPI_Cfg_s obj;
	obj.Data_Order= DATA_ORDER_MSB;
	obj.Interrupt_Mode= SPI_POLLING;
	obj.Phase_Mode= SAMPLING_EDGE_LEAD;
	obj.Polarity_Mode= CLOCK_POLARITY_LOW;
	obj.Pre_Scaller= FOSC_4;
	obj.SPI_Enable= SPI_ENABLE;
	obj.SPI_Mode = MASTERMODE;
	obj.Speed_Mode= NORMAL_SPEED_MODE;

	SPI_init(&obj);

	DIO_Init_Pin(PA0,LOW); //configure PA0 as input pin

	while(1)
	{
			if(BIT_IS_SET(PINA,PA0)) //if switch is pressed
		{
			SPI_sendByte(SWITCH_PRESSED);
		}
		else
		{
			SPI_sendByte(SWITCH_NOT_PRESSED);
		}
	}
	return 0;
}
