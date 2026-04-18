#ifndef LCD_H
#define LCD_H

#include "STD_TYPES.h"
#include "GPIO_interface.h"

/* Config */
#define LCD_DATA_PORT   GPIO_PORTB
#define LCD_CTRL_PORT   GPIO_PORTC

#define LCD_RS_PIN      GPIO_PIN0
#define LCD_RW_PIN      GPIO_PIN1
#define LCD_EN_PIN      GPIO_PIN2

/* Commands */
#define LCD_CLEAR        0x01
#define LCD_HOME         0x02
#define LCD_ENTRY_MODE   0x06
#define LCD_ON           0x0C
#define LCD_8BIT_MODE    0x38

/* APIs */
void LCD_Init(void);
void LCD_SendCommand(u8 cmd);
void LCD_SendChar(u8 data);
void LCD_SendString(const char* str);
void LCD_SetCursor(u8 row, u8 col);
void LCD_Clear(void);

#endif