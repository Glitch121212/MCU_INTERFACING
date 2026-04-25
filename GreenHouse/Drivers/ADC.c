#include "ADC.h"
#include "BIT_MATH.h"

/* ATmega328P registers */
#define ADMUX   (*(volatile u8*)0x7C)
#define ADCSRA  (*(volatile u8*)0x7A)
#define ADCL    (*(volatile u8*)0x78)
#define ADCH    (*(volatile u8*)0x79)

static void (*cb)(void)=0;

void ADC_Init(u8 ref, u8 prescaler, u8 res)
{
    ADCSRA |= (1<<7);
}

u16 ADC_Read10(u8 ch)
{
    ADMUX = (ADMUX & 0xE0) | ch;
    ADCSRA |= (1<<6);
    while(!(ADCSRA & (1<<4)));
    ADCSRA |= (1<<4);
    return (u16)ADCL | ((u16)ADCH<<8);
}

u8 ADC_Read8(u8 ch)
{
    return (u8)(ADC_Read10(ch)>>2);
}

void ADC_EnableInterrupt(void){ ADCSRA |= (1<<3); }
void ADC_DisableInterrupt(void){ ADCSRA &= ~(1<<3); }

void ADC_SetCallback(void (*f)(void)){ cb=f; }

void __vector_16(void) __attribute__((signal));
void __vector_16(void){ if(cb) cb(); }
