#include "TEMP.h"
#include "GPIO.h"

// default values (can be updated by keypad) 
u16 temp_threshold = 30;
u16 moisture_threshold = 300;
u16 light_threshold = 200;

u8 alarm_count = 0;   // total alarms

 // ========================================================= 
// LM35 conversion */
//  ========================================================= 

u16 LM35_ReadTemp(u16 adc_value)
{
    u16 temp;

    temp = (adc_value * 5 * 100) / 1024; 
    // convert ADC value to °C

    return temp;
}

// ========================================================= 
 // Threshold checking 
// ========================================================= 

void CheckThresholds(u16 temp, u16 moisture, u16 light)
{
    u8 alarm_flag = 0;     
    static u8 prev_alarm = 0; // last state

    if(temp > temp_threshold)
    {
        alarm_flag = 1;   // high temp
    }

    if(moisture < moisture_threshold)
    {
        alarm_flag = 1;   // low moisture
    }

    if(light < light_threshold)
    {
        alarm_flag = 1;   // low light
    }

    if(alarm_flag)
    {
        GPIO_WritePin(GPIO_PORTD, PIN7, GPIO_HIGH); // buzzer ON

        if(!prev_alarm)
        {
            alarm_count++; // count once per event
        }
    }
    else
    {
        GPIO_WritePin(GPIO_PORTD, PIN7, GPIO_LOW); // buzzer OFF
    }

    prev_alarm = alarm_flag; // update state
}