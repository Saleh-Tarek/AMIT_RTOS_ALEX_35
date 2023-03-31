/*
 * system_register.h
 *
 *  Created on: Mar 24, 2022
 *      Author: Tarek ElDallal
 */

#ifndef LIBRARIES_SYSTEM_REGISTER_H_
#define LIBRARIES_SYSTEM_REGISTER_H_

/*----------------------------------- DIO Registers --------------------------------------*/

/*PORTA*/
#define		PORTA				*((volatile uint8_t*)(0x3B))
#define		DDRA				*((volatile uint8_t*)(0x3A))
#define		PINA				*((volatile uint8_t*)(0x39))
/*PORTB*/
#define		PORTB				*((volatile uint8_t*)(0x38))
#define		DDRB				*((volatile uint8_t*)(0x37))
#define		PINB				*((volatile uint8_t*)(0x36))
/*PORTC*/
#define		PORTC				*((volatile uint8_t*)(0x35))
#define		DDRC				*((volatile uint8_t*)(0x34))
#define		PINC				*((volatile uint8_t*)(0x33))
/*PORTD*/
#define		PORTD				*((volatile uint8_t*)(0x32))
#define		DDRD				*((volatile uint8_t*)(0x31))
#define		PIND				*((volatile uint8_t*)(0x30))


/*----------------------------------- TIMER ZERO Registers --------------------------------------*/

/***************THE Timer0 Control Register – TCCR0 [ADDRESS]***************/
#define		TCCR0					*((volatile uint8_t*)(0x53))
/***************THE Timer0 Register – TCNT0 [ADDRESS]***************/
#define		TCNT0					*((volatile uint8_t*)(0x52))
/***************THE TIMER0 Output Compare Register – OCR0 [ADDRESS]***************/
#define		OCR0					*((volatile uint8_t*)(0x5c))
/***************THE Timer0 Interrupt Mask Register – TIMSK [ADDRESS]***************/
#define		TIMSK					*((volatile uint8_t*)(0x59))
/***************THE Timer0 Interrupt Flag Register – TIFR [ADDRESS]***************/
#define		TIFR					*((volatile uint8_t*)(0x58))



#endif /* LIBRARIES_SYSTEM_REGISTER_H_ */
