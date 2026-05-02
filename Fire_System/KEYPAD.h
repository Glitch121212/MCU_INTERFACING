#ifndef KEYPAD_H
#define KEYPAD_H

#include "STD_TYPES.h"
#include "GPIO.h"

/* ===== CONFIG ===== */
#define KEYPAD_PORT GPIO_enuPORTB

#define KEYPAD_Row0 GPIO_enuPIN0
#define KEYPAD_Row1 GPIO_enuPIN1
#define KEYPAD_Row2 GPIO_enuPIN2
#define KEYPAD_Row3 GPIO_enuPIN3

#define KEYPAD_Col0 GPIO_enuPIN4
#define KEYPAD_Col1 GPIO_enuPIN5
#define KEYPAD_Col2 GPIO_enuPIN6
#define KEYPAD_Col3 GPIO_enuPIN7

/* ===== FUNCTIONS ===== */
void KEYPAD_Init();
u8 Keypad_CheckNum( u8 port);

#endif