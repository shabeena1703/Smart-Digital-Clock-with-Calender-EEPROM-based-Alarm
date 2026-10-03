/*
 * File:   main.c
 * Author: sksha
 *
 * Created on 15 August, 2026, 3:28 PM
 */


#include <xc.h>
#include <stdint.h>
#include "timer.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include "rtc.h"
#include "eeprom.h"
#include "alarm.h"

volatile uint8_t mode_flag = 0;    //0 (run mode), 1(edit mode)  2(alarm)
uint8_t field_flag = 0;   // 0 (hr),1(min),2(sec),3(date),4(month),5(year)

volatile uint16_t delay = 0; //int

void init_config(void)
{
    init_timer0();
    init_matrix_keypad();
    init_clcd();
    init_alarm();
    //save_alarm();
    load_alarm();
}

void main(void)
{
    unsigned char key;
    init_config();
    
    while(1)
    {
        delay++;
        if(delay >= 200)
        {
            delay = 0;
        }
        key = read_matrix_keypad(EDGE);
        
        //check alarm only if it is in run mode
        if(mode_flag == 0)
        {
            check_alarm();
            if(alarm_flag == 1)
            {
                //clear display
                clcd_print("ALARM!          ", LINE1(0));
                clcd_print("                ",LINE2(0));
            }
        }
        
        if(key == SW4)
        {
            //if(mode_flag == 2) 
            //{
             //   save_alarm();
            //}
            mode_flag++;
            
            if(mode_flag > 2)
            {
                mode_flag = 0;
            }
            field_flag = 0;
            delay = 0;
        }
        
        //save alarm if SW5 is pressed(in alarm mode only)
        if(key == SW5)
        {
            if(mode_flag == 2)
            {
                save_alarm();

                // After saving, go back to RUN mode //
                mode_flag = 0;
                field_flag = 0;
                delay = 0;
            }
        }
        
        //TO TURN OFF THE BUZZER
        if(key == SW6)
        {
            if(alarm_flag == 1) 
            {
                RE0 = 0;
                alarm_flag = 0;
            }
        }
        
        
        
        // =================== RTC EDIT MODE====================== //                

        if(mode_flag == 1)
        {
            //SW3 (select next field)
            if(key == SW3)
            {
                field_flag++;
                if(field_flag > 5)
                {
                    field_flag = 0;
                }
                delay = 0;
            }
            
            //sw1 (increment)
            else if(key == SW1)
            {
                if(field_flag == 0)
                {
                    hr++;
                    if(hr > 23)
                    {
                        hr = 0;
                    }
                }
                else if(field_flag == 1)
                {
                    min++;
                    if(min > 59)
                    {
                        min = 0;
                    }
                }
                else if(field_flag == 2)
                {
                    sec++;
                    if(sec > 59)
                    {
                        sec = 0;
                    }
                }
                else if(field_flag == 3)
                {
                    date++;
                    
                    if(date > get_days())
                    {
                        date = 1;
                    }
                }
                else if(field_flag == 4)
                {
                    month++;
                    if(month > 12)
                    {
                        month = 1;
                    }
                    //to check if next month has valid no.of days or not
                    if(date > get_days())
                    {
                        date = get_days();
                    }
                }
                
                else if(field_flag == 5)
                {
                    year++;
                    if(date > get_days())
                    {
                        date = get_days();
                    }
                }
                
            }
            
            //decrement
            else if(key == SW2)
            {
                if(field_flag == 0)
                {
                    if(hr == 0)
                    {
                        hr = 23;
                    }
                    else
                    {
                        hr--;
                    }
                }
                else if(field_flag == 1)
                {
                    if(min == 0 )
                    {
                        min = 59;
                    }
                    else
                    {
                        min--;
                    }
                }
                else if(field_flag == 2)
                {
                    if(sec == 0)
                    {
                        sec = 59;
                    }
                    else
                    {
                        sec--;
                    }
                }
                else if(field_flag == 3)
                {
                    if(date == 1)
                    {
                        date = get_days();
                    }
                    else
                    {
                        date--;
                    }
                }
                else if(field_flag == 4)
                {
                    if(month == 1)
                    {
                        month = 12;
                    }
                    else
                    {
                        month--;
                    }
                    
                    //to check if the decreased month also contains same number of days....if not,then calculate again
                    if(date > get_days())
                    {
                        date = get_days();
                    }
                }
                else if(field_flag == 5)
                {
                    if(year > 2026)  //if year is 2026,then 2026 > 2026 is false..so it dont decrement
                    {
                        year--;
                    }
                    if(date > get_days())
                    {
                        date = get_days();
                    }
                }
                
            }
            
        }
        
        
        
        
        // =================== ALARM EDIT MODE====================== // 
        if(mode_flag == 2)
        {
            //SW3 (select next field)
            if(key == SW3)
            {
                field_flag++;
                if(field_flag > 5)
                {
                    field_flag = 0;
                }
                delay = 0;
            }
            
            //sw1 (increment)
            else if(key == SW1)
            {
                if(field_flag == 0)
                {
                    alarm_hr++;
                    if(alarm_hr > 23)
                    {
                        alarm_hr = 0;
                    }
                }
                else if(field_flag == 1)
                {
                    alarm_min++;
                    if(alarm_min > 59)
                    {
                        alarm_min = 0;
                    }
                }
                else if(field_flag == 2)
                {
                    alarm_sec++;
                    if(alarm_sec > 59)
                    {
                        alarm_sec = 0;
                    }
                }
                else if(field_flag == 3)
                {
                    alarm_date++;
                    
                    if(alarm_date > get_alarm_days())
                    {
                        alarm_date = 1;
                    }
                }
                else if(field_flag == 4)
                {
                    alarm_month++;
                    if(alarm_month > 12)
                    {
                        alarm_month = 1;
                    }
                    //to check whether the no of days are valid or not for month
                    if(alarm_date > get_alarm_days())
                    {
                        alarm_date = get_alarm_days();
                    }
                }
                else if(field_flag == 5)
                {
                    alarm_year++;
                    
                    if(alarm_date > get_alarm_days())
                    {
                        alarm_date = get_alarm_days();
                    }
                }
                
            }
            
            //decrement
            else if(key == SW2)
            {
                if(field_flag == 0)
                {
                    if(alarm_hr == 0)
                    {
                        alarm_hr = 23;
                    }
                    else
                    {
                        alarm_hr--;
                    }
                }
                else if(field_flag == 1)
                {
                    if(alarm_min == 0 )
                    {
                        alarm_min = 59;
                    }
                    else
                    {
                        alarm_min--;
                    }
                }
                else if(field_flag == 2)
                {
                    if(alarm_sec == 0)
                    {
                        alarm_sec = 59;
                    }
                    else
                    {
                        alarm_sec--;
                    }
                }
                else if(field_flag == 3)
                {
                    if(alarm_date == 1)
                    {
                        alarm_date = get_alarm_days();
                    }
                    else
                    {
                        alarm_date--;
                    }
                }
                else if(field_flag == 4)
                {
                    if(alarm_month == 1)
                    {
                        alarm_month = 12;
                    }
                    else
                    {
                        alarm_month--;
                    }
                    
                    //to check if the decreased month also contains same number of days....if not,then calculate again
                    if(alarm_date > get_alarm_days())
                    {
                        alarm_date = get_alarm_days();
                    }
                }
                else if(field_flag == 5)
                {
                    if(alarm_year > 2026)  //if year is 2026,then 2026 > 2026 is false..so it dont decrement
                    {
                        alarm_year--;
                    }
                    if(alarm_date > get_alarm_days())
                    {
                        alarm_date = get_alarm_days();
                    }
                }
            }
            
        }
        
        
        
        //RUN MODE + RTC EDIT MODE
        //Display normal RTC only when mode is 0 or 1 and when the alarm is not active.
        if((mode_flag == 0 || mode_flag == 1) && alarm_flag == 0)
        { 
            //blinking hours
            if(mode_flag == 1 && field_flag == 0)
            {
                if(delay < 100)
                {
                    clcd_putch((hr / 10) + '0',LINE1(0));
                    clcd_putch((hr % 10) + '0',LINE1(1));
                }
                else if(delay < 200)
                {
                    clcd_putch(' ',LINE1(0));
                    clcd_putch(' ',LINE1(1));
                }
            }
            else
            {
                clcd_putch((hr / 10) + '0',LINE1(0));
                clcd_putch((hr % 10) + '0',LINE1(1));
            }

            clcd_putch(':',LINE1(2));

            //blinking minute field
            if(mode_flag == 1 && field_flag == 1)
            {
                if(delay < 100)
                {
                    clcd_putch((min / 10) + '0',LINE1(3));
                    clcd_putch((min % 10) + '0',LINE1(4));
                }
                else if(delay < 200)
                {
                    clcd_putch(' ',LINE1(3));
                    clcd_putch(' ',LINE1(4));
                }
            }
            else
            {
                clcd_putch((min / 10) + '0',LINE1(3));    //display normally dont blink
                clcd_putch((min % 10) + '0',LINE1(4));   
            }

            clcd_putch(':',LINE1(5));

           //blinking seconds field
            if(mode_flag == 1 && field_flag == 2)
            {
                if(delay < 100)
                {
                    clcd_putch((sec / 10) + '0',LINE1(6));
                    clcd_putch((sec % 10) + '0',LINE1(7));
                }
                else if(delay < 200)
                {
                    clcd_putch(' ',LINE1(6));
                    clcd_putch(' ',LINE1(7));
                }
            }
            else
            {
                clcd_putch((sec / 10) + '0',LINE1(6));        //display normally dont blink
                clcd_putch((sec % 10) + '0',LINE1(7));
            }
            if(mode_flag == 1) 
            { 
                clcd_putch('E', LINE1(13)); //to recognize RTC Edit mode
            } 
            else 
            { 
                clcd_putch(' ', LINE1(13)); 
            } 

            //blinking date
            if(mode_flag == 1 && field_flag == 3)
            {
                if(delay < 100)
                {
                    clcd_putch((date / 10) + '0',LINE2(0));
                    clcd_putch((date % 10) + '0',LINE2(1));
                }
                else if(delay < 200)
                {
                    clcd_putch(' ',LINE2(0));
                    clcd_putch(' ',LINE2(1));
                }
            }
            else
            {
                clcd_putch((date / 10) + '0',LINE2(0));      //display normally ..dont blink
                clcd_putch((date % 10) + '0',LINE2(1));
            }

            clcd_putch('-',LINE2(2));

            //blinking month field
            if(mode_flag == 1 && field_flag == 4)
            {
                if(delay < 100)
                {
                    clcd_putch((month / 10) + '0',LINE2(3));
                    clcd_putch((month % 10) + '0',LINE2(4));
                }
                else if(delay < 200)
                {
                    clcd_putch(' ',LINE2(3));
                    clcd_putch(' ',LINE2(4));
                }
            }
            else
            {
                clcd_putch((month / 10) + '0',LINE2(3));     //display normally ..dont blink
                clcd_putch((month % 10) + '0',LINE2(4));
            }

            clcd_putch('-',LINE2(5));


            //blinking year field 
            if(mode_flag == 1 && field_flag == 5)
            {
                if(delay < 100)
                {
                    clcd_putch((year / 1000) + '0',LINE2(6));
                    clcd_putch(((year / 100) % 10) + '0',LINE2(7));
                    clcd_putch(((year / 10) % 10) + '0',LINE2(8));
                    clcd_putch((year % 10) + '0',LINE2(9));
                }
                else if(delay < 200)
                {
                    clcd_putch(' ',LINE2(6));
                    clcd_putch(' ',LINE2(7));
                    clcd_putch(' ',LINE2(8));
                    clcd_putch(' ',LINE2(9));
                }
            }
            else
            {
                clcd_putch((year / 1000) + '0',LINE2(6));
                clcd_putch(((year / 100) % 10) + '0',LINE2(7));  //display normally ..dont blink
                clcd_putch(((year / 10) % 10) + '0',LINE2(8));
                clcd_putch((year % 10) + '0',LINE2(9));
            }
        }
        
        
        
        //ALARM clock display
        else if(mode_flag == 2)
        {
            //blinking hours
            if(field_flag == 0)
            {
                if(delay < 100)
                {
                    clcd_putch((alarm_hr / 10) + '0',LINE1(0));
                    clcd_putch((alarm_hr % 10) + '0',LINE1(1));
                }
                else if(delay < 200)
                {
                    clcd_putch(' ',LINE1(0));
                    clcd_putch(' ',LINE1(1));
                }
            }
            else
            {
                clcd_putch((alarm_hr / 10) + '0',LINE1(0));
                clcd_putch((alarm_hr % 10) + '0',LINE1(1));
            }

            clcd_putch(':',LINE1(2));

            //blinking minute field
            if(field_flag == 1)
            {
                if(delay < 100)
                {
                    clcd_putch((alarm_min / 10) + '0',LINE1(3));
                    clcd_putch((alarm_min % 10) + '0',LINE1(4));
                }
                else if(delay < 200)
                {
                    clcd_putch(' ',LINE1(3));
                    clcd_putch(' ',LINE1(4));
                }
            }
            else
            {
                clcd_putch((alarm_min / 10) + '0',LINE1(3));    //display normally dont blink
                clcd_putch((alarm_min % 10) + '0',LINE1(4));   
            }

            clcd_putch(':',LINE1(5));

           //blinking seconds field
            if(field_flag == 2)
            {
                if(delay < 100)
                {
                    clcd_putch((alarm_sec / 10) + '0',LINE1(6));
                    clcd_putch((alarm_sec % 10) + '0',LINE1(7));
                }
                else if(delay < 200)
                {
                    clcd_putch(' ',LINE1(6));
                    clcd_putch(' ',LINE1(7));
                }
            }
            else
            {
                clcd_putch((alarm_sec / 10) + '0',LINE1(6));        //display normally dont blink
                clcd_putch((alarm_sec % 10) + '0',LINE1(7));
            }
            clcd_print("A",LINE1(13));                    //to recognize alarm edit mode

            //blinking date
            if(field_flag == 3)
            {
                if(delay < 100)
                {
                    clcd_putch((alarm_date / 10) + '0',LINE2(0));
                    clcd_putch((alarm_date % 10) + '0',LINE2(1));
                }
                else if(delay < 200)
                {
                    clcd_putch(' ',LINE2(0));
                    clcd_putch(' ',LINE2(1));
                }
            }
            else
            {
                clcd_putch((alarm_date / 10) + '0',LINE2(0));      //display normally ..dont blink
                clcd_putch((alarm_date % 10) + '0',LINE2(1));
            }

            clcd_putch('-',LINE2(2));

            //blinking month field
            if(field_flag == 4)
            {
                if(delay < 100)
                {
                    clcd_putch((alarm_month / 10) + '0',LINE2(3));
                    clcd_putch((alarm_month % 10) + '0',LINE2(4));
                }
                else if(delay < 200)
                {
                    clcd_putch(' ',LINE2(3));
                    clcd_putch(' ',LINE2(4));
                }
            }
            else
            {
                clcd_putch((alarm_month / 10) + '0',LINE2(3));     //display normally ..dont blink
                clcd_putch((alarm_month % 10) + '0',LINE2(4));
            }

            clcd_putch('-',LINE2(5));

            //blinking year field 
            if(field_flag == 5)
            {
                if(delay < 100)
                {
                    clcd_putch((alarm_year / 1000) + '0',LINE2(6));
                    clcd_putch(((alarm_year / 100) % 10) + '0',LINE2(7));
                    clcd_putch(((alarm_year / 10) % 10) + '0',LINE2(8));
                    clcd_putch((alarm_year % 10) + '0',LINE2(9));
                }
                else if(delay < 200)
                {
                    clcd_putch(' ',LINE2(6));
                    clcd_putch(' ',LINE2(7));
                    clcd_putch(' ',LINE2(8));
                    clcd_putch(' ',LINE2(9));
                }
            }
            else
            {
                clcd_putch((alarm_year / 1000) + '0',LINE2(6));
                clcd_putch(((alarm_year / 100) % 10) + '0',LINE2(7));  //display normally ..dont blink
                clcd_putch(((alarm_year / 10) % 10) + '0',LINE2(8));
                clcd_putch((alarm_year % 10) + '0',LINE2(9));
            }
        }

    }
}