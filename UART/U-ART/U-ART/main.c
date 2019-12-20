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
	uint8_t data = 0x55;
	uint8_t data_Rec ;
	UART_init(&cfg);
    while (1) 
    {
		UART_recieveByte(&data_Rec) ;
		UART_sendByte(data); //Resend the received byte to Terminal2
    }
	


}

