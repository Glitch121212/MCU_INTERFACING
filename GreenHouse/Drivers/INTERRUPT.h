#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "STD_TYPES.h"

#define LOW_LEVEL 0
#define ANY_CHANGE 1
#define RISING 2
#define FALLING 3

void INT0_Init(u8 sense);
void INT1_Init(u8 sense);

void INT0_Enable(void);
void INT1_Enable(void);

void INT0_SetCallback(void (*cb)(void));
void INT1_SetCallback(void (*cb)(void));

void GLOBAL_INT_Enable(void);
void GLOBAL_INT_Disable(void);

#endif
