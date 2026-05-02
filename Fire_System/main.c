#define F_CPU 1000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC.h"
#include "GPIO.h"
#include "TIMER0_interface.h"
#include "KEYPAD.h"
#include "LCD.h"

/* ================= PINS ================= */
#define Leds_Port   GPIO_enuPORTD
#define Red_Led     GPIO_enuPIN6
#define Green_Led   GPIO_enuPIN7

#define Buzzer_Port GPIO_enuPORTC
#define BUZZER      GPIO_enuPIN2

/* ================= THRESHOLDS ================= */
u8  Temp_thr = 50;
u16 Gas_thr  = 70;

/* ================= MODE ================= */
#define MODE_EDIT 0
#define MODE_RUN  1

u8 system_mode;

/* ================= MAIN ================= */

int main(void)
{
    u8 temp, key;
    u16 gas;

    /* INIT */
    ADC_VidInit(ADC_enuAVCC, ADC_enuPRESCALER_128, ADC_enu10BIT);
    LCD_Init();
    KEYPAD_Init();
    TIMER0_VidInit(TIMER0_enuCTC_MODE);

    GPIO_VidSetPinDirection(Leds_Port, Red_Led, GPIO_enuOUTPUT);
    GPIO_VidSetPinDirection(Leds_Port, Green_Led, GPIO_enuOUTPUT);
    GPIO_VidSetPinDirection(Buzzer_Port, BUZZER, GPIO_enuOUTPUT);

    LCD_Clear();
    LCD_SendString("1:RUN 2:EDIT");

    /* ================= MODE SELECT ================= */
    while (1)
    {
        key = Keypad_CheckNum(PORTB);

        if (key == '1')
        {
            system_mode = MODE_RUN;
            break;
        }
        else if (key == '2')
        {
            system_mode = MODE_EDIT;
            break;
        }
    }

    LCD_Clear();

    /* ================= EDIT MODE ================= */
    if (system_mode == MODE_EDIT)
    {
        LCD_SendString("EDIT MODE");

        while (system_mode == MODE_EDIT)
        {
            key = Keypad_CheckNum(PORTB);

            switch (key)
            {
                case '1': Temp_thr += 5; break;
                case '2': if (Temp_thr > 5) Temp_thr -= 5; break;
                case '3': Gas_thr += 10; break;
                case '4': if (Gas_thr > 10) Gas_thr -= 10; break;

                case '0': system_mode = MODE_RUN; break; // switch to run
            }

            LCD_SetCursor(1,0);
            LCD_SendString("T:");
            LCD_PrintNumber(Temp_thr);
            LCD_SendString(" G:");
            LCD_PrintNumber(Gas_thr);

            _delay_ms(50);
        }
    }

    LCD_Clear();
    LCD_SendString("RUN MODE");

    /* ================= RUN MODE ================= */
    while (1)
    {
        key = Keypad_CheckNum(PORTB);

        /* optional return to edit */
        if (key == '0')
        {
            LCD_Clear();
            LCD_SendString("EDIT MODE");

            system_mode = MODE_EDIT;
            break;
        }

        temp = (u8)((ADC_U16ReadChannel(ADC_enuCHANNEL_0) * 500UL) / 1024.0);
        gas  = ADC_U16ReadChannel(ADC_enuCHANNEL_1);
        gas_adc = ADC_U16ReadChannel(ADC_enuCHANNEL_1);
        gas = (u8)((gas_adc * 100UL) / 1024.0);

        if (temp >= Temp_thr || gas >= Gas_thr)
        {
            GPIO_VidSetPinValue(Leds_Port, Red_Led, GPIO_enuHIGH);
            GPIO_VidSetPinValue(Leds_Port, Green_Led, GPIO_enuLOW);
            GPIO_VidSetPinValue(Buzzer_Port, BUZZER, GPIO_enuHIGH);

            LCD_SetCursor(1,0);
            LCD_SendString("FIRE ALERT ");
        }
        else
        {
            GPIO_VidSetPinValue(Leds_Port, Red_Led, GPIO_enuLOW);
            GPIO_VidSetPinValue(Leds_Port, Green_Led, GPIO_enuHIGH);
            GPIO_VidSetPinValue(Buzzer_Port, BUZZER, GPIO_enuLOW);

            LCD_SetCursor(1,0);
            LCD_SendString("SAFE       ");
        }

        _delay_ms(50);   
    }
}