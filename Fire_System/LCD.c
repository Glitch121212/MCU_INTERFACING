#define F_CPU 10000000UL
#include <util/delay.h>
#include "LCD.h"
#include "TIMER0_interface.h"

static void LCD_EnablePulse(void);
static void LCD_Send4Bits(u8 data);

/* ================= INIT ================= */

void LCD_Init(void)
{
    /* Data pins */
    GPIO_VidSetPinDirection(LCD_DATA_PORT, LCD_D4_PIN, GPIO_enuOUTPUT);
    GPIO_VidSetPinDirection(LCD_DATA_PORT, LCD_D5_PIN, GPIO_enuOUTPUT);
    GPIO_VidSetPinDirection(LCD_DATA_PORT, LCD_D6_PIN, GPIO_enuOUTPUT);
    GPIO_VidSetPinDirection(LCD_DATA_PORT, LCD_D7_PIN, GPIO_enuOUTPUT);

    /* Control pins */
    GPIO_VidSetPinDirection(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_enuOUTPUT);
    GPIO_VidSetPinDirection(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_enuOUTPUT);

    _delay_ms(40);

    /* Initialization sequence */
    LCD_Send4Bits(0x02);  /* Switch to 4-bit */

    LCD_SendCommand(LCD_4BIT_MODE);
    LCD_SendCommand(LCD_ON);
    LCD_SendCommand(LCD_CLEAR);
    LCD_SendCommand(LCD_ENTRY_MODE);
}


/* ================= INTERNAL ================= */

static void LCD_Send4Bits(u8 data)
{
    GPIO_VidSetPinValue(LCD_DATA_PORT, LCD_D4_PIN, (data >> 0) & 1);
    GPIO_VidSetPinValue(LCD_DATA_PORT, LCD_D5_PIN, (data >> 1) & 1);
    GPIO_VidSetPinValue(LCD_DATA_PORT, LCD_D6_PIN, (data >> 2) & 1);
    GPIO_VidSetPinValue(LCD_DATA_PORT, LCD_D7_PIN, (data >> 3) & 1);

    LCD_EnablePulse();
}

static void LCD_EnablePulse(void)
{
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_enuHIGH);
    _delay_us(20);
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_enuLOW);
    _delay_ms(10);
}

void LCD_SendCommand(u8 cmd){
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_enuLOW);
    LCD_Send4Bits(cmd >> 4);
    _delay_ms(10);
    LCD_Send4Bits(cmd);
    _delay_ms(10);
    
}
void LCD_SendChar(u8 data){
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_enuHIGH);
    LCD_Send4Bits(data >> 4);
    _delay_ms(10);
    LCD_Send4Bits(data);
    _delay_ms(10);   
}
void LCD_SendString(const char* str){
    while(*str != '\0'){
        LCD_SendChar((u8)*str);
        str++;
    }
    
}
void LCD_SetCursor(u8 row, u8 col){
    if (row == 0){
        LCD_SendCommand(0x80 + col);
    }
    else{
        LCD_SendCommand(0xC0 + col);
    }
    
    
}
void LCD_Clear(void){
    LCD_SendCommand(LCD_CLEAR);
    _delay_us(10);
}

void LCD_PrintNumber(u16 num)
{
    u8 digits[5];  
    u8 i = 0;

    if(num == 0)
    {
        LCD_SendChar('0');
        return;
    }

    while(num > 0)
    {
        digits[i] = num % 10;
        num /= 10;
        i++;
    }

    while(i > 0)
    {
        i--;
        LCD_SendChar((u8) (((u8) digits[i]) + ((u8) ('0'))));
    }
}