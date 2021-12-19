/*
 * button.c
 *
 * Created: 10.05.2020 01:03:39
 *  Author: AlexHome
 */ 
#include "Button.h"

char ButtonState = 0x01;
char function = 0x01;
long i;
char digitIncrDecrPress = 0x00;
char functionPress = 0x00;

void Button_Init(void)
{
	
	DDRD &= ~(1 << DDD7);
	DDRC &= ~(1 << DDC1);
	DDRC &= ~(1 << DDC0);

}



void FuncButtonPressed(void)
{
	if ((FunctionButton) && (functionPress == 0x00))
	{
		function++;
		functionPress = 0x01;
		_delay_ms(1);
	}
	else if ((!FunctionButton) && (functionPress == 0x01))
	{
		if(function < 0x01)
		{
			function = 0x01;
		}
		
		functionPress = 0x00;
		_delay_ms(1);
		ButtonState = 0x01;
	}
}

void DownButtonPressed(void)
{



	if ((DownButton) && (digitIncrDecrPress == 0x00))
	{
		i--;
		digitIncrDecrPress = 0x01;
		_delay_ms(1);
	}
	else if((!DownButton) && (digitIncrDecrPress == 0x01))
	{

		digitIncrDecrPress = 0x00;
		_delay_ms(1);
		ButtonState = 0x01;
				
	}
}

void UpButtonPressed(void)
{

	if ((UpButton) && (digitIncrDecrPress == 0x00))
	{
		i++;
		digitIncrDecrPress = 0x02;
		_delay_ms(1);
	}
	else if((!UpButton) && (digitIncrDecrPress == 0x02))
	{
		digitIncrDecrPress = 0x00;
		ButtonState = 0x01;
		_delay_ms(1);
	}
}
