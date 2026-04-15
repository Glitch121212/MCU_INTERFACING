#include "GPIO_Interface.h"
#include <util/delay.h>

char keys[4][4] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

char KPD_GetPressedKey(void)
{
    for(u8 r=0; r<4; r++)
    {
        GPIO_WritePin(GPIO_PORTC,r,0);

        for(u8 c=0; c<4; c++)
        {
            if(GPIO_ReadPin(GPIO_PORTC,c+4)==0)
            {
                _delay_ms(20);
                return keys[r][c];
            }
        }

        GPIO_WritePin(GPIO_PORTC,r,1);
    }
    return 0;
}