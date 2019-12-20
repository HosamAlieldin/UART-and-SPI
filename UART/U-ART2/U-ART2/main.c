/*
 * U-ART.c
 *
 * Created: 12/20/2019 10:47:25 AM
 * Author : Mario
 */ 

#include "uart.h"
int main(void)
{
	strUART_Config cfg;
	cfg.u16_BaudRate = 9600;
	cfg.u8_DataBits = EIGHT_BITS;
	cfg.u8_Duplex = FULL_DUPLEX;
	cfg.u8_Interrupt = INTERRUPT_MODE;
	cfg.u8_Parity = PARITY_DISABLED;
	cfg.u8_SpeedMode = NORMAL_SPEED;
	cfg.u8_StopBits = ONE_STOP;
	cfg.u8_Sync = ASYNCHRONOUS;
	uint8_t data;
	uint8_t data_transmit = 0x66 ;
	PORTA = 0xFF ;
	UART_init(&cfg);
    while (1) 
    {
		 UART_sendByte(data_transmit) ;
		 UART_recieveByte(&data); //Receive Byte from Terminal1	 
    }
}

