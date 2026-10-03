/* 
 * File:   rtc.h
 * Author: sksha
 *
 * Created on 15 August, 2026, 5:23 PM
 */

#ifndef RTC_H
#define	RTC_H
#include <stdint.h>

extern uint8_t hr;
extern uint8_t min;
extern uint8_t sec;

extern uint8_t date;
extern uint8_t month;
extern uint32_t year;

void update_time(void);
void update_date(void);

uint8_t get_days(void);
#endif	/* RTC_H */

