#ifndef TIMER0_INTERFACE_H
#define TIMER0_INTERFACE_H

#include "STD_TYPES.h"

/* Modes */
typedef enum
{
    TIMER0_enuNORMAL_MODE = 0,
    TIMER0_enuCTC_MODE
} TIMER0_enuMode_t;

/* Clock */
typedef enum
{
    TIMER0_enuNO_CLOCK = 0,
    TIMER0_enuNO_PRESCALER,
    TIMER0_enuPRESCALER_8,
    TIMER0_enuPRESCALER_64,
    TIMER0_enuPRESCALER_256,
    TIMER0_enuPRESCALER_1024,
    TIMER0_enuEXT_FALLING,
    TIMER0_enuEXT_RISING
} TIMER0_enuClock_t;

/* APIs */
void TIMER0_VidInit(TIMER0_enuMode_t Copy_enuMode);
void TIMER0_VidStart(TIMER0_enuClock_t Copy_enuClock);
void TIMER0_VidStop(void);

void TIMER0_VidSetPreload(u8 Copy_u8Value);
void TIMER0_VidSetCompareMatch(u8 Copy_u8Value);

/* Interrupts */
void TIMER0_VidEnableOVFInterrupt(void);
void TIMER0_VidEnableCTCInterrupt(void);
void TIMER0_VidDisableInterrupts(void);

void TIMER0_VidDelay_ms(u32 delay);

/* Callbacks */
void TIMER0_VidSetOVFCallBack(void (*ptr)(void));
void TIMER0_VidSetCTCCallBack(void (*ptr)(void));

void TIMER0_VidDelay_ms(u32 delay);

#endif