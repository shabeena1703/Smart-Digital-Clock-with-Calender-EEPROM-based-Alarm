/* 
 * File:   alarm.h
 * Author: sksha
 *
 * Created on 18 August, 2026, 10:44 PM
 */

#ifndef ALARM_H
#define	ALARM_H

#include <stdint.h>

extern uint8_t alarm_hr;
extern uint8_t alarm_min;
extern uint8_t alarm_sec;

extern uint8_t alarm_date;
extern uint8_t alarm_month;
extern uint32_t alarm_year;

extern uint8_t alarm_flag;

void init_alarm(void);
void save_alarm(void);
void load_alarm(void);
void check_alarm(void);

uint8_t get_alarm_days(void);




#endif	/* ALARM_H */

