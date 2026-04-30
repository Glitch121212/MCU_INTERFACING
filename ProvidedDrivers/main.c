/* 
 * File:   main.c
 * Author: Muhammed.Hany
 *
 * Created on April 29, 2026, 10:37 AM
 */

#include "GPIO.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "LCD.h"
#include "Keypad.h"
#include "ADC.h"
#include "TIMER0_interface.h"
#define F_CPU 1000000UL
#include <util/delay.h>


/* Values */
u16 temp_value = 0;
u16 soil_value = 0;
u16 light_value = 0;

/* Thresholds */
u16 temp_thr = 30;
u16 soil_thr = 300;
u16 light_thr = 300;

int main(void)
{
    LCD_Init();
    Keypad_init(GPIO_enuPORTC);

    ADC_VidInit(ADC_enuAREF , ADC_enuPRESCALER_128 , ADC_enu10BIT);

    GPIO_VidSetPinDirection(GPIO_enuPORTD , GPIO_enuPIN7 , GPIO_enuOUTPUT);

    while(1)
    {
        /* ================= POLLING ONLY ================= */
        temp_value  = ADC_U16ReadChannel(ADC_enuCHANNEL_3);
        soil_value  = ADC_U16ReadChannel(ADC_enuCHANNEL_4);
        light_value = ADC_U16ReadChannel(ADC_enuCHANNEL_5);

        /* scaling */
        temp_value  = (temp_value * 500.0) / 1023.0;
        soil_value  = (soil_value * 100.0) / 1023.0;
        light_value = (light_value * 100.0) / 1023.0;

        /* ================= LCD ================= */
        LCD_Clear();

        LCD_SetCursor(0,0);
        LCD_SendString("T:");
        LCD_SendChar(temp_value + '0');
        //1        LCD_SendNumber(u16)

        LCD_SetCursor(0,8);
        LCD_SendString("S:");
        LCD_SendChar(soil_value + '0');

        LCD_SetCursor(1,8);
        LCD_SendString("L:");
        LCD_SendChar(light_value + '0');

        /* ================= THRESHOLD ================= */
        if(temp_value > temp_thr || soil_value < soil_thr || light_value < light_thr)
        {
            GPIO_VidSetPinValue(GPIO_enuPORTD , GPIO_enuPIN7 , GPIO_enuHIGH);
        }
        else
        {
            GPIO_VidSetPinValue(GPIO_enuPORTD , GPIO_enuPIN7 , GPIO_enuLOW);
        }
        
        if(soil_value > soil_thr)
        {
            GPIO_VidSetPinValue(GPIO_enuPORTC , GPIO_enuPIN1 , GPIO_enuHIGH);

        }
        else
        {
            GPIO_VidSetPinValue(GPIO_enuPORTC , GPIO_enuPIN1 , GPIO_enuHIGH);
        }

        /* ================= KEYPAD ================= */
        u8 key = Keypad_CheckNum(GPIO_enuPORTD);

        if(key == 1)
        {
            
        }
        if(key != 0xFF)
        {
            if(key == 1)
                temp_thr += 5;

            else if(key == 2)
                soil_thr += 10;

            else if(key == 3)
                light_thr += 5;
        }

        TIMER0_VidDelay_ms(500);
    }
}