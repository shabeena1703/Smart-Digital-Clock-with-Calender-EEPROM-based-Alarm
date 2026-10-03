#include<xc.h>
#include "timer.h"

void init_timer0(void)
{
     //TO use enable timer0
    TMR0ON = 1;
    
    //we need to preload from 6
    TMR0 = 6;
    T08BIT = 1;
    T0CS = 0;
    PSA = 1;
    
    
    //to use timer0 as interrupt
    GIE = 1;
    PEIE = 1;
    TMR0IE = 1;
    TMR0IF = 0;
}
