/*
 * UC1.c
 *
 *  Created on: Dec 27, 2019
 *      Author: hosam
 */
#include "uc1.h"

uint8_t system_init(void)
{
	uint8_t status;
	strUART_Config UART_config;
		UART_config.u16_BaudRate = 9600;
		UART_config.u8_DataBits = EIGHT_BITS;
		UART_config.u8_Duplex = FULL_DUPLEX;
		UART_config.u8_Interrupt = POLLING_MODE;
		UART_config.u8_Parity = PARITY_DISABLED;
		UART_config.u8_SpeedMode = NORMAL_SPEED;
		UART_config.u8_StopBits = ONE_STOP;
		UART_config.u8_Sync = ASYNCHRONOUS;

		UART_init(&UART_config);

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
	DIO_Init_Pin(PB2,LOW);
	DIO_Init_Pin(PD2,LOW);


	SET_BIT(GICR,INT2);
	SET_BIT(GICR,INT0);
	SET_BIT(MCUCSR,ISC2);
	SET_BIT(MCUCR,ISC00);
	SET_BIT(MCUCR,ISC01);
	SET_BIT(SREG,I);

	return status;
}
