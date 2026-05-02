#include "ADC.h"
#include "BIT_MATH.h"

/* Registers */
#define ADMUX   (*(volatile u8*)0x7C)
#define ADCSRA  (*(volatile u8*)0x7A)
#define ADCSRB  (*(volatile u8*)0x7B)
#define ADCL    (*(volatile u8*)0x78)
#define ADCH    (*(volatile u8*)0x79)
#define ADC     (*(volatile u16*)0x78)
#define DIDR0   (*(volatile u8*)0x7E)
#define SREG    (*(volatile u8*)0x5F)

/* Bits */
#define REFS0   6
#define REFS1   7
#define ADLAR   5

#define ADEN    7
#define ADSC    6
#define ADIE    3

/* Callback */
static void (*ADC_CallBack)(void) = 0;

/* ================= INIT ================= */

void ADC_VidInit(ADC_enuReference_t Copy_enuRef, ADC_enuPrescaler_t Copy_enuPrescaler, ADC_enuResolution_t Copy_enuResolution)
{
    /* Reference */
    ADMUX &= ~(0xC0);

    switch (Copy_enuRef)
    {
        case ADC_enuAREF:
            break;

        case ADC_enuAVCC:
            SET_BIT(ADMUX, REFS0);
            break;

        case ADC_enuINTERNAL_1V1:
            SET_BIT(ADMUX, REFS0);
            SET_BIT(ADMUX, REFS1);
            break;
    }

    /* Resolution */
    if (Copy_enuResolution == ADC_enu8BIT)
        SET_BIT(ADMUX, ADLAR);
    else
        CLR_BIT(ADMUX, ADLAR);

    /* Prescaler */
    ADCSRA &= 0xF8;
    ADCSRA |= Copy_enuPrescaler;

    /* Enable ADC */
    SET_BIT(ADCSRA, ADEN);
}

/* ================= POLLING ================= */

u16 ADC_U16ReadChannel(ADC_enuChannel_t Copy_enuChannel)
{
    ADMUX = (ADMUX & 0xE0) | Copy_enuChannel;

    SET_BIT(DIDR0, Copy_enuChannel);

    SET_BIT(ADCSRA, ADSC);

    while (GET_BIT(ADCSRA, ADSC));

    return ADC;
}

u8 ADC_U8ReadChannel(ADC_enuChannel_t Copy_enuChannel)
{
    ADMUX = (ADMUX & 0xE0) | Copy_enuChannel;

    SET_BIT(DIDR0, Copy_enuChannel);

    SET_BIT(ADCSRA, ADSC);

    while (GET_BIT(ADCSRA, ADSC));

    return ADCH;
}

/* ================= INTERRUPT ================= */

void ADC_VidEnableInterrupt(void)
{
    SET_BIT(ADCSRA, ADIE);
    SET_BIT(SREG, 7);
}

void ADC_VidDisableInterrupt(void)
{
    CLR_BIT(ADCSRA, ADIE);
}

void ADC_VidSetCallBack(void (*ptr)(void))
{
    ADC_CallBack = ptr;
}

/* ISR */
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
    if (ADC_CallBack)
        ADC_CallBack();
}