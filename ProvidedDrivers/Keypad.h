/* 
 * File:   Keypad.h
 * Author: Muhammed.Hany
 *
 * Created on April 29, 2026, 10:29 AM
 */


#ifndef KEYPAD_H
#define	KEYPAD__H
#include "GPIO.h"


#define Keypad_Arr {{'7','8','9','/'} ,{'4','5','6','B'} ,{'1','2','3','-'},{'C','0','=','+'}}

#define KPD_Row1 GPIO_enuPIN0
#define KPD_Row2 GPIO_enuPIN1
#define KPD_Row3 GPIO_enuPIN2
#define KPD_Row4 GPIO_enuPIN3

#define KPD_col1 GPIO_enuPIN4
#define KPD_col2 GPIO_enuPIN5
#define KPD_col3 GPIO_enuPIN6
#define KPD_col4 GPIO_enuPIN7

#define KPD_ROWNUM 4
#define KPD_ColNUM 4

void Keypad_init(u8 copy_port);
u8 Keypad_CheckNum(u8 copy_u8port);

#endif	/* KEYPAD_H */

