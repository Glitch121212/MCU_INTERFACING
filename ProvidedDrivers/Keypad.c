#include "Keypad.h"

static const u8 KPD_Keys[KPD_ROWNUM][KPD_ColNUM] = Keypad_Arr;

static const u8 KPD_RowsPins[KPD_ROWNUM] = {KPD_Row1, KPD_Row2, KPD_Row3, KPD_Row4};
static const u8 KPD_ColsPins[KPD_ColNUM] = {KPD_col1, KPD_col2, KPD_col3, KPD_col4};

void Keypad_init(u8 copy_port) {
    u8 i;
    for (i = 0; i < KPD_ROWNUM; i++) {
        GPIO_VidSetPinDirection(copy_port, KPD_RowsPins[i], GPIO_enuOUTPUT);
        GPIO_VidSetPinValue(copy_port, KPD_RowsPins[i], GPIO_enuHIGH);
    }
    for (i = 0; i < KPD_ColNUM; i++) {
        GPIO_VidSetPinDirection(copy_port, KPD_ColsPins[i], GPIO_enuINPUT);
        GPIO_VidSetPinValue(copy_port, KPD_ColsPins[i], GPIO_enuHIGH);
    }
}

u8 Keypad_CheckNum(u8 copy_u8port) {
    u8 row_idx, col_idx, pin_state;
    u8 pressed_key = 0xFF;
    
    
    do
    {
    for (row_idx = 0; row_idx < KPD_ROWNUM; row_idx++) {
        GPIO_VidSetPinValue(copy_u8port, KPD_RowsPins[row_idx], GPIO_enuLOW);

        for (col_idx = 0; col_idx < KPD_ColNUM; col_idx++) {
            pin_state = GPIO_U8GetPinValue(copy_u8port, KPD_ColsPins[col_idx]);

            if (pin_state == GPIO_enuLOW) {
                while (pin_state == GPIO_enuLOW) {
                    pin_state = GPIO_U8GetPinValue(copy_u8port, KPD_ColsPins[col_idx]);
                }
                pressed_key = KPD_Keys[row_idx][col_idx];
                GPIO_VidSetPinValue(copy_u8port, KPD_RowsPins[row_idx], GPIO_enuHIGH);
                return pressed_key;
            }
        }
        GPIO_VidSetPinValue(copy_u8port, KPD_RowsPins[row_idx], GPIO_enuHIGH);
    }
    }   while(pressed_key == 0xFF);
    return pressed_key;
}