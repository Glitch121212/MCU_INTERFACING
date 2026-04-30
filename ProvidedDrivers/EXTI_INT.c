/* 
 * File:   EXTI_INT.c
 * Author: Muhammed.Hany
 *
 * Created on April 29, 2026, 11:00 AM
 */

#include "EXTI_INT.h"
#include "BIT_MATH.h"
#include <avr/io.h>



void EXT_INT_GLOBALENABLE(void){
   SET_BIT(SREG,7);
}
