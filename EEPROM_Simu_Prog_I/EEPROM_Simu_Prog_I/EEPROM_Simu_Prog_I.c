/*
 * EEPROM_Simu_Prog_I.c
 *
 * Created: 10.05.2020 00:50:10
 *  Author: AlexHome
 */ 
#include "EEPROM_Simu_Prog_I.h"
#include <avr/io.h>

#ifndef F_CPU
//#warning "F_CPU war noch nicht definiert, wird nun mit 7372800UL definiert"
#define F_CPU 7372800UL
#endif
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "lcd.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "Button.h"
int count;
char s[1];
char Current_state, Init_return_flag;
extern char function;
extern char ButtonState;
long next_Address;
extern long i;
long i_total;
char memosim[20];
char inputBuff[64];
volatile  char MemSize,LineSize;
volatile int  AddressMem, address_line, interaction;
char ReceiveSession, Lcd_refresh, Lcd_refresh_0;


#if (1)
int main(void)
{	

Init_return_flag = 0x00;

Current_state = Init;
	while (1)
	{
		
	switch (Current_state)
	{
	case Init :
		{
			Button_Init();
			lcd_init(LCD_DISP_ON);
			Memory_4040_pin_Init();
			if(!Init_return_flag)
			{
			  lcd_gotoxy(0,0);
			  lcd_puts("EEPROM PROG/SIMU");
			  lcd_gotoxy(0,1);
			  lcd_puts(" Initializating...");
			  _delay_ms(4000);
			}
			  UART_Init();
			  lcd_clrscr();
              Init_return_flag = 0x01;
			  Current_state = Menu_SelectionMachine();
		}
		break;
	 case Memory_view :
		{
			View_Memory();
		}
		break;
	 case Memory_definition :
		{
			Memory_def();
		}
		break;
     case Memory_Download :
	    {
		   Memory_Download_F();
	    }
		break;
	 case Memory_sim :
	    {
		  Memory_Simulation();
	    }
	 default:
	 break;	
	}
	}

}


char Menu_SelectionMachine()
{
	char sel = 1;
	char Return_function = 0xFF;
	
	while (sel)
	{
		DownButtonPressed();
		UpButtonPressed();
		FuncButtonPressed();
        Disable_memory();
        CMOS_Reset_on();
		lcd_gotoxy(0,0);
		lcd_puts(" SELECT OPTIONS ");
		

		switch (i)
		{
		case 0 :
		{
			lcd_gotoxy(0,1);
			lcd_puts(">Edit EEPROM    ");
			if (function == 0x02)
			{
				function = 0x01;
				sel = 0x00;
				Return_function = Memory_edit;
				lcd_clrscr();
			}
			
			
		}
		break;
			
		case 1 :
		{
			lcd_gotoxy(0,1);
			lcd_puts(">Download to EEPROM");
			if (function == 0x02)
			{
				function = 0x01;
				sel = 0x00;
				Return_function = Memory_Download;
				lcd_clrscr();
			}
			
		}
			
		break;
		
		case 2 :
		{
			lcd_gotoxy(0,1);
			lcd_puts(">Upload f. EEPROM");
			if (function == 0x02)
			{
				function = 0x01;
				sel = 0x00;
				Return_function = Memory_upload;
				lcd_clrscr();
			}
			
			
					
		}
				
		break;
		
		case 3 :
		{
			lcd_gotoxy(0,1);
			lcd_puts(">Memory Def      ");
			if (function == 0x02)
			{
				function = 0x01;
				sel = 0x00;
				Return_function = Memory_definition;
				lcd_clrscr();
			}
					
					
					
		}
				
		break;
		
		case 4 :
		{
			lcd_gotoxy(0,1);
			lcd_puts(">Mem. Read      ");
			if (function == 0x02)
			{
				function = 0x01;
				sel = 0x00;
				Return_function = Memory_view;
				lcd_clrscr();
			}
					
					
					
		}
				
		break;
				
				
		case 5 :
	    {
			lcd_gotoxy(0,1);
			lcd_puts(">Mem. Sim.      ");
			if (function == 0x02)
			{
				function = 0x01;
				sel = 0x00;
				Return_function = Memory_sim;
				lcd_clrscr();
			}
					
					
					
		}
				
		break;
		
		default :
		{
			LimitOption(0x00);
			
		}
		
		break;
		
	}

}


i = 0x00;
return(Return_function);
}

void LimitOption(char case_limit)
{
	
	if(case_limit == 0x00)
	{
	 		if ((i == 0xffffffff) && (i != 0x02) && (i != 0x01) && (i != 0x00))  i = 0x00; /* Limit reached */
	 		if (i == 0x06) i = 0x05; /* Limit reached */	
	}
	if (case_limit == 0x01)
	{
		    if(i == 0xffffffff) i = 0x00;
	}
}

void View_Memory(void)
{
	i = 0x00;
	Lcd_refresh = 0x01;
	
	Init_Memory_Read();
	CMOS_Reset_off();
	Disable_Write_Memory();
	Enable_memory();
	_delay_us(5000);
	
	next_Address = 0x0000;
	Lcd_refresh_0 = 0x01;
	
	while(function == 0x01)
	{
			DownButtonPressed();
			UpButtonPressed();
			FuncButtonPressed();
			lcd_gotoxy(0,0);
			lcd_puts("EEPROM View");
			LimitOption(0x01);
			Access_Memory(next_Address);

	}
	
Disable_memory();
Current_state = Init;		
i = 0x00;
Init_return_flag = 0x01;
function = 0x01;


	
}
void Access_Memory(long address)
{
	char k, data_m;
	

   if (next_Address == 0x00)
   {
	   	data_m = PINB;
		   if ( Lcd_refresh_0)
		   {
	        	Lcd_refresh = 0x01;
			    Lcd_refresh_0 = 0x00;
		   }
		   
   }


   if(i > next_Address)
   {
	   next_Address++;
	   Lcd_refresh = 0x01;
	   Lcd_refresh_0 = 0x01;
	   data_m = Read_Memory_step();
	
   }

   if ((i < next_Address)&&(next_Address != 0x00))
   {
	   next_Address--;
	   Lcd_refresh = 0x01;
	   Lcd_refresh_0 = 0x01;
	if (i == 0xFFFF)
	{
		i = 0;
	}
	   CMOS_4040_Reset_on;
	   _delay_ms(2);
	   CMOS_4040_Reset_off;
	   for (k =0; k < next_Address; k++)
	   {
		   data_m = Read_Memory_step();
		
	   }	
   }

 Display_EEPROM(data_m);
	
}

void Memory_Download_F(void)
{

	char LineFinished;
	char Endcounter;
	char Temp_char;
	
   Endcounter = 0x00;	
   LineFinished = 0x00;	
   ReceiveSession = 0x01;
   _delay_ms(1000);
   lcd_gotoxy(0,0);
   lcd_puts("MEM Down");	
   i = 0x00;
   Init_Memory_Write();
   
   while(ReceiveSession)
   {
	         
		 
       //Write_Memory_step(UART_Receive());
	   while(!(LineFinished))
	   {
        UART_Transmit(0x38);  
	    inputBuff[i] = UART_Receive();
		if ((inputBuff[0] == 0x38)&&(inputBuff[1] == 0x45)&&(inputBuff[2] == 0x4E)&&(inputBuff[3] == 0x44))
		{
		
		Endcounter++;
		if (Endcounter == 9)
		{
		  ReceiveSession = 0x00;
		  LineFinished = 0x01;
		  
		  Disable_memory();	// added
		  Current_state = Init;
		  i = 0x00;
		  Init_return_flag = 0x01; // added
		  
		  
		}
		
	
		}
		if ((inputBuff[i + 1] != 0x0a)&&(inputBuff[i] != 0x0d))
		{
		i++;
		}
		else
		{
		i_total = i;
		LineFinished = 1;
		Disable_memory();
		CMOS_Reset_on();
			   
	   
		
		i = 0x00;
		
		for (interaction = 0x00; interaction < i_total; interaction++)
		{
		   if(inputBuff[interaction] == 58)
		   {
			  LineSize |= ((0xf0)&(convert_char(inputBuff[interaction + 1])<<4));
			  LineSize |= ((0x0f)&(convert_char(inputBuff[interaction + 2])));
			  AddressMem |= (0x000f)&(convert_char(inputBuff[interaction + 6])<<0);
			  AddressMem |= (0x00f0)&(convert_char(inputBuff[interaction + 5])<<4);
			  AddressMem |= (0x0f00)&(convert_char(inputBuff[interaction + 4])<<8);
			  AddressMem |= (0xf000)&(convert_char(inputBuff[interaction + 3])<<12);
		   }
		   
			
		}
		
	   for (i = 0x00; i < LineSize; i++)
	   {
		  memosim[i] = 0xFF; 
	   }
       if ((inputBuff[1] == 83)&&(inputBuff[2] == 84)&&(inputBuff[3] == 65)&&(inputBuff[4] == 82)&&(inputBuff[5] == 84))
	    {		
	       for (i = 0x00; i < LineSize; i++)
		     {
				Temp_char = 0x00u;
                Temp_char |= ((0xf0)&(convert_char(inputBuff[(2*i) + 9 +  9])<<4));
		        Temp_char |= ((0x0f)&convert_char(inputBuff[(2*i)+1 + 9 +  9]));
				memosim[i] = Temp_char;
		     }	
		 }
	    else
         {
            for (i = 0x00; i < LineSize; i++)
			 {
				 Temp_char = 0x00u;
			     Temp_char |= ((0xf0)&(convert_char(inputBuff[(2*i) + 10/*12*/])<<4));
				 Temp_char |= ((0x0f)&convert_char(inputBuff[(2*i)+1 + 10/*12*/]));
	             memosim[i] = Temp_char;
			 }
			
		}
		
		
		
		CMOS_Reset_off();
		for (i = 0x00; i < AddressMem; i++)
		{
		  Count_4040();	
		}
		
		Enable_memory();
		_delay_us(500);
		MEM_OE_on;
		for (i = 0x00; i < LineSize; i++)
		{
			
			_delay_us(400);
		    Write_Memory_step(memosim[i]);
			
			
				
		}
		i = 0x00;
		Disable_memory();
		_delay_us(500);
		Disable_Write_Memory();
		_delay_us(500);
		CMOS_Reset_on();
		LineFinished = 0;
		AddressMem = 0;
		LineSize = 0;
		

	
		}
		
	} 
	
  
   }
   

}
	   
Memory_def()
{
	
}

void Memory_Simulation(void)
{
	Init_Memory_Read();
	
	Disable_Write_Memory();
	
	Set_CS_OE_Input_MCU();
	function = 1;
	
	lcd_gotoxy(0,1);
    lcd_puts(" Simulating...");
	
	while ( function == 1)
	{
		FuncButtonPressed();
	}

Current_state = Init;
i = 0x00;
Init_return_flag = 0x01;
function = 0x01;	
	
	
}

char convert_char (char Ascii_value)
{
	switch(Ascii_value)
	{
		
	
	case 0x30:
	{
		return 0x00;
	}
	break;
	case 0x31:
	{
		return 0x01;
	}
	break;
	case 0x32:
	{
		return 0x02;
	}
	break;
	case 0x33:
	{
		return 0x03;
	}
	break;
	case 0x34:
	{
		return 0x04;
	}
	break;
	case 0x35:
	{
		return 0x05;
	}
	break;
	case 0x36:
	{
		return 0x06;
	}
	break;
	case 0x37:
	{
		return 0x07;
	}
	break;
	case 0x38:
	{
		return 0x08;
	}
	break;
	case 0x39:
	{
		return 0x09;
	}
	break;
	case 0x41:
	{
		return 0x0A;
	}
	break;
	case 0x42:
	{
		return 0x0B;
	}
	break;
	case 0x43:
	{
		return 0x0C;
	}
	break;
	case 0x44:
	{
		return 0x0D;
	}
	break;
	case 0x45:
	{
		return 0x0E;
	}
	break;
	case 0x46:
	{
		return 0x0F;
	}
	break;
	}
	
	

}


void Display_EEPROM(char data_m)
{
 char	buff_data[2], buff_adr[5], buff_tot[15];
 
 
  if(Lcd_refresh == 0x01)
  {
	  lcd_clrscr();
	  itoa(data_m, buff_data, 16);
	  itoa(next_Address, buff_adr, 16);
	  lcd_gotoxy(0,1);
	  lcd_puts("Addr:");
	  lcd_gotoxy(6,1);
	  lcd_puts(buff_adr);
	  lcd_gotoxy(12,1);
	  lcd_puts("D:");
	  lcd_gotoxy(14,1);
	  lcd_puts(buff_data);
	  Lcd_refresh = 0x00;

  }	
}






#endif

