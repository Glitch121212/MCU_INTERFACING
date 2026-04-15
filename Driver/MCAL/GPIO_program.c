#include "GPIO_interface.h"
#include "BIT_MATH.h"

/* Register Struct */
typedef struct
{
    volatile u8 PIN;
    volatile u8 DDR;
    volatile u8 PORT;
} GPIO_t;

/* Base Addresses (ATmega328P) */
#define GPIOA ((GPIO_t*)0x39)
#define GPIOB ((GPIO_t*)0x23)
#define GPIOC ((GPIO_t*)0x26)
#define GPIOD ((GPIO_t*)0x1F)

/* Private */
static GPIO_t* GPIO_GetPort(u8 port)
{
    switch(port)
    {
        case GPIO_PORTA: return GPIOA;
        case GPIO_PORTB: return GPIOB;
        case GPIO_PORTC: return GPIOC;
        case GPIO_PORTD: return GPIOD;
        default: return 0;
    }
}

/* APIs */

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