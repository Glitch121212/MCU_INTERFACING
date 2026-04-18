#define F_CPU 1000000UL
#include <util/delay.h>

#include "LCD.h"

static void LCD_EnablePulse(void);

void LCD_Init(void)
{
    GPIO_VidSetPortDirection(LCD_DATA_PORT, GPIO_PORT_OUTPUT);

    GPIO_VidSetPinDirection(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_OUTPUT);
    GPIO_VidSetPinDirection(LCD_CTRL_PORT, LCD_RW_PIN, GPIO_OUTPUT);
    GPIO_VidSetPinDirection(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_OUTPUT);

    _delay_ms(40);

    LCD_SendCommand(LCD_8BIT_MODE);
    LCD_SendCommand(LCD_ON);
    LCD_SendCommand(LCD_CLEAR);
    LCD_SendCommand(LCD_ENTRY_MODE);
}

void LCD_SendCommand(u8 cmd)
{
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_LOW);
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, GPIO_LOW);

    GPIO_VidSetPortValue(LCD_DATA_PORT, cmd);
    LCD_EnablePulse();
}


void LCD_SendChar(u8 data)
{
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_HIGH);
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, GPIO_LOW);

    GPIO_VidSetPortValue(LCD_DATA_PORT, data);
    LCD_EnablePulse();
}

void LCD_SendString(const char* str)
{
    while(*str)
    {
        LCD_SendChar(*str++);
    }
}

void LCD_SetCursor(u8 row, u8 col)
{
    if(row == 0)
        LCD_SendCommand(0x80 + col);
    else
        LCD_SendCommand(0xC0 + col);
}

void LCD_Clear(void)
{
    LCD_SendCommand(LCD_CLEAR);
    _delay_ms(2);
}

static void LCD_EnablePulse(void)
{
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_HIGH);
    _delay_us(2);
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_LOW);
    _delay_ms(2);
}