/*
 * Button.h
 *
 * Created: 10.05.2020 01:08:33
 *  Author: AlexHome
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include <avr/io.h>
#include <util/delay.h>


#define DD_Input1	DDC0 //Input1
#define DD_Input2	DDC1 //Input2
#define DD_Input3   DDD7 //Input3


#define UpButton (PINC & (1 << PINC0)) //switch 1
#define DownButton (PINC & (1 << PINC1))//switch 2
#define FunctionButton (PIND & (1 << PIND7)) //switch 3














void Button_Init(void);
void DownButtonPressed (void);
void UpButtonPressed (void);
void FuncButtonPressed(void);





#endif /* BUTTON_H_ */