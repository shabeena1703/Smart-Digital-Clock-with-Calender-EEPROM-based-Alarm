#include<xc.h>
#include "eeprom.h"

void write_eeprom (unsigned char address , unsigned char data)
{
    EEADR = address;
    EEDATA = data;
    EEPGD = 0; //(EEPROM)
    CFGS = 0; //(access EEPROM)
    WREN = 1; //(enable write operation)
    GIE = 0;
    EECON2 = 0X55;
    EECON2 = 0XAA;
    WR = 1;
    GIE = 1;
    EECON1bits.WREN = 0;  //(disable write)
    
    while(!EEIF);
    EEIF = 0;
    
}




uint8_t read_eeprom(unsigned char address)
{
    EEADR = address;
    EEPGD = 0;  //(EEPROM)
    CFGS = 0;   //(ACCESS EEPROM)
    RD = 1;    //(enable read operation)
    unsigned char w = EEDATA;
    return w;
    
    
}

