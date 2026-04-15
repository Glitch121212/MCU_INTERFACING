#include "SevenSeg_Interface.h"
#include "GPIO_interface.h"

u8 numbers[10] = {
    0x3F,0x06,0x5B,0x4F,0x66,
    0x6D,0x7D,0x07,0x7F,0x6F
};

void SevenSeg_Display(u8 port, u8 num, u8 type)
{
    u8 val = numbers[num];

    if(type == COMMON_ANODE)
        val = ~val;

    GPIO_WritePort(port, val);
}