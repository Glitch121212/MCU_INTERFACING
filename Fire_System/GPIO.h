#ifndef GPIO_H
#define GPIO_H

#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* ================== Register Definitions ================== */

/* PORTB */
#define PORTB   *((volatile u8*)0x25)
#define DDRB    *((volatile u8*)0x24)
#define PINB    *((volatile u8*)0x23)

/* PORTC */
#define PORTC   *((volatile u8*)0x28)
#define DDRC    *((volatile u8*)0x27)
#define PINC    *((volatile u8*)0x26)

/* PORTD */
#define PORTD   *((volatile u8*)0x2B)
#define DDRD    *((volatile u8*)0x2A)
#define PIND    *((volatile u8*)0x29)

/* ================== ENUMS ================== */

/* Ports */
typedef enum
{
    GPIO_enuPORTB = 0,
    GPIO_enuPORTC,
    GPIO_enuPORTD
} GPIO_enuPort_t;

/* Pins */
typedef enum
{
    GPIO_enuPIN0 = 0,
    GPIO_enuPIN1,
    GPIO_enuPIN2,
    GPIO_enuPIN3,
    GPIO_enuPIN4,
    GPIO_enuPIN5,
    GPIO_enuPIN6,
    GPIO_enuPIN7
} GPIO_enuPin_t;

/* Direction */
typedef enum
{
    GPIO_enuINPUT = 0,
    GPIO_enuOUTPUT
} GPIO_enuDirection_t;

/* Value */
typedef enum
{
    GPIO_enuLOW = 0,
    GPIO_enuHIGH
} GPIO_enuValue_t;

/* ================== APIs ================== */

void GPIO_VidSetPinDirection(GPIO_enuPort_t Copy_enuPort, GPIO_enuPin_t Copy_enuPin, GPIO_enuDirection_t Copy_enuDirection);

void GPIO_VidSetPinValue(GPIO_enuPort_t Copy_enuPort, GPIO_enuPin_t Copy_enuPin,GPIO_enuValue_t Copy_enuValue);

void GPIO_VidSetPortDirection(GPIO_enuPort_t Copy_enuPort,  u8 Copy_u8Direction);

void GPIO_VidSetPortValue(GPIO_enuPort_t Copy_enuPort, u8 Copy_u8Value);

void GPIO_VidTogglePinValue(GPIO_enuPort_t Copy_enuPort,  GPIO_enuPin_t Copy_enuPin);

u8 GPIO_U8GetPinValue(GPIO_enuPort_t Copy_enuPort,GPIO_enuPin_t Copy_enuPin);

u8 GPIO_U8GetPortValue(GPIO_enuPort_t Copy_enuPort);

#endif