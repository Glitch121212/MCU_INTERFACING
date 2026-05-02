#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include "STD_TYPES.h"

/* ========== ENUMS ========== */

/* Reference Voltage */
typedef enum
{
    ADC_enuAREF = 0,
    ADC_enuAVCC,
    ADC_enuINTERNAL_1V1
} ADC_enuReference_t;

/* Resolution */
typedef enum
{
    ADC_enu10BIT = 0,
    ADC_enu8BIT
} ADC_enuResolution_t;

/* Prescaler */
typedef enum
{
    ADC_enuPRESCALER_2 = 1,
    ADC_enuPRESCALER_4,
    ADC_enuPRESCALER_8,
    ADC_enuPRESCALER_16,
    ADC_enuPRESCALER_32,
    ADC_enuPRESCALER_64,
    ADC_enuPRESCALER_128
} ADC_enuPrescaler_t;

/* Channels */
typedef enum
{
    ADC_enuCHANNEL_0 = 0,
    ADC_enuCHANNEL_1,
    ADC_enuCHANNEL_2,
    ADC_enuCHANNEL_3,
    ADC_enuCHANNEL_4,
    ADC_enuCHANNEL_5
} ADC_enuChannel_t;

/* ========== APIs ========== */

void ADC_VidInit(ADC_enuReference_t Copy_enuRef, ADC_enuPrescaler_t Copy_enuPrescaler, ADC_enuResolution_t Copy_enuResolution);

/* Polling */
u16 ADC_U16ReadChannel(ADC_enuChannel_t Copy_enuChannel);
u8  ADC_U8ReadChannel(ADC_enuChannel_t Copy_enuChannel);

/* Interrupt */
void ADC_VidEnableInterrupt(void);
void ADC_VidDisableInterrupt(void);
void ADC_VidSetCallBack(void (*ptr)(void));

#endif