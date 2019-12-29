/*
 * UC1.h
 *
 *  Created on: Dec 27, 2019
 *      Author: hosam
 */

#ifndef UC1_H_
#define UC1_H_

#include "..\Mcal\DIO\dio.h"
#include "..\Mcal\spi\spi.h"
#include "..\Mcal\UART\uart.h"


#define SYSTEM_IDLE		0U
#define SPEED_RECEIEVE	1U
#define NEW_SPEED		2U
uint8_t system_init(void);


#endif /* UC1_H_ */
