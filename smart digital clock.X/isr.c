#include<xc.h>
#include <stdint.h>
#include "rtc.h"
extern volatile uint8_t mode_flag;

void __interrupt() isr(void)
{
    static uint16_t count = 0;
    if(TMR0IF == 1)
    {
        TMR0 = TMR0 +8;
        if(count++ >= 20000)
        {
            count = 0;
            
            //RTC continuous in run mode and alarm mode...but stops in RTC edit mode
            if(mode_flag != 1)  // rtc should stop counting in edit mode
            {
                update_time();
            }
        }
        TMR0IF = 0;
    }
}
