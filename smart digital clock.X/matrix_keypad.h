

/* 
 * File:   matrix_keypad.h
 * Author: sksha
 *
 * Created on 4 August, 2026, 5:31 PM
 */

#ifndef MATRIX_KEYPAD_H
#define	MATRIX_KEYPAD_H

#define R0      RB5
#define R1      RB6
#define R2      RB7

#define C0      RB1
#define C1      RB2
#define C2      RB3
#define C3      RB4

#define SW1     1
#define SW2     2
#define SW3     3
#define SW4     4
#define SW5     5
#define SW6     6
#define SW7     7
#define SW8     8
#define SW9     9
#define SW10    10
#define SW11    11
#define SW12    12
#define ALL_RELEASED  0XFF

#define EDGE    0
#define LEVEL   1


void init_matrix_keypad(void);
unsigned char read_matrix_keypad(unsigned char trigger);



#endif	/* MATRIX_KEYPAD_H */




