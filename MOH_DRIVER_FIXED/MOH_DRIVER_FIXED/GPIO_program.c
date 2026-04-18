#include "GPIO_interface.h"
#include "BIT_MATH.h"

/* Register Struct: { PIN, DDR, PORT } */
typedef struct
{
    volatile u8 PIN;
    volatile u8 DDR;
    volatile u8 PORT;
} GPIO_t;

/*
 * ATmega328P I/O base addresses (PIN register = base)
 * Datasheet Table 36-1
 */
#define GPIOA ((GPIO_t*)0x20)   /* PINA=0x20, DDRA=0x21, PORTA=0x22 */
#define GPIOB ((GPIO_t*)0x23)   /* PINB=0x23, DDRB=0x24, PORTB=0x25 */
#define GPIOC ((GPIO_t*)0x26)   /* PINC=0x26, DDRC=0x27, PORTC=0x28 */
#define GPIOD ((GPIO_t*)0x29)   /* PIND=0x29, DDRD=0x2A, PORTD=0x2B */

static GPIO_t* GPIO_GetPort(u8 port)
{
    switch(port)
    {
        case GPIO_PORTA: return GPIOA;
        case GPIO_PORTB: return GPIOB;
        case GPIO_PORTC: return GPIOC;
        case GPIO_PORTD: return GPIOD;
        default:         return 0;
    }
}

void GPIO_VidSetPinDirection(u8 port, u8 pin, u8 dir)
{
    GPIO_t* GPIOx = GPIO_GetPort(port);
    if(dir == GPIO_OUTPUT)
        SET_BIT(GPIOx->DDR, pin);
    else
        CLR_BIT(GPIOx->DDR, pin);
}

void GPIO_VidSetPinValue(u8 port, u8 pin, u8 value)
{
    GPIO_t* GPIOx = GPIO_GetPort(port);
    if(value == GPIO_HIGH)
        SET_BIT(GPIOx->PORT, pin);
    else
        CLR_BIT(GPIOx->PORT, pin);
}

void GPIO_VidTogglePin(u8 port, u8 pin)
{
    GPIO_t* GPIOx = GPIO_GetPort(port);
    TOGGLE_BIT(GPIOx->PORT, pin);
}

void GPIO_VidSetPortDirection(u8 port, u8 dir)
{
    GPIO_t* GPIOx = GPIO_GetPort(port);
    GPIOx->DDR = dir;
}

void GPIO_VidSetPortValue(u8 port, u8 value)
{
    GPIO_t* GPIOx = GPIO_GetPort(port);
    GPIOx->PORT = value;
}

u8 GPIO_U8GetPinValue(u8 port, u8 pin)
{
    GPIO_t* GPIOx = GPIO_GetPort(port);
    return GET_BIT(GPIOx->PIN, pin);
}
