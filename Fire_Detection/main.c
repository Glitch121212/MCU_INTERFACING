#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO.h"
#include "LCD.h"
#include "ADC.h"
#include "KEYPAD.h"

/* ================= PINS (As per Case Study) ================= */
#define RED_LED   GPIO_enuPIN6 // PORTD
#define GREEN_LED GPIO_enuPIN7 // PORTD
#define BUZZER    GPIO_enuPIN2 // PORTC
#define LM35      GPIO_enuPIN0 // PORTC (ADC0)
#define MQ2       GPIO_enuPIN1 // PORTC (ADC1)

void ALRAM()
{
    for(int i = 0; i < 5; i++) // Flash 5 times
    {
        GPIO_VidSetPinValue(GPIO_enuPORTD, GREEN_LED, GPIO_enuLOW);

        GPIO_VidSetPinValue(GPIO_enuPORTD, RED_LED, GPIO_enuHIGH);
        GPIO_VidSetPinValue(GPIO_enuPORTC, BUZZER, GPIO_enuHIGH);
        _delay_ms(500);
        GPIO_VidSetPinValue(GPIO_enuPORTD, RED_LED, GPIO_enuLOW);
        GPIO_VidSetPinValue(GPIO_enuPORTC, BUZZER, GPIO_enuLOW);
        _delay_ms(500);
    }
}
volatile u16 temp_raw, Gas_raw;
u8 mode = 0;
u16 temp_threshold = 30, Gas_threshold = 50;

/* ================= ADC INTERRUPT (Task 8) ================= */
ISR(ADC_vect) {
    static u8 ch = 0;
    if (ch == 0) {
        temp_raw = ADC;
        ch = 1;
    } else {
        Gas_raw = ADC;
        ch = 0;
    }
    ADMUX = (ADMUX & 0xF0) | ch;
    ADCSRA |= (1 << ADSC); // Start next conversion
}

/* ================= MAIN ================= */
int main(void)
{
    u8 key, select, i;
    u16 value;

    /* INIT Directions */
    GPIO_VidSetPinDirection(GPIO_enuPORTD, RED_LED, GPIO_enuOUTPUT);
    
    GPIO_VidSetPinDirection(GPIO_enuPORTD, GREEN_LED, GPIO_enuOUTPUT);
    GPIO_VidSetPinValue(GPIO_enuPORTD, GREEN_LED, GPIO_enuHIGH);

    GPIO_VidSetPinDirection(GPIO_enuPORTC, BUZZER, GPIO_enuOUTPUT);
    GPIO_VidSetPinDirection(GPIO_enuPORTC, LM35, GPIO_enuINPUT);
    GPIO_VidSetPinDirection(GPIO_enuPORTC, MQ2, GPIO_enuINPUT);

    
        /* ADC Interrupt Setup */
    ADC_VidInit(ADC_enuAVCC, ADC_enuPRESCALER_64, ADC_enu10BIT);
    ADCSRA |= (1 << ADIE); 
    sei(); 
    ADCSRA |= (1 << ADSC); 

    LCD_Init();
    KEYPAD_Init();

    while (1)
    {
        /* ================= MENU ================= */
        LCD_Clear();
        LCD_SetCursor(0,0); LCD_SendString("1:Show");
        LCD_SetCursor(1,0); LCD_SendString("2:Edit");

        mode = 0;
        while (!mode)
        {
            key = Keypad_CheckNum(GPIO_enuPORTB); // Keypad on PORTB
            if (key == '1') { mode = 1; LCD_Clear();        GPIO_VidSetPinValue(GPIO_enuPORTD, GREEN_LED, GPIO_enuLOW);
 }
            if (key == '2') { mode = 2; LCD_Clear(); }
        }

        /* ================= SHOW MODE ================= */
        if (mode == 1)
        {
            while (mode == 1)
            {
                u16 t = (u32)temp_raw * 500 / 1024;
                u16 g = (u32)Gas_raw * 100 / 1024;

                LCD_SetCursor(0,0);
                LCD_SendString("T:"); LCD_SendChar(t/10+'0'); LCD_SendChar(t%10+'0');
                LCD_SendString(" G:"); LCD_SendChar(g/10+'0'); LCD_SendChar(g%10+'0');

                GPIO_VidSetPinValue(GPIO_enuPORTD, GREEN_LED, GPIO_enuHIGH);

                if (t > temp_threshold || g > Gas_threshold) 
                {
                    ALRAM();
                }

                key = Keypad_CheckNum(GPIO_enuPORTB);
                if (key == 'C') mode = 0;
            }
        }

        /* ================= EDIT MODE ================= */
        else if (mode == 2)
        {
            temp_raw = 0; Gas_raw = 0; // Sensors Low
            GPIO_VidSetPinValue(GPIO_enuPORTC, BUZZER, GPIO_enuLOW);
            GPIO_VidSetPinValue(GPIO_enuPORTD, RED_LED, GPIO_enuLOW);

            LCD_SendString("1.Temp 2.Gas");
            select = 0;
            while (!select)
            {
                key = Keypad_CheckNum(GPIO_enuPORTB);
                if (key == '1') { select = 1; LCD_Clear(); LCD_SendString("Set Temp:"); }
                if (key == '2') { select = 2; LCD_Clear(); LCD_SendString("Set Gas:"); }
                if (key == 'C') { select = 3; mode = 0;  while (!mode)
        {
            key = Keypad_CheckNum(GPIO_enuPORTB); // Keypad on PORTB
            if (key == '1') { mode = 1; LCD_Clear(); }
            if (key == '2') { mode = 2; LCD_Clear(); }
        } }
            }

            if (select != 3) 
            {
                value = 0;
                while (1)
                {
                    key = Keypad_CheckNum(GPIO_enuPORTB);
                    if (key >= '0' && key <= '9') {
                        value = value * 10 + (key - '0');
                        LCD_SendChar(key);
                    }
                    else if (key == '=') {
                        if (select == 1) temp_threshold = value;
                        if (select == 2) Gas_threshold = value;
                        ALRAM();
                        
                        break;
                    }
                    else if (key == 'C') { mode = 0; break; }
                }
            }
        }
    }
}
