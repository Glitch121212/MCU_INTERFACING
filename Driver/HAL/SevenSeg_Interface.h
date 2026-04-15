#ifndef SEVENSEG_INTERFACE_H
#define SEVENSEG_INTERFACE_H

#include "STD_TYPES.h"

/* Seven Segment Types */
#define SEVENSEG_COMMON_CATHODE  0
#define SEVENSEG_COMMON_ANODE    1

/* Functions */
void SEVENSEG_VidInit(u8 Copy_U8Port);
void SEVENSEG_VidDisplayNumber(u8 Copy_U8Port, u8 Copy_U8Number);

/* Optional (advanced use) */
void SEVENSEG_Display(u8 port, u8 num, u8 type);

#endif