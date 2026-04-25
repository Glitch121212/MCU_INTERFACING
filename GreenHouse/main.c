#include "TEMP.h"

/* ADC values from ISR */
extern volatile u16 adc_ch0; // temp
extern volatile u16 adc_ch1; // moisture
extern volatile u16 adc_ch2; // light

int main(void)
{
    u16 temp;

    while(1)
    {
        temp = LM35_ReadTemp(adc_ch0); // convert temp

        CheckThresholds(temp, adc_ch1, adc_ch2); // check system
    }
}