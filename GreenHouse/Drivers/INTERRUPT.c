#include "INTERRUPT.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static void (*cb0)(void)=0;
static void (*cb1)(void)=0;

void INT0_Init(u8 sense){}
void INT1_Init(u8 sense){}

void INT0_Enable(void){ EIMSK |= (1<<INT0); }
void INT1_Enable(void){ EIMSK |= (1<<INT1); }

void INT0_SetCallback(void (*cb)(void)){ cb0=cb; }
void INT1_SetCallback(void (*cb)(void)){ cb1=cb; }

void GLOBAL_INT_Enable(void){ sei(); }
void GLOBAL_INT_Disable(void){ cli(); }

ISR(INT0_vect){ if(cb0) cb0(); }
ISR(INT1_vect){ if(cb1) cb1(); }
