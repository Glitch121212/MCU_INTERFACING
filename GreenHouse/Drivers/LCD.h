#ifndef LCD_H
#define LCD_H

#include "STD_TYPES.h"

void LCD_Init(void);
void LCD_SendCommand(u8 cmd);
void LCD_Clear(void);
void LCD_SendChar(u8 ch);
void LCD_SendString(const char *str);
void LCD_SetCursor(u8 col,u8 row);

#endif
