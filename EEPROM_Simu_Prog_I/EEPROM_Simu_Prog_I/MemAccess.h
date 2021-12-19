/*
 * MemAccess.h
 *
 * Created: 11.05.2020 21:33:37
 *  Author: AlexHome
 */ 


#ifndef MEMACCESS_H_
#define MEMACCESS_H_

#include <avr/io.h>
#include <util/delay.h>

#define CMOS_4040_Clock_on PORTA |= (1 << PA7);
#define CMOS_4040_Clock_off PORTA &= ~(1 << PA7);

#define CMOS_4040_Reset_on PORTD |= (1 << PD3);    /* 4040 Reset pin */
#define CMOS_4040_Reset_off PORTD &= ~(1 << PD3);

#define MEM_CS_on PORTD |= (1 << PD6);             /* Memory CS pin */
#define MEM_CS_off PORTD &= ~(1 << PD6);

#define MEM_OE_on PORTD |= (1 << PD5);             /* Memory OE pin */
#define MEM_OE_off PORTD &= ~(1 << PD5);


#define MEM_WE_on PORTD |= (1 << PD4);             /* Memory WE pin */
#define MEM_WE_off PORTD &= ~(1 << PD4);


char *Read_Memory(int address);
void Write_Memory(int address, char *data_in);

extern char Read_Memory_step(void);
void Write_Memory_step(char data_in);

void Count_4040(void);
void Memory_4040_pin_Init(void);
void Enable_memory(void);
void Disable_memory(void);
void CMOS_Reset_off(void);
void CMOS_Reset_on(void);
void Enable_Write_Memory(void);
void Disable_Write_Memory(void);
void Init_Memory_Write(void);
void Init_Memory_Read(void);

void Set_CS_OE_Input_MCU(void);




#endif /* MEMACCESS_H_ */