/*
 * EEPROM_Simu_Prog_I.h
 *
 * Created: 13.05.2020 21:37:41
 *  Author: AlexHome
 */ 


#ifndef EEPROM_SIMU_PROG_I_H_
#define EEPROM_SIMU_PROG_I_H_

#include "MemAccess.h"

enum Main_State
{

Init = 0,
Menu_Select,
Memory_definition,
Memory_view,
Memory_Download,
Memory_upload,
Memory_sim,
Memory_edit,		
};

char Menu_SelectionMachine(void);
void View_Memory(void);
void LimitOption(char case_limit);
void Access_Memory(long address);
void Memory_Download_F(void);
void Memory_def(void);
void Download_code(void);
char convert_char (char Ascii_value);
void Display_EEPROM(char data_m);
void Memory_Simulation(void);



#endif /* EEPROM_SIMU_PROG_I_H_ */