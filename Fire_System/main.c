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
u8  Gas_thr  = 70;

/* ================= MODE ================= */
#define MODE_EDIT 0
#define MODE_RUN  1

u8 system_mode;

/* ================= MAIN ================= */

int main(void)
{
    u8 temp, key, gas;

    /* INIT */
    ADC_VidInit(ADC_enuAVCC, ADC_enuPRESCALER_128, ADC_enu10BIT);
    LCD_Init();
    KEYPAD_Init();
    TIMER0_VidInit(TIMER0_enuCTC_MODE);

    GPIO_VidSetPinDirection(Leds_Port, Red_Led, GPIO_enuOUTPUT);
    GPIO_VidSetPinDirection(Leds_Port, Green_Led, GPIO_enuOUTPUT);
    GPIO_VidSetPinDirection(Buzzer_Port, BUZZER, GPIO_enuOUTPUT);

    /* ================= START MENU ================= */
    LCD_Clear();
    LCD_SendString("1:RUN 2:EDIT");

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
                case '3': Gas_thr += 5; break;
                case '4': if (Gas_thr > 5) Gas_thr -= 5; break;
                case '0': system_mode = MODE_RUN; break;
            }

            LCD_SetCursor(1,0);
            LCD_SendString("T:");
            LCD_PrintNumber(Temp_thr);
            LCD_SendString(" G:");
            LCD_PrintNumber(Gas_thr);

            _delay_ms(50);
        }
    }

    /* ================= RUN MODE ================= */
    LCD_Clear();
    LCD_SendString("RUN MODE");

    /* 🔥 IMMEDIATE ALERT WHEN ENTER RUN */
    GPIO_VidSetPinValue(Leds_Port, Red_Led, GPIO_enuHIGH);
    GPIO_VidSetPinValue(Leds_Port, Green_Led, GPIO_enuLOW);
    GPIO_VidSetPinValue(Buzzer_Port, BUZZER, GPIO_enuHIGH);

    LCD_SetCursor(1,0);
    LCD_SendString("FIRE ALERT ");

    _delay_ms(500);  // show alert first

    while (1)
    {
        key = Keypad_CheckNum(PORTB);

        if (key == '0')
        {
            LCD_Clear();
            LCD_SendString("EDIT MODE");
            system_mode = MODE_EDIT;
            break;
        }

        /* ================= READ SENSORS ================= */
        temp = (u8)((ADC_U16ReadChannel(ADC_enuCHANNEL_0) * 500UL) / 1023);
        gas  = (u8)((ADC_U16ReadChannel(ADC_enuCHANNEL_1) * 100UL) / 1023);

        /* ================= NORMAL LOGIC ================= */
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