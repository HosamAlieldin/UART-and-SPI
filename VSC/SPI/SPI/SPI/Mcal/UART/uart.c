 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Mario
 *
 *******************************************************************************/

#include "uart.h"
volatile uint8_t gu8_DataTransmit ;
volatile uint8_t gu8_DataReceive ;
/******************Setting the ISR**********************************************/
void __vector_14(void)__attribute((signal,used));

void __vector_13(void)__attribute((signal,used));

void __vector_14 (void)  /************************** ISR For SENDING**********************/
{
	UDR = gu8_DataTransmit ;
	CLEAR_BIT(UCSRB,UDRIE);
}
void __vector_13 (void)
{
		gu8_DataReceive = UDR ;
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
UART_ERROR UART_init(const strUART_Config *UART_Cfg)
{
	uint8_t ERROR  = ERROR_OK;
			/**********************Configuration of Duplex Transmission**********************/
		switch(UART_Cfg->u8_Duplex)
		{
			case FULL_DUPLEX :
			SET_BIT(UCSRB,RXEN) ;
			SET_BIT(UCSRB,TXEN) ;
			break;

			case TRANSIMETER :
			SET_BIT(UCSRB,TXEN) ;
			break;

			case RECEIVER :
			SET_BIT(UCSRB,TXEN) ;
			break;
		}


		/******************Checking Speed Mode & BAUDRATE ************************************/
		//CLEAR_BIT(UBRRH,URSEL) ; /***********************to Write in UBRRH REGISTERS***********/
			switch(UART_Cfg->u8_SpeedMode)
			{
			case NORMAL_SPEED :
			CLEAR_BIT(UCSRA,U2X);
			/**************************BAUDRATE****************************************/
			/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
			UBRRH = BAUD_PRESCALE_SINGLE>>8;
			UBRRL = BAUD_PRESCALE_SINGLE;
			break;

			case DOUBLE_SPEED :
			SET_BIT(UCSRA,U2X) ;
				/**************************BAUDRATE****************************************/
				/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
			UBRRH = BAUD_PRESCALE_DOUBLE>>8;
			UBRRL = BAUD_PRESCALE_DOUBLE;
			break;
			default :
			ERROR = ERROR_NOK ;
			break ;
		}
		/**********************Synchronous or Asynchronous Operation **************/
		//SET_BIT(UCSRC,URSEL) ; /******************Setting to Access UCRSC Register********/
		switch(UART_Cfg->u8_Sync)
		{
			case SYNCHRONOUS:
				SET_BIT(UCSRC,URSEL) ;
				SET_BIT(UCSRC,UMSEL);
				break;
			case ASYNCHRONOUS:
				CLEAR_BIT(UCSRC,UMSEL);
				break ;
			default:
				ERROR = ERROR_NOK ;
		}
		/***********************FRAME DATA BITS*************************************/
		switch(UART_Cfg->u8_DataBits)
		{
			case FIVE_BITS:
				CLEAR_BIT(UCSRC,UCSZ0) ;
				CLEAR_BIT(UCSRC,UCSZ1) ;
				CLEAR_BIT(UCSRB,UCSZ2) ;
				break;

			case SIX_BITS:
				UCSRC |= (1<<UCSZ0) | (1<<URSEL) ;

				break;

			case SEVEN_BITS:
				UCSRC |= (1<< UCSZ1) | (1<<URSEL);

				break;

			case EIGHT_BITS:
				UCSRC |= (1<<UCSZ1) | (1<<UCSZ0) | (1<<URSEL);

				break;

			case NINE_BITS:
				UCSRC |= (1<< UCSZ1) | (1<< UCSZ0) | (1<<UCSZ2) | (1<<URSEL);

				break;
			default:
				ERROR = ERROR_NOK ;
				break;
		}



		/****************************PARITY CHECKING****************************/
		switch(UART_Cfg->u8_Parity)
		{
			case PARITY_DISABLED:
				CLEAR_BIT(UCSRC,UPM1);
				CLEAR_BIT(UCSRC,UPM0);
				break;
			case EVEN_PARITY:
				SET_BIT(UCSRC,UPM1);
				CLEAR_BIT(UCSRC,UPM0);
				break;
			case ODD_PARITY:
				SET_BIT(UCSRC,UPM1);
				SET_BIT(UCSRC,UPM0);
				break;
			default:
				ERROR = ERROR_NOK ;
				break;
		}
		/************************** STOP BITS************************************/
		switch(UART_Cfg->u8_StopBits)
		{
			case ONE_STOP:
				CLEAR_BIT(UCSRC,USBS) ;
				break;
			case TWO_STOP:
				SET_BIT(UCSRC,USBS) ;

				break;
			default:
				ERROR = ERROR_NOK ;
				break;
		}
		/********************Interrup or Polling Mode****************************/
		switch(UART_Cfg->u8_Interrupt)
		{
			case INTERRUPT_MODE:
			SET_BIT(UCSRB,TXCIE) ;
			SET_BIT(UCSRB,RXCIE) ;
			SET_BIT(SREG,7) ;
			break;
			case POLLING_MODE:
			break;
			default:
			ERROR = ERROR_NOK ;
			break;
		}
		return ERROR ;
}
	
UART_ERROR UART_sendByte(const uint16_t data)
{
	/*************running on interrupt Mode************/
	//while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	/*gu8_DataTransmit = data ;
	SET_BIT(UCSRB,UDRIE) ;*/
	/************running on Polling Mode*************/
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	UDR = data;
	return ERROR_OK ;
}

UART_ERROR UART_recieveByte(uint8_t *pu8_Received_Data)
{
	/***********Receiving on Inerrupt Mode*********/
	/*SET_BIT(UCSRB,RXCIE) ;
	*pu8_Received_Data = gu8_DataReceive;*/
	/***********Polling on Mode*********************/
	while(BIT_IS_CLEAR(UCSRA,RXC)){}	 
    *pu8_Received_Data = UDR;
   return ERROR_OK;
}


