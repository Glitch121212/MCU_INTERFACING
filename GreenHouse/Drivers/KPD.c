#include "KPD.h"
#include "GPIO.h"
#include <util/delay.h>

void KPD_Init(void)
{
    SetPortDirection(GPIO_PORTD, 0xF0);
    SetPortValue(GPIO_PORTD, GPIO_HIGH);
}

u8 KPD_GetKey(void)
{
    u8 i;
    for(i=0;i<4;i++)
    {
        SetPinValue(GPIO_PORTD,i,GPIO_LOW);
        _delay_ms(5);
        SetPinValue(GPIO_PORTD,i,GPIO_HIGH);
    }
    return 0xFF;
}
