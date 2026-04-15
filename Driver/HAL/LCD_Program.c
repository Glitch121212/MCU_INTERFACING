#include <util/delay.h>
#include "LCD_Interface.h"
#include "LCD_Interface.h"

#define RS GPIO_PORTB,0
#define EN GPIO_PORTB,2

void LCD_Send4Bits(u8 data)
{
    GPIO_WritePin(GPIO_PORTD,4,(data>>0)&1);
    GPIO_WritePin(GPIO_PORTD,5,(data>>1)&1);
    GPIO_WritePin(GPIO_PORTD,6,(data>>2)&1);
    GPIO_WritePin(GPIO_PORTD,7,(data>>3)&1);
}

void LCD_Enable()
{
    GPIO_WritePin(GPIO_PORTB,2,1);
    _delay_ms(2);
    GPIO_WritePin(GPIO_PORTB,2,0);
}

void LCD_SendCommand(unsigned char cmd)
{
    GPIO_WritePin(GPIO_PORTB,0,0);

    LCD_Send4Bits(cmd>>4);
    LCD_Enable();

    LCD_Send4Bits(cmd);
    LCD_Enable();
}

void LCD_SendData(unsigned char data)
{
    GPIO_WritePin(GPIO_PORTB,0,1);

    LCD_Send4Bits(data>>4);
    LCD_Enable();

    LCD_Send4Bits(data);
    LCD_Enable();
}

void LCD_Init()
{
    _delay_ms(20);
    LCD_SendCommand(0x28);
    LCD_SendCommand(0x0C);
    LCD_SendCommand(0x01);
}

void LCD_SendString(char* str)
{
    while(*str)
        LCD_SendData(*str++);
}

void LCD_SetCursor(unsigned char row, unsigned char col)
{
    if(row==0)
        LCD_SendCommand(0x80 + col);
    else
        LCD_SendCommand(0xC0 + col);
}