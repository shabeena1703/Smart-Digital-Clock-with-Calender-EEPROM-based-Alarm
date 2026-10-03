#include<xc.h>
#include "matrix_keypad.h"

unsigned char scan_key(void)
{
    R0 = 0;
    R1 = R2 = 1;
    
    if(C0 == 0)
    {
        return SW1;
    }
    else if(C1 == 0)
    {
        return SW4;
    }
    else if(C2 == 0)
    {
        return SW7;
    }
    else if(C3 == 0)
    {
        return SW10;
    }
    
    R1 = 0;
    R0 = R2 = 1;
    
    if(C0 == 0)
    {
        return SW2;
    }
    else if(C1 == 0)
    {
        return SW5;
    }
    else if(C2 == 0)
    {
        return SW8;
    }
    else if(C3 == 0)
    {
        return SW11;
    }
    
    R2 = 0;
    R0 = R1 = 1;
    
    if(C0 == 0)
    {
        return SW3;
    }
    else if(C1 == 0)
    {
        return SW6;
    }
    else if(C2 == 0)
    {
        return SW9;
    }
    else if(C3 == 0)
    {
        return SW12;
    }
    
    return ALL_RELEASED;
            
}

void init_matrix_keypad(void)
{
    TRISB = (TRISB & 0X1F) | 0X1E;
    RBPU = 0;
}


unsigned char read_matrix_keypad(unsigned char trigger)
{
    if(trigger == LEVEL)
    {
        return scan_key();
    }
    
    else if(trigger == EDGE)
    {
        static int once_pressed = 0;
        if((scan_key() != ALL_RELEASED) && (once_pressed == 0))
        {
            once_pressed = 1;
            return scan_key();
        }
        
        else if(scan_key() == ALL_RELEASED)
        {
            once_pressed = 0;
        }
    }
    return ALL_RELEASED;
}
