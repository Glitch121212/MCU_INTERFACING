#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/io.h>

#include "KEYPAD_interface.h"

/* 4x4 key map */
static const char KEYPAD_Map[4][4] =
{
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'C', '0', '=', '+'}
};

static const u8 Rows[4] = {KEYPAD_ROW0, KEYPAD_ROW1, KEYPAD_ROW2, KEYPAD_ROW3};
static const u8 Cols[4] = {KEYPAD_COL0, KEYPAD_COL1, KEYPAD_COL2, KEYPAD_COL3};

void KEYPAD_Init(void)
{
    u8 i;

    /* Rows -> OUTPUT, initially HIGH */
    for(i = 0; i < 4; i++)
    {
        GPIO_VidSetPinDirection(KEYPAD_PORT, Rows[i], GPIO_OUTPUT);
        GPIO_VidSetPinValue(KEYPAD_PORT, Rows[i], GPIO_HIGH);
    }

    /* Columns -> INPUT with internal pull-up */
    for(i = 0; i < 4; i++)
    {
        GPIO_VidSetPinDirection(KEYPAD_PORT, Cols[i], GPIO_INPUT);
        GPIO_VidSetPinValue(KEYPAD_PORT, Cols[i], GPIO_HIGH);   /* enable pull-up */
    }
}

char KEYPAD_GetKey(void)
{
    u8 row, col;

    for(row = 0; row < 4; row++)
    {
        /* Pull current row LOW */
        GPIO_VidSetPinValue(KEYPAD_PORT, Rows[row], GPIO_LOW);
        _delay_ms(5);

        for(col = 0; col < 4; col++)
        {
            if(GPIO_U8GetPinValue(KEYPAD_PORT, Cols[col]) == GPIO_LOW)
            {
                /* Debounce */
                _delay_ms(20);
                if(GPIO_U8GetPinValue(KEYPAD_PORT, Cols[col]) == GPIO_LOW)
                {
                    /* Wait for release */
                    while(GPIO_U8GetPinValue(KEYPAD_PORT, Cols[col]) == GPIO_LOW);
                    GPIO_VidSetPinValue(KEYPAD_PORT, Rows[row], GPIO_HIGH);
                    return KEYPAD_Map[row][col];
                }
            }
        }

        /* Restore row HIGH */
        GPIO_VidSetPinValue(KEYPAD_PORT, Rows[row], GPIO_HIGH);
    }

    return 0;   /* no key pressed */
}
