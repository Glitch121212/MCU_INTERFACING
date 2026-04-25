#ifndef ADC_H
#define ADC_H

#include "STD_TYPES.h"

#define ADC_REF_AREF 0
#define ADC_REF_AVCC 1
#define ADC_REF_INTERNAL 2

#define ADC_PRESCALER_2   1
#define ADC_PRESCALER_4   2
#define ADC_PRESCALER_8   3
#define ADC_PRESCALER_16  4
#define ADC_PRESCALER_32  5
#define ADC_PRESCALER_64  6
#define ADC_PRESCALER_128 7

#define ADC_RES_10BIT 0
#define ADC_RES_8BIT  1

#define ADC_CH0 0
#define ADC_CH1 1
#define ADC_CH2 2
#define ADC_CH3 3
#define ADC_CH4 4
#define ADC_CH5 5
#define ADC_CH6 6
#define ADC_CH7 7

void ADC_Init(u8 ref, u8 prescaler, u8 res);
u16 ADC_Read10(u8 ch);
u8 ADC_Read8(u8 ch);

void ADC_EnableInterrupt(void);
void ADC_DisableInterrupt(void);
void ADC_SetCallback(void (*cb)(void));

#endif
