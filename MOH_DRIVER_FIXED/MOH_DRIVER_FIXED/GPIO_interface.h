#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include "STD_TYPES.h"

/* Ports */
#define GPIO_PORTA   0
#define GPIO_PORTB   1
#define GPIO_PORTC   2
#define GPIO_PORTD   3

/* Pins */
#define GPIO_PIN0    0
#define GPIO_PIN1    1
#define GPIO_PIN2    2
#define GPIO_PIN3    3
#define GPIO_PIN4    4
#define GPIO_PIN5    5
#define GPIO_PIN6    6
#define GPIO_PIN7    7

/* Direction */
#define GPIO_INPUT   0
#define GPIO_OUTPUT  1

/* Values */
#define GPIO_LOW     0
#define GPIO_HIGH    1

/* Port config */
#define GPIO_PORT_INPUT   0x00
#define GPIO_PORT_OUTPUT  0xFF

/* APIs */
void GPIO_VidSetPinDirection(u8 port, u8 pin, u8 dir);
void GPIO_VidSetPinValue(u8 port, u8 pin, u8 value);
void GPIO_VidTogglePin(u8 port, u8 pin);

void GPIO_VidSetPortDirection(u8 port, u8 dir);
void GPIO_VidSetPortValue(u8 port, u8 value);

u8 GPIO_U8GetPinValue(u8 port, u8 pin);

#endif