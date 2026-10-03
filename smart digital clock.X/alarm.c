#include<xc.h>
#include<stdint.h>

#include "alarm.h"
#include "eeprom.h"
#include "rtc.h"
uint8_t alarm_hr = 00;
uint8_t alarm_min = 00;
uint8_t alarm_sec = 00;

uint8_t alarm_date = 01;
uint8_t alarm_month = 01;
uint32_t alarm_year = 2026;

uint8_t alarm_flag = 0;


void init_alarm(void)
{
    TRISE = TRISE & 0XFE;  //RE0 as output
    RE0 = 0;            //buzzer off
}


//to get correct no of days in month
uint8_t get_alarm_days(void)
{
    uint8_t days;
    if(alarm_month == 2)
    {
        if((alarm_year % 400 == 0) ||((alarm_year % 4 == 0) &&(alarm_year % 100 != 0)))
        {
            days = 29;
        }
        else
        {
            days = 28;
        }
    }
    else if((alarm_month == 4) || (alarm_month == 6) || (alarm_month == 9) || (alarm_month == 11))
    {
        days = 30;
    }
    else
    {
        days = 31;
    }
    return days;
}



//to set the alarm
void save_alarm(void)
{
   write_eeprom(0,alarm_hr);
   write_eeprom(1,alarm_min);
   write_eeprom(2,alarm_sec);
   write_eeprom(3,alarm_date);
   write_eeprom(4,alarm_month);
   
   //year is 32bit. It wont fit in eeprom in single byte...we need to typecast it to 8 bit
   write_eeprom(5,(uint8_t)(alarm_year & 0xFF));
   write_eeprom(6,(uint8_t)((alarm_year >> 8) & 0xFF));
   write_eeprom(7,(uint8_t)((alarm_year >> 16) & 0xFF));
   write_eeprom(8,(uint8_t)((alarm_year >> 24) & 0xFF));
   
   write_eeprom(9, 0xAA);
}


//to read the alarm
void load_alarm(void)
{
    if(read_eeprom(9) == 0xAA)
    {
        alarm_hr = read_eeprom(0);
        alarm_min = read_eeprom(1);
        alarm_sec = read_eeprom(2);
        alarm_date = read_eeprom(3);
        alarm_month = read_eeprom(4);

        alarm_year = read_eeprom(5);
        alarm_year |= ((uint32_t)read_eeprom(6) << 8);
        alarm_year |= ((uint32_t)read_eeprom(7) << 16);
        alarm_year |= ((uint32_t)read_eeprom(8) << 24);

        //to check whether the stored alarm date is valid or not
        if(alarm_date > get_alarm_days())
        {
            alarm_date = get_alarm_days();
        }
    }
    
    else
    {
        // EEPROM has no saved alarm
        alarm_hr = 0;
        alarm_min = 0;
        alarm_sec = 0;

        alarm_date = 1;
        alarm_month = 1;
        alarm_year = 2026;
    }
}


//to check the alarm
void check_alarm(void)
{
    if((hr == alarm_hr) && (min == alarm_min) && (sec == alarm_sec) &&(date == alarm_date) && (month == alarm_month) && (year == alarm_year))
    {
        RE0 = 1;
        
        alarm_flag = 1;
    }
    //else
    //{
        //RE0 = 0;
        //alarm_flag = 0;
    //}
}
