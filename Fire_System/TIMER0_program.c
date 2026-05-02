#define F_CPU 1000000UL

#include "TIMER0_interface.h"
#include "BIT_MATH.h"

/* ========== Registers (ATmega328P) ========== */

#define TCCR0A   (*(volatile u8*)0x44)
#define TCCR0B   (*(volatile u8*)0x45)
#define TCNT0    (*(volatile u8*)0x46)
#define OCR0A    (*(volatile u8*)0x47)
#define TIMSK0   (*(volatile u8*)0x6E)
#define TIFR0    (*(volatile u8*)0x35)
#define SREG     (*(volatile u8*)0x5F)

/* ========== Bits ========== */

#define WGM01   1

#define CS00    0
#define CS01    1
#define CS02    2

#define TOIE0   0
#define OCIE0A  1

#define OCF0A   1

/* ========== Callbacks ========== */

static void (*TIMER0_OVF_CallBack)(void) = 0;
static void (*TIMER0_CTC_CallBack)(void) = 0;

/* ================= INIT ================= */

void TIMER0_VidInit(TIMER0_enuMode_t Copy_enuMode)
{
    TCCR0A = 0;
    TCCR0B = 0;

    switch (Copy_enuMode)
    {
        case TIMER0_enuNORMAL_MODE:
            break;

        case TIMER0_enuCTC_MODE:
            SET_BIT(TCCR0A, WGM01);
            break;
    }
}

/* ================= START ================= */

void TIMER0_VidStart(TIMER0_enuClock_t Copy_enuClock)
{
    TCCR0B &= 0xF8;
    TCCR0B |= Copy_enuClock;

    /* Enable Global Interrupt */
    SET_BIT(SREG,7);
}

/* ================= STOP ================= */

void TIMER0_VidStop(void)
{
    TCCR0B &= 0xF8;
}

/* ================= CONTROL ================= */

void TIMER0_VidSetPreload(u8 Copy_u8Value)
{
    TCNT0 = Copy_u8Value;
}

void TIMER0_VidSetCompareMatch(u8 Copy_u8Value)
{
    OCR0A = Copy_u8Value;
}

/* ================= INTERRUPTS ================= */

void TIMER0_VidEnableOVFInterrupt(void)
{
    SET_BIT(TIMSK0, TOIE0);
}

void TIMER0_VidEnableCTCInterrupt(void)
{
    SET_BIT(TIMSK0, OCIE0A);
}

void TIMER0_VidDisableInterrupts(void)
{
    CLR_BIT(TIMSK0, TOIE0);
    CLR_BIT(TIMSK0, OCIE0A);
}

/* ================= CALLBACKS ================= */

void TIMER0_VidSetOVFCallBack(void (*ptr)(void))
{
    TIMER0_OVF_CallBack = ptr;
}

void TIMER0_VidSetCTCCallBack(void (*ptr)(void))
{
    TIMER0_CTC_CallBack = ptr;
}



/* ================= ISR ================= */

/* TIMER0 OVF */
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
    if (TIMER0_OVF_CallBack)
        TIMER0_OVF_CallBack();
}

/* TIMER0 CTC */
void __vector_14(void) __attribute__((signal));
void __vector_14(void)
{
    if (TIMER0_CTC_CallBack)
        TIMER0_CTC_CallBack();
}

void TIMER0_VidDelay_ms(u32 delay){
    
    TIMER0_VidInit(TIMER0_enuCTC_MODE);

    OCR0A = 15; 

    while (delay--)
    {
        TCNT0 = 0;
        SET_BIT(TIFR0, 1);
        TIMER0_VidStart(TIMER0_enuPRESCALER_64);

        while (GET_BIT(TIFR0, 1) == 0);

        TIMER0_VidStop();
    }
}
