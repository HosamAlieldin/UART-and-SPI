/******************************************************************************
 *
 * Module: Registers
 *
 * File Name: registers.h
 *
 * Description: File include all registers addresses
 *
 * Author: Hosam
 *
 *******************************************************************************/

#ifndef REGISTERS_H_
#define REGISTERS_H_
/*GPIO PORTS ADDRESSES */
#define PORTA (*(volatile uint8_t *)0x003B)
#define PORTB (*(volatile uint8_t *)0x0038)
#define PORTC (*(volatile uint8_t *)0x0035)
#define PORTD (*(volatile uint8_t *)0x0032)

#define PINA (*(volatile uint8_t *)0x0039)
#define PINB (*(volatile uint8_t *)0x0036)
#define PINC (*(volatile uint8_t *)0x0033)
#define PIND (*(volatile uint8_t *)0x0030)

#define DDRA (*(volatile uint8_t *)0x003A)
#define DDRB (*(volatile uint8_t *)0x0037)
#define DDRC (*(volatile uint8_t *)0x0034)
#define DDRD (*(volatile uint8_t *)0x0031)

/*Control Register*/
#define SREG (*(volatile uint8_t *)0x005F)

/* SREG Register Pins*/
#define C  0
#define Z  1
#define N  2
#define V  3
#define S  4
#define H  5
#define T  6
#define I  7

/*INTERRUPT REGISTERS ADDRESSES*/
#define GICR (*(volatile uint8_t *) 0x005B)
#define GIFR (*(volatile uint8_t *) 0x005A)
#define MCUCR (*(volatile uint8_t *)0x0055)
#define MCUCSR (*(volatile uint8_t *)0x0054)

/* GICR Register Pins*/
#define IVCE  0
#define IVSEL 1
#define INT2  5
#define INT0  6
#define INT1  7

/* GIFR Register Pins*/
#define INTF2 5
#define INTF0 6
#define INTF1 7

/*MCUCR Register Pins*/
#define ISC00  0
#define ISC01  1
#define ISC10  2
#define ISC11  3
#define SM0    4
#define SM1    5
#define SE     6
#define SM2    7

/*MCUCSR Register Pins*/
#define PORF  0
#define EXTRF 1
#define BORF  2
#define WDRF  3
#define JTRF  4
#define ISC2  6
#define JTD   7

/*TIMER REGISTERS ADDRESSES*/
#define TCCR0 (*(volatile uint8_t *)0x0053)
#define TCNT0 (*(volatile uint8_t *)0x0052)
#define OCR0 (*(volatile uint8_t *)0x005C)
#define TIMSK (*(volatile uint8_t *)0x0059)
#define TIFR (*(volatile uint8_t *)0x0058)

#define TCCR1A (*(volatile uint8_t *)0x004F)
#define TCCR1B (*(volatile uint8_t *)0x004E)
#define TCNT1H (*(volatile uint8_t *)0x004D)
#define TCNT1L (*(volatile uint8_t *)0x004C)
#define OCR1AH (*(volatile uint8_t *)0x004B)
#define OCR1AL (*(volatile uint8_t *)0x004A)
#define OCR1BH (*(volatile uint8_t *)0x0049)
#define OCR1BL (*(volatile uint8_t *)0x0048)
#define ICR1H (*(volatile uint8_t *)0x0047)
#define ICR1L (*(volatile uint8_t *)0x0046)

#define TCCR2 (*(volatile uint8_t *)0x0045)
#define TCNT2 (*(volatile uint8_t *)0x0044)
#define OCR2 (*(volatile uint8_t *)0x0043)
/*TIMSK Register pins*/
#define TOIE0  0
#define OCIE0  1
#define TOIE1  2
#define OCIE1B 3
#define OCIE1A 4
#define TICIE1 5
#define TOIE2  6
#define OCIE2  7

/*TIFR Register Timer0 pins*/
#define TOV0  0
#define OCF0  1
#define TOV1  2
#define OCF1B 3
#define OCF1A 4
#define ICF1  5
#define TOV2  6
#define OCF2  7

/* TCCR0 register pins*/
#define CS00  0
#define CS01  1
#define CS02  2
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0  7

/* TCCR1A register pins*/
#define WGM10  0
#define WGM11  1
#define FOC1B  2
#define FOC1A  3
#define COM1B0 4
#define COM1B1 5
#define COM1A0 6
#define COM1A1 7

/* TCCR1B register pins*/
#define CS10  0
#define CS11  1
#define CS12  2
#define WGM12 3
#define WGM13 4
#define ICES1 6
#define ICNC1 7

/* TCCR2 register pins*/
#define CS20  0
#define CS21  1
#define CS22  2
#define WGM21 3
#define COM20 4
#define COM21 5
#define WGM20 6
#define FOC2  7



/* SPI Registers ADDRESSES*/

#define SPDR (*(volatile uint8_t *)0x002F)
#define SPSR (*(volatile uint8_t *)0x002E)
#define SPCR (*(volatile uint8_t *)0x002D)


/*SPSR register pins*/
#define SPIF	7
#define WCOL	6
#define SPI2X	0

/*SPCR Register pins*/
#define SPIE	7
#define SPE		6
#define DORD	5
#define MSTR	4
#define CPOL	3
#define CPHA	2
#define SPR1	1
#define SPR0	0

/*UART Registers*/
# define UDR   (*(volatile uint8_t *)0x002C)
# define UCSRA (*(volatile uint8_t *)0x002B)
# define UCSRB (*(volatile uint8_t *)0x002A)
# define UCSRC (*(volatile uint8_t *)0x0040)
# define UBRRH (*(volatile uint8_t *)0x0040)
# define UBRRL (*(volatile uint8_t *)0x0029)

/*UCSRA Register pins*/
#define MPCM 0
#define U2X  1
#define PE 	 2
#define DOR  3
#define FE   4
#define UDRE 5
#define TXC  6
#define RXC  7

/*UCSRB Register pins*/
#define TXB8  0
#define RXB8  1
#define UCSZ2 2
#define TXEN  3
#define RXEN  4
#define UDRIE 5
#define TXCIE 6
#define RXCIE 7

/*UCSRC Register pins*/
#define UCPOL 0
#define UCSZ0 1
#define UCSZ1 2
#define USBS  3
#define UPM0  4
#define UPM1  5
#define UMSEL 6
#define URSEL 7

#endif /* REGISTERS_H_ */
