#ifndef TEMP_H
#define TEMP_H

#include "STD_TYPES.h"

/* thresholds from keypad */
extern u16 temp_threshold;
extern u16 moisture_threshold;
extern u16 light_threshold;

/* alarm counter */
extern u8 alarm_count;

/* functions */
u16 LM35_ReadTemp(u16 adc_value);          // ADC -> temperature
void CheckThresholds(u16 temp, u16 moisture, u16 light); // compare & control buzzer

#endif