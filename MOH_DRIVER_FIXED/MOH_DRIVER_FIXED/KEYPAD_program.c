#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/io.h>

#include "KEYPAD_interface.h"

/*
 * Key map [row][col]
 *           Col1  Col2  Col3  Col4
 * Row A  :   7     8     9     /
 * Row B  :   4     5     6     *
 * Row C  :   1     2     3     -
 * Row D  :   C     0     =     +
 */
static const char KEYPAD_Map[4][4] =
{
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'C', '0', '=', '+'}
};

static const u8 Cols[4] = {KEYPAD_COL0, KEYPAD_COL1, KEYPAD_COL2, KEYPAD_COL3};
static const u8 Rows[4] = {KEYPAD_ROW0, KEYPAD_ROW1, KEYPAD_ROW2, KEYPAD_ROW3};

void KEYPAD_Init(void)
{
    u8 i;

    /* Cols -> OUTPUT, idle HIGH */
    for(i = 0; i < 4; i++)
    {
        GPIO_VidSetPinDirection(KEYPAD_PORT, Cols[i], GPIO_OUTPUT);
        GPIO_VidSetPinValue(KEYPAD_PORT, Cols[i], GPIO_HIGH);
    }

    /* Rows -> INPUT with internal pull-up */
    for(i = 0; i < 4; i++)
    {
        GPIO_VidSetPinDirection(KEYPAD_PORT, Rows[i], GPIO_INPUT);
        GPIO_VidSetPinValue(KEYPAD_PORT, Rows[i], GPIO_HIGH);
    }
}

char KEYPAD_GetKey(void)
{
    u8 col, row;

    for(col = 0; col < 4; col++)
    {
        /* Pull this column LOW */
        GPIO_VidSetPinValue(KEYPAD_PORT, Cols[col], GPIO_LOW);
        _delay_ms(2);

        for(row = 0; row < 4; row++)
        {
            if(GPIO_U8GetPinValue(KEYPAD_PORT, Rows[row]) == GPIO_LOW)
            {
                _delay_ms(20);  /* debounce */
                if(GPIO_U8GetPinValue(KEYPAD_PORT, Rows[row]) == GPIO_LOW)
                {
                    /* Wait for key release */
                    while(GPIO_U8GetPinValue(KEYPAD_PORT, Rows[row]) == GPIO_LOW);
                    _delay_ms(10);
                    /* Restore column */
                    GPIO_VidSetPinValue(KEYPAD_PORT, Cols[col], GPIO_HIGH);
                    return KEYPAD_Map[row][col];
                }
            }
        }

        /* Restore column HIGH before next scan */
        GPIO_VidSetPinValue(KEYPAD_PORT, Cols[col], GPIO_HIGH);
    }

    return 0;   /* no key pressed */
}
