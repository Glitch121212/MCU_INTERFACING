#include "GPIO.h"

/* ================== Set Pin Direction ================== */
void GPIO_VidSetPinDirection(GPIO_enuPort_t Copy_enuPort,   GPIO_enuPin_t Copy_enuPin,  GPIO_enuDirection_t Copy_enuDirection)
{
    if (Copy_enuDirection == GPIO_enuINPUT)
    {
        switch (Copy_enuPort)
        {
            case GPIO_enuPORTB: CLR_BIT(DDRB, Copy_enuPin); break;
            case GPIO_enuPORTC: CLR_BIT(DDRC, Copy_enuPin); break;
            case GPIO_enuPORTD: CLR_BIT(DDRD, Copy_enuPin); break;
        }
    }
    else
    {
        switch (Copy_enuPort)
        {
            case GPIO_enuPORTB: SET_BIT(DDRB, Copy_enuPin); break;
            case GPIO_enuPORTC: SET_BIT(DDRC, Copy_enuPin); break;
            case GPIO_enuPORTD: SET_BIT(DDRD, Copy_enuPin); break;
        }
    }
}

/* ================== Set Pin Value ================== */
void GPIO_VidSetPinValue(GPIO_enuPort_t Copy_enuPort,  GPIO_enuPin_t Copy_enuPin, GPIO_enuValue_t Copy_enuValue)
{
    if (Copy_enuValue == GPIO_enuLOW)
    {
        switch (Copy_enuPort)
        {
            case GPIO_enuPORTB: CLR_BIT(PORTB, Copy_enuPin); break;
            case GPIO_enuPORTC: CLR_BIT(PORTC, Copy_enuPin); break;
            case GPIO_enuPORTD: CLR_BIT(PORTD, Copy_enuPin); break;
        }
    }
    else
    {
        switch (Copy_enuPort)
        {
            case GPIO_enuPORTB: SET_BIT(PORTB, Copy_enuPin); break;
            case GPIO_enuPORTC: SET_BIT(PORTC, Copy_enuPin); break;
            case GPIO_enuPORTD: SET_BIT(PORTD, Copy_enuPin); break;
        }
    }
}

/* ================== Set Port Direction ================== */
void GPIO_VidSetPortDirection(GPIO_enuPort_t Copy_enuPort, u8 Copy_u8Direction)
{
    switch (Copy_enuPort)
    {
        case GPIO_enuPORTB: DDRB = Copy_u8Direction; break;
        case GPIO_enuPORTC: DDRC = Copy_u8Direction; break;
        case GPIO_enuPORTD: DDRD = Copy_u8Direction; break;
    }
}

/* ================== Set Port Value ================== */
void GPIO_VidSetPortValue(GPIO_enuPort_t Copy_enuPort, u8 Copy_u8Value)
{
    switch (Copy_enuPort)
    {
        case GPIO_enuPORTB: PORTB = Copy_u8Value; break;
        case GPIO_enuPORTC: PORTC = Copy_u8Value; break;
        case GPIO_enuPORTD: PORTD = Copy_u8Value; break;
    }
}

/* ================== Toggle Pin ================== */
void GPIO_VidTogglePinValue(GPIO_enuPort_t Copy_enuPort,   GPIO_enuPin_t Copy_enuPin)
{
    switch (Copy_enuPort)
    {
        case GPIO_enuPORTB: TOGGLE_BIT(PORTB, Copy_enuPin); break;
        case GPIO_enuPORTC: TOGGLE_BIT(PORTC, Copy_enuPin); break;
        case GPIO_enuPORTD: TOGGLE_BIT(PORTD, Copy_enuPin); break;
    }
}

/* ================== Get Pin Value ================== */
u8 GPIO_U8GetPinValue(GPIO_enuPort_t Copy_enuPort, GPIO_enuPin_t Copy_enuPin)
{
    u8 Local_u8Value = 0;

    switch (Copy_enuPort)
    {
        case GPIO_enuPORTB: Local_u8Value = GET_BIT(PINB, Copy_enuPin); break;
        case GPIO_enuPORTC: Local_u8Value = GET_BIT(PINC, Copy_enuPin); break;
        case GPIO_enuPORTD: Local_u8Value = GET_BIT(PIND, Copy_enuPin); break;
    }

    return Local_u8Value;
}

/* ================== Get Port Value ================== */
u8 GPIO_U8GetPortValue(GPIO_enuPort_t Copy_enuPort)
{
    u8 Local_u8Value = 0;

    switch (Copy_enuPort)
    {
        case GPIO_enuPORTB: Local_u8Value = PINB; break;
        case GPIO_enuPORTC: Local_u8Value = PINC; break;
        case GPIO_enuPORTD: Local_u8Value = PIND; break;
    }

    return Local_u8Value;
}