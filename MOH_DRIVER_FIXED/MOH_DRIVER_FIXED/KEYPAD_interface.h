#ifndef KEYPAD_INTERFACE_H
#define KEYPAD_INTERFACE_H

#include "STD_TYPES.h"
#include "GPIO_interface.h"

/*
 * Keypad 4x4  —  Proteus wiring (matches schematic):
 *
 *   Keypad Rows (A,B,C,D)  ->  PORTD  PD0,PD1,PD2,PD3   INPUT  + pull-up
 *   Keypad Cols (1,2,3,4)  ->  PORTD  PD4,PD5,PD6,PD7   OUTPUT (scan LOW)
 *
 * Proteus KEYPAD-CALCULATOR model: drive Cols LOW and read Rows.
 */

#define KEYPAD_PORT     GPIO_PORTD

/* Rows = INPUT lines */
#define KEYPAD_ROW0     GPIO_PIN0   /* Row A  (7 8 9 /) */
#define KEYPAD_ROW1     GPIO_PIN1   /* Row B  (4 5 6 *) */
#define KEYPAD_ROW2     GPIO_PIN2   /* Row C  (1 2 3 -) */
#define KEYPAD_ROW3     GPIO_PIN3   /* Row D  (C 0 = +) */

/* Cols = OUTPUT scan lines */
#define KEYPAD_COL0     GPIO_PIN4   /* Col 1 */
#define KEYPAD_COL1     GPIO_PIN5   /* Col 2 */
#define KEYPAD_COL2     GPIO_PIN6   /* Col 3 */
#define KEYPAD_COL3     GPIO_PIN7   /* Col 4 */

void KEYPAD_Init(void);
char KEYPAD_GetKey(void);

#endif /* KEYPAD_INTERFACE_H */
