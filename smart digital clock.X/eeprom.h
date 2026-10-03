/* 
 * File:   eeprom.h
 * Author: sksha
 *
 * Created on 16 August, 2026, 3:58 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H
#include <stdint.h>

void write_eeprom(unsigned char address , unsigned char data);
uint8_t read_eeprom(unsigned char address);
#endif	/* EEPROM_H */

