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
	uint8_t  data;
	SPI_Cfg_s obj;
	obj.Data_Order= DATA_ORDER_MSB;
	obj.Interrupt_Mode= SPI_POLLING;
	obj.Phase_Mode= SAMPLING_EDGE_LEAD;
	obj.Polarity_Mode= CLOCK_POLARITY_LOW;
	obj.Pre_Scaller= FOSC_4;
	obj.SPI_Enable= SPI_ENABLE;
	obj.SPI_Mode = SLAVEMODE;
	obj.Speed_Mode= NORMAL_SPEED_MODE;

	SPI_init(&obj);

	DIO_Init_Pin(PC3,HIGH); //configure PC3 as output pin
	while(1)
	{
		SPI_receiveByte(&data); //receive data from the master Micro-controller
		if(data == SWITCH_PRESSED)
		{
			DIO_Pin_Write(PC3,HIGH); //Led on
		}
		else if(data == SWITCH_NOT_PRESSED)
		{
			DIO_Pin_Write(PC3,LOW); //Led off
		}
	}
	return 0;
}
