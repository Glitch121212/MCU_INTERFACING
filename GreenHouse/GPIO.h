#ifndef GPIO_H
#define GPIO_H

#include "STD_TYPES.h"

#define GPIO_PORTA 0
#define GPIO_PORTB 1
#define GPIO_PORTC 2
#define GPIO_PORTD 3

#define GPIO_PIN0 0
#define GPIO_PIN1 1
#define GPIO_PIN2 2
#define GPIO_PIN3 3
#define GPIO_PIN4 4
#define GPIO_PIN5 5
#define GPIO_PIN6 6
#define GPIO_PIN7 7

#define GPIO_OUTPUT 1
#define GPIO_INPUT 0
#define GPIO_HIGH 1
#define GPIO_LOW 0

void SetPortDirection(u8 port, u8 dir);
void SetPortValue(u8 port, u8 val);
void SetPinDirection(u8 port, u8 pin, u8 dir);
void SetPinValue(u8 port, u8 pin, u8 val);
u8 GetPin(u8 port, u8 pin);

#endif
