#ifndef KEYPAD_INTERFACE_H
#define KEYPAD_INTERFACE_H

#include "STD_TYPES.h"
#include "GPIO_interface.h"

/*
 * Keypad 4x4 wiring — matches Proteus schematic:
 *   Rows (A,B,C,D) -> PORTD  PD0, PD1, PD2, PD3  (OUTPUT, driven LOW one at a time)
 *   Cols (1,2,3,4) -> PORTD  PD4, PD5, PD6, PD7  (INPUT with internal pull-up)
 */

#define KEYPAD_PORT     GPIO_PORTD

#define KEYPAD_ROW0     GPIO_PIN0   /* Row A */
#define KEYPAD_ROW1     GPIO_PIN1   /* Row B */
#define KEYPAD_ROW2     GPIO_PIN2   /* Row C */
#define KEYPAD_ROW3     GPIO_PIN3   /* Row D */

#define KEYPAD_COL0     GPIO_PIN4   /* Col 1 */
#define KEYPAD_COL1     GPIO_PIN5   /* Col 2 */
#define KEYPAD_COL2     GPIO_PIN6   /* Col 3 */
#define KEYPAD_COL3     GPIO_PIN7   /* Col 4 */

/* Returns the pressed key character, or 0 if none pressed */
void KEYPAD_Init(void);
char KEYPAD_GetKey(void);

#endif /* KEYPAD_INTERFACE_H */
