/*
 * Serial.h
 *
 * Created: 13.06.2020 00:19:55
 *  Author: AlexHome
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_
#define F_CPU_N           7372800L
#define UART_BAUD_RATE    9600L

#define UART_BAUD_CALC(UART_BAUD_RATE, F_CPU_N) (F_CPU_N)/(((UART_BAUD_RATE)*16L)-1)
#define TimerStart 253
#define DDR_SPI_Input		DDRD
#define UART_RX			DDD0 //RX
#define UART_TX			DDD1 //TX




char UART_Receive(void);
void UART_Transmit(char cData);

unsigned long CPU_Speed;



#endif /* SERIAL_H_ */