/*
 * MemAcess.c
 *
 * Created: 11.05.2020 21:32:58
 *  Author: AlexHome
 */ 
#include"MemAccess.h"

#if(0)
char* Read_Memory(int address)
{
	int i;
	char Mem_Data[address -1];
	DDRD |= (1 << DDD6); /* CMOS 4040 Clock output*/
	DDRD |= (1 << DDD5); /* CMOS 4040 Reset output*/
	CMOS_4040_Clock_off
	
	for(i = 0; i <= address; i++)
	{
		if(i == 0x00) Mem_Data[0] = PINA;
		CMOS_4040_Clock_off
		CMOS_4040_Clock_on
		CMOS_4040_Clock_off
		Mem_Data[i] = PINB;
		
		
	}
	
	return *Mem_Data;
}
void Write_Memory(int address, char *data_in)
{
	int i;
	char Mem_Data[address -1];
	DDRD |= (1 << DDD6); /* CMOS 4040 Clock output*/
	DDRD |= (1 << DDD5); /* CMOS 4040 Reset output*/
	CMOS_4040_Clock_off
	
	for(i = 0; i <= address; i++)
	{
		PORTB = Mem_Data[i];
		CMOS_4040_Clock_off
		CMOS_4040_Clock_on
		CMOS_4040_Clock_off
		
		
	}
}
#endif

void Init_Memory_Write(void)
{
   DDRB = 0xFF;	
}

void Init_Memory_Read(void)
{
	DDRB = 0x00;
}

void Memory_4040_pin_Init(void)
{
	/*DDRB = 0xFF;*/
	DDRA |= (1 << DDD7);
	DDRD |= (1 << DDD5);
	DDRD |= (1 << DDD6);
	DDRD |= (1 << DDD3);
	DDRD |= (1 << DDD4);
}

char Read_Memory_step(void)
{
	char i;

    
	CMOS_4040_Clock_off
	_delay_us(500);
	CMOS_4040_Clock_on
	_delay_us(500);
	CMOS_4040_Clock_off
	_delay_us(5000);
	i = PINB;

	return (i);
}
void Write_Memory_step(char data_in)
{
    MEM_CS_off;
	_delay_us(100);
	Enable_Write_Memory();
//	_delay_us(1000);
	PORTB = data_in;
//	_delay_us(1000);
	Disable_Write_Memory();
	_delay_us(100);
	MEM_CS_on;
	CMOS_4040_Clock_off
	_delay_us(1000);
	CMOS_4040_Clock_on
	_delay_us(1000);
	CMOS_4040_Clock_off
	
	
}

void Enable_memory(void)
{

	MEM_CS_off
	MEM_OE_off	
	
}

void Enable_Write_Memory(void)
{
	MEM_WE_off
}

void Disable_Write_Memory(void)
{
	MEM_WE_on
}

void Set_CS_OE_Input_MCU(void)
{
	DDRD &= ~(1 << PIND5);
	DDRD &= ~(1 << PIND6);
}


void Disable_memory(void)
{
	MEM_CS_on
	MEM_OE_on	
}

void CMOS_Reset_off(void)
{
	CMOS_4040_Reset_off
}

void CMOS_Reset_on(void)
{
	CMOS_4040_Reset_on
}

void Count_4040(void)
{
	CMOS_4040_Clock_off
	_delay_us(500);
	CMOS_4040_Clock_on
	_delay_us(500);
	CMOS_4040_Clock_off	
}