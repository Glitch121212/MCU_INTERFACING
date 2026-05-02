#ifndef LCD_H
#define LCD_H

#include "STD_TYPES.h"
#include "GPIO.h"

/* ================= CONFIG ================= */

/* Data (4-bit mode ? upper nibble) */
#define LCD_DATA_PORT   GPIO_enuPORTD

#define LCD_D4_PIN      GPIO_enuPIN2
#define LCD_D5_PIN      GPIO_enuPIN3
#define LCD_D6_PIN      GPIO_enuPIN4
#define LCD_D7_PIN      GPIO_enuPIN5

/* Control */
#define LCD_CTRL_PORT   GPIO_enuPORTD

#define LCD_RS_PIN      GPIO_enuPIN0
#define LCD_EN_PIN      GPIO_enuPIN1

/* Commands */
#define LCD_CLEAR        0x01
#define LCD_HOME         0x02
#define LCD_ENTRY_MODE   0x06
#define LCD_ON           0x0C
#define LCD_4BIT_MODE    0x28   /* 4-bit, 2 lines */
#define LCD_INIT_4BIT    0x02   /* special init */

/* APIs */
void LCD_Init(void);
void LCD_SendCommand(u8 cmd);
void LCD_SendChar(u8 data);
void LCD_SendString(const char* str);
void LCD_SetCursor(u8 row, u8 col);
void LCD_Clear(void);
void LCD_PrintNumber(u16 num);

#endif