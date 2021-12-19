/*
 * Serial.c
 *
 * Created: 12.06.2020 23:54:29
 *  Author: AlexHome
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Serial.h"



void UART_Init(void)
{
	UBRRH = 0x00;//(uint8_t)(UART_BAUD_CALC(UART_BAUD_RATE, F_CPU)>>8);
	UBRRL = 47U;//(uint8_t)UART_BAUD_CALC(UART_BAUD_RATE, F_CPU);

	UCSRB |= (1<<RXEN);
	UCSRB |= (1<<TXEN);

	UCSRC |= (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);



	CPU_Speed = F_CPU;
}



char UART_Receive(void)
{
	char c;
	/* Wait for reception complete */
	while (!(UCSRA & (1<<RXC)));
	c = UDR;

	/* Return data register */
	return c;
}

void UART_Transmit(char cData)
{
	/* Wait for transmission complete */
	while
	(!(UCSRA & (1<<UDRE)));
	
	UDR = cData;
}