/*
 * uc2.c
 *
 *  Created on: Dec 27, 2019
 *      Author: hosam
 */
#include "uc2.h"
uint8_t system_init(void)
{
	uint8_t status;
	strUART_Config obj2;
	obj2.u16_BaudRate = USART_BAUDRATE;
	obj2.u8_Interrupt = POLLING_MODE;
	obj2.u8_DataBits = EIGHT_BITS;
	obj2.u8_Duplex =  FULL_DUPLEX;
	obj2.u8_Parity = PARITY_DISABLED;
	obj2.u8_SpeedMode = NORMAL_SPEED;
	obj2.u8_StopBits = ONE_STOP;
	obj2.u8_Sync = ASYNCHRONOUS;
	UART_init(&obj2);


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

	Timer_Configuration_S_H Timer_Confg ;
	Timer_Configuration_S_H *Timer_Confg_ptr = &Timer_Confg ;
	Timer_Confg_ptr->Mode = 0 ;
	Timer_Confg_ptr->Res = 50 ;
	Timer_Confg_ptr->Timer_Channel = 0 ;
	Timer_Confg_ptr->Timer_Mode = 0 ;
	Timer_Confg_ptr->Timer_Psc = 5 ;
	Timer_Init(Timer_Confg_ptr) ;

	DIO_Init_Pin(PD2,LOW);
	SET_BIT(GICR,INT0);
	SET_BIT(MCUCR,ISC00);
	SET_BIT(MCUCR,ISC01);
	SET_BIT(SREG,I);

	return status;
}
