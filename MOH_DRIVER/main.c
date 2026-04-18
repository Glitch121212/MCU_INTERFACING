#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "LCD.h"
#include "KEYPAD_interface.h"

/* ---- helpers ---- */
static void LCD_SendInt(s32 n)
{
    char buf[12];
    u8   i = 0;
    u8   neg = 0;

    if(n == 0) { LCD_SendChar('0'); return; }

    if(n < 0) { neg = 1; n = -n; }

    while(n > 0)
    {
        buf[i++] = (char)('0' + (n % 10));
        n /= 10;
    }

    if(neg) buf[i++] = '-';

    /* Reverse */
    u8 j;
    for(j = 0; j < i / 2; j++)
    {
        char tmp = buf[j];
        buf[j]   = buf[i - 1 - j];
        buf[i - 1 - j] = tmp;
    }
    buf[i] = '\0';
    LCD_SendString(buf);
}

/* ---- main ---- */
int main(void)
{
    LCD_Init();
    KEYPAD_Init();

    s32  operand1  = 0;
    s32  operand2  = 0;
    char operation = 0;
    u8   entering  = 1;
    u8   fresh     = 1;

    LCD_SendString("Calculator");
    LCD_SetCursor(1, 0);
    LCD_SendChar('0');

    while(1)
    {
        char key = KEYPAD_GetKey();
        if(!key) continue;

        if(key == 'C')
        {
            operand1  = 0; operand2 = 0;
            operation = 0; entering = 1; fresh = 1;
            LCD_Clear();
            LCD_SendString("Calculator");
            LCD_SetCursor(1, 0); LCD_SendChar('0');
            continue;
        }

        if(key >= '0' && key <= '9')
        {
            u8 digit = (u8)(key - '0');
            if(entering == 1)
            {
                if(fresh) { operand1 = 0; fresh = 0; }
                operand1 = operand1 * 10 + digit;
                LCD_SetCursor(1, 0); LCD_SendString("                ");
                LCD_SetCursor(1, 0); LCD_SendInt(operand1);
            }
            else
            {
                if(fresh) { operand2 = 0; fresh = 0; }
                operand2 = operand2 * 10 + digit;
                LCD_SetCursor(1, 0); LCD_SendString("                ");
                LCD_SetCursor(1, 0); LCD_SendInt(operand2);
            }
            continue;
        }

        if(key == '+' || key == '-' || key == '*' || key == '/')
        {
            operation = key; entering = 2; fresh = 1;
            LCD_SetCursor(0, 0); LCD_SendString("                ");
            LCD_SetCursor(0, 0); LCD_SendInt(operand1);
            LCD_SendChar(' '); LCD_SendChar(operation);
            LCD_SetCursor(1, 0); LCD_SendString("                ");
            LCD_SetCursor(1, 0); LCD_SendChar('0');
            continue;
        }

        if(key == '=')
        {
            if(operation == 0) continue;
            s32 result = 0;
            switch(operation)
            {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/':
                    if(operand2 == 0)
                    {
                        LCD_Clear(); LCD_SendString("Error: Div/0");
                        _delay_ms(2000);
                        operand1 = 0; operand2 = 0;
                        operation = 0; entering = 1; fresh = 1;
                        LCD_Clear(); LCD_SendString("Calculator");
                        LCD_SetCursor(1, 0); LCD_SendChar('0');
                        continue;
                    }
                    result = operand1 / operand2; break;
            }
            LCD_Clear();
            LCD_SendInt(operand1); LCD_SendChar(operation); LCD_SendInt(operand2); LCD_SendChar('=');
            LCD_SetCursor(1, 0); LCD_SendInt(result);
            operand1 = result; operand2 = 0;
            operation = 0; entering = 1; fresh = 1;
        }
    }
}
