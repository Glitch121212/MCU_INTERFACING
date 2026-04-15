#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

void LCD_Init(void);
void LCD_SendCommand(unsigned char cmd);
void LCD_SendData(unsigned char data);
void LCD_SendString(char* str);
void LCD_SetCursor(unsigned char row, unsigned char col);

#endif