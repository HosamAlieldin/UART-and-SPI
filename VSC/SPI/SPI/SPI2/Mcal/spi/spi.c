/*
 * spi.c
 *
 *  Created on: Dec 20, 2019
 *      Author: hosam
 */


#include "..\..\Infrastructure\registers.h"
#include "..\DIO\dio_cfg.h"
#include "..\DIO\dio.h"
#include "spi.h"
void __vector_12(void)__attribute((signal,used));
/********** global flag for receive interrupt*****************************/
static uint8_t gu8_flag =0;

void __vector_12()
{
	gu8_flag =1;
	CLEAR_BIT(SPCR,SPIE);
}


/********** global variable to store interrupt/polling state***************/
static uint8_t gu8_Int =0 ;

/********** global variable to store data for interrupt state**************/
static uint8_t gu8_Var =0 ;
/***************************************************************************
 * Function: SPI_Init
 * @param: *cfg, a pointer to a configuration structure sent by the user
 * @return: returns error status
 * Description: Function to initialize SPI
 **************************************************************************/

uint8_t SPI_init(SPI_Cfg_s *cfg)
{
	uint8_t status=ERROR_OK;
	if (SPI_ENABLE ==cfg->SPI_Enable)
	{
		if (MASTERMODE == cfg->SPI_Mode)
		{
			DIO_Init_Pin(PB4,HIGH);
			DIO_Init_Pin(PB5,HIGH);
			DIO_Init_Pin(PB6,LOW);
			DIO_Init_Pin(PB7,HIGH);
			SET_BIT(SPCR,MSTR);
			if (cfg->Pre_Scaller >=0 && cfg->Pre_Scaller <4)
			{
				SPCR= (SPCR & 0xFC) | cfg->Pre_Scaller;
				if (DOUBLE_SPEED_MODE == cfg->Speed_Mode)
				{
					SET_BIT(SPSR,SPI2X);
				}
				else
				{
					CLEAR_BIT(SPSR,SPI2X);
				}
				if (DATA_ORDER_LSB == cfg->Data_Order)
				{
					SET_BIT(SPCR,DORD);
				}
				else
				{
					CLEAR_BIT(SPCR,DORD);
				}
				if (SPI_INTERRUPT == cfg->Interrupt_Mode)
				{
					SET_BIT(SREG,I);
					gu8_Int = cfg->Interrupt_Mode;
				}
				else
				{
					CLEAR_BIT(SREG,I);
					CLEAR_BIT(SPCR,SPIE);
					gu8_Int = cfg->Interrupt_Mode;
				}
				if (CLOCK_POLARITY_HIGH == cfg->Polarity_Mode)
				{
					SET_BIT(SPCR,CPOL);
				}
				else
				{
					CLEAR_BIT(SPCR,CPOL);
				}
				if (SAMPLING_EDGE_TRAIL == cfg->Phase_Mode)
				{
					SET_BIT(SPCR,CPHA);
				}
				else
				{
					CLEAR_BIT(SPCR,CPHA);
				}
				/*SET_BIT(SPCR,SPE);*/
			}
			else
			{
				status = ERROR_NOK;
			}
		}
		else if (SLAVEMODE == cfg->SPI_Mode)
		{
			DIO_Init_Pin(PB4,LOW);
			DIO_Init_Pin(PB5,LOW);
			DIO_Init_Pin(PB6,HIGH);
			DIO_Init_Pin(PB7,LOW);
			CLEAR_BIT(SPCR,MSTR);
			CLEAR_BIT(SPSR,SPI2X);
			CLEAR_BIT(SPCR,SPR0);
			CLEAR_BIT(SPCR,SPR1);
			if (DATA_ORDER_LSB == cfg->Data_Order)
			{
				SET_BIT(SPCR,DORD);
			}
			else
			{
				CLEAR_BIT(SPCR,DORD);
			}
			if (SPI_INTERRUPT == cfg->Interrupt_Mode)
			{
				SET_BIT(SREG,I);
				gu8_Int = cfg->Interrupt_Mode;
			}
			else
			{
				CLEAR_BIT(SREG,I);
				CLEAR_BIT(SPCR,SPIE);
				gu8_Int = cfg->Interrupt_Mode;
			}
			if (CLOCK_POLARITY_HIGH == cfg->Polarity_Mode)
			{
				SET_BIT(SPCR,CPOL);
			}
			else
			{
				CLEAR_BIT(SPCR,CPOL);
			}
			if (SAMPLING_EDGE_TRAIL == cfg->Phase_Mode)
			{
				SET_BIT(SPCR,CPHA);
			}
			else
			{
				CLEAR_BIT(SPCR,CPHA);
			}

		}
		else
		{
			status = ERROR_NOK;
		}
		/*SET_BIT(SPCR,SPE);*/
	}
	else
	{
		status = ERROR_NOK;
		CLEAR_BIT(SPCR,SPE);
	}
	SET_BIT(SPCR,SPE);
	return status;
}


/***************************************************************************
 * Function: SPI_sendByte
 * @param: data, a const data byte sent by the user
 * @return: returns error status
 * Description: Function to send data byte using SPI
 **************************************************************************/

uint8_t SPI_sendByte(const uint8_t data)
{
	uint8_t status;
	if (SPI_POLLING == gu8_Int)
	{
		SPDR = data;
		while (BIT_IS_CLEAR(SPSR,SPIF)){}
	}
	else if (SPI_INTERRUPT == gu8_Int)
	{
		gu8_Var = data;
		SET_BIT(SPCR,SPIE);
	}
	return status;
}

/***************************************************************************
 * Function: SPI_receieveByte
 * @param: *data, a pointer to variable to return data
 * @return: returns error status
 * Description: Function to receive data byte using SPI
 **************************************************************************/

uint8_t SPI_receiveByte(uint8_t *data)
{
	uint8_t status;
	if (SPI_POLLING == gu8_Int)
	{
		while (BIT_IS_CLEAR(SPSR,SPIF)){}
		*data=SPDR;
	}
	else if (SPI_INTERRUPT == gu8_Int)
	{
		SET_BIT(SPCR,SPIE);
	}
	return status;
}

/***************************************************************************
 * Function: SPI_sendString
 * @param: *str, a pointer to a const string to send str
 * @return: returns error status
 * Description: Function to receive data byte using SPI
 **************************************************************************/

uint8_t SPI_sendString(const uint8_t *Str)
{
	uint8_t status;
	uint8_t loop = 0;
	while(Str[loop] != '\0')
	{
		SPI_sendByte(Str[loop]);
		loop++;
	}
	return status;
}

/***************************************************************************
 * Function: SPI_receiveString
 * @param: *str, a pointer to a string to return data
 * @return: returns error status
 * Description: Function to receive data byte using SPI
 **************************************************************************/

uint8_t SPI_receiveString(uint8_t *Str)
{
	uint8_t status;
	uint8_t loop = 0;
	SPI_receiveByte(&Str[loop]);
	while(Str[loop] != '#')
	{
		loop++;
		SPI_receiveByte(&Str[loop]);
	}
	Str[loop] = '\0';
	return status;
}
