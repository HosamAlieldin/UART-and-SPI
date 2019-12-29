/*
 * spi.h
 *
 *  Created on: Dec 20, 2019
 *      Author: hosam
 */

#ifndef SPI_SPI_H_
#define SPI_SPI_H_

#include "..\..\Infrastructure\std_types.h"

/* Master\Slave select */
#define SLAVEMODE	0
#define MASTERMODE	1

/* INTERRUPT Mode	*/
#define SPI_INTERRUPT	1
#define SPI_POLLING		0

/* Enable SPI Module */
#define SPI_DISABLE	0
#define SPI_ENABLE	1

/* Data Transmit Order */
#define DATA_ORDER_MSB	0
#define DATA_ORDER_LSB	1

/* Clock Polarity */
#define CLOCK_POLARITY_LOW		0
#define CLOCK_POLARITY_HIGH		1

/* Clock Phase */
#define SAMPLING_EDGE_LEAD		0
#define SAMPLING_EDGE_TRAIL		1


/* PRE-Scallers*/
#define NORMAL_SPEED_MODE	0
#define DOUBLE_SPEED_MODE	1

/* for Fosc_2 activate Double speed mode with Fosc_4 config*/
#define FOSC_4		0
/* for Fosc_8 activate Double speed mode with Fosc_16 config*/
#define FOSC_16		1
/* for Fosc_32 activate Double speed mode with Fosc_64 config*/
#define FOSC_64		2
/* for Fosc_64 activate Double speed mode with Fosc_128 config*/
#define FOSC_128	3



typedef struct
{
	uint8_t Pre_Scaller;
	uint8_t Speed_Mode;
	uint8_t SPI_Mode;
	uint8_t Interrupt_Mode;
	uint8_t	Polarity_Mode;
	uint8_t Phase_Mode;
	uint8_t SPI_Enable;
	uint8_t Data_Order;
}SPI_Cfg_s;



uint8_t SPI_init(SPI_Cfg_s *cfg);
uint8_t SPI_sendByte(const uint8_t data);
uint8_t SPI_receiveByte(uint8_t *data);
uint8_t SPI_sendString(const uint8_t *Str);
uint8_t SPI_receiveString(uint8_t *Str);
#endif /* SPI_SPI_H_ */
