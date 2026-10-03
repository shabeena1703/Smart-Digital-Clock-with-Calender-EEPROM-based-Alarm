#include<xc.h>
#include <stdint.h>
#include "rtc.h"

uint8_t hr = 0;
uint8_t min = 0;
uint8_t sec = 0;

uint8_t date = 1;
uint8_t month = 1;
uint32_t year = 2026;

uint8_t get_days(void)
{
    uint8_t days;
    if(month == 2)
    {
        if((year % 400 == 0) ||((year % 4 == 0) &&(year % 100 != 0)))
        {
            days = 29;
        }
        else
        {
            days = 28;
        }
    }
    else if((month == 4) || (month == 6) || (month == 9) || (month == 11))
    {
        days = 30;
    }
    else
    {
        days = 31;
    }
    return days;
}


void update_time()
{
    sec++;
    if(sec == 60)
    {
        sec = 0;
        min++;
    }
    if(min == 60)
    {
        min = 0;
        hr++;
    }
    if(hr == 24)
    {
        hr = 0;
        update_date();
    }
}


void update_date()
{
    uint8_t days;
    days = get_days();
    date++;
    
    if(date > days)
    {
        date = 1;
        month++;
    }
    if(month > 12)
    {
        month = 1;
        year++;
    }
}
