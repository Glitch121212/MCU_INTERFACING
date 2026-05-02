#define F_CPU 10000000UL
#include <util/delay.h>

#include "KEYPAD.h"

/* ===== ARRAYS ===== */
static u8 KEYPAD_Rows[4] = {KEYPAD_Row0, KEYPAD_Row1, KEYPAD_Row2, KEYPAD_Row3};
static u8 KEYPAD_Cols[4] = {KEYPAD_Col0, KEYPAD_Col1, KEYPAD_Col2, KEYPAD_Col3};

static u8 KEYPAD_Map[4][4] =
{
    {'7','8','9','/'},
    {'4','5','6','*'},
    {'1','2','3','-'},
    {'C','0','=','+'}
};

/* ===== INIT ===== */
void KEYPAD_Init()
{
    for(u8 i=0;i<4;i++)
    {
        GPIO_VidSetPinDirection(KEYPAD_PORT, KEYPAD_Cols[i], GPIO_enuOUTPUT);
        GPIO_VidSetPinValue(KEYPAD_PORT, KEYPAD_Cols[i], GPIO_enuHIGH);
    }

    for(u8 i=0;i<4;i++)
    {
        GPIO_VidSetPinDirection(KEYPAD_PORT, KEYPAD_Rows[i], GPIO_enuINPUT);
        GPIO_VidSetPinValue(KEYPAD_PORT, KEYPAD_Rows[i], GPIO_enuHIGH);
    }
}

/* ===== GET KEY ===== */
u8 Keypad_CheckNum(u8 port)
{
    for(u8 i=0;i<4;i++)
    {
        GPIO_VidSetPinValue(KEYPAD_PORT, KEYPAD_Cols[i], GPIO_enuLOW);

        for(u8 j=0;j<4;j++)
        {
            if(GPIO_U8GetPinValue(KEYPAD_PORT, KEYPAD_Rows[j]) == GPIO_enuLOW)
            {
                _delay_ms(20);

                while(GPIO_U8GetPinValue(KEYPAD_PORT, KEYPAD_Rows[j]) == GPIO_enuLOW);

                GPIO_VidSetPinValue(KEYPAD_PORT, KEYPAD_Cols[i], GPIO_enuHIGH);

                return KEYPAD_Map[j][i];
            }
        }

        GPIO_VidSetPinValue(KEYPAD_PORT, KEYPAD_Cols[i], GPIO_enuHIGH);
    }

    return 0xFF;   // no key
}