#include "global.h"
#include "ov.h"


#define SECONDS_IN_DAY 86400
#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_MINUTE 60

#define TICKS_PER_SEC 0xFFB3D58
#define TICKS_PER_MIN 0x3BEE260A0UL
#define TICKS_IN_5_MIN 0x12BA6BE320UL

#define ADJ(posX, isBottom) (isBottom ? posX - 80 : posX)

u64     osGetTime(void);
Result  PTMU_GetBatteryLevel(u8 *out);
Result  MCU_GetBatteryLevel(u8* out);

#define LIMEGREEN   50,205,50
#define ORANGE      255,140,0
#define RED         255,0,0
#define BLANK       255,255,255

void    GetTimeString(char *output)
{
    u64 timeInSeconds = osGetTime() / 1000;
    u64 dayTime = timeInSeconds % SECONDS_IN_DAY;
    u8 hour = dayTime / SECONDS_IN_HOUR;
    u8 min = (dayTime % SECONDS_IN_HOUR) / SECONDS_IN_MINUTE;
    u8 seconds = dayTime % SECONDS_IN_MINUTE;

    xsprintf(output, "%02d:%02d", hour, min);
}

int     DrawClockAndBattery(int isBottom, u32 percent) 
{
    static u32      batval = 0;
    static u8      batPercent = 0;
    static u64      tick = 0;

    if (svc_getSystemTick() >= tick)
    {
        u8 batteryLevel = 0;
        PTMU_GetBatteryLevel(&batteryLevel);
        MCU_GetBatteryLevel(&batPercent);
        tick = svc_getSystemTick() + TICKS_IN_5_MIN;

        if (batteryLevel == 1) 
        {
            batval = 2;
        } 
        else if (batteryLevel == 2) 
        {
            batval = 5;
        } 
        else if (batteryLevel == 3) 
        {
            batval = 8;
        } 
        else if (batteryLevel == 4) 
        {
            batval = 11;
        } 
        else if (batteryLevel == 5) 
        {
            batval = 16;
        }
    }

    char buf[30] = {0};    

    //DrawBackground
    OvDrawTranspartBlackRect(ADJ(338, isBottom), 9, 57, 12, 1);

    // Draw battery
    OvDrawRect(ADJ(374, isBottom), 11, 18, 1, BLANK);
    OvDrawRect(ADJ(374, isBottom), 18, 18, 1, BLANK);
    OvDrawRect(ADJ(374, isBottom), 11, 1, 8, BLANK);
    OvDrawRect(ADJ(391, isBottom), 11, 1, 8, BLANK);

    if (batval >= 4)
        OvDrawRect(ADJ(375, isBottom), 12, batval, 6, LIMEGREEN);
    else if (batval >= 2 && batval <= 3)
        OvDrawRect(ADJ(375, isBottom), 12, batval, 6, ORANGE);
    else 
        OvDrawRect(ADJ(375, isBottom), 12, batval, 6, RED);

    OvDrawRect(ADJ(392, isBottom), 13, 1, 4, BLANK);

    if (percent)
    {
        xsprintf(buf, "%d%%", batPercent);
        int posX = ADJ(381, isBottom);
        int len = strlen(buf) - 1;
        posX -= (len) * 2;
        OvDrawStringTiny(buf, posX, 12, BLANK);        
    }



    // Draw clock
    GetTimeString(buf);
    OvDrawString(buf, ADJ(341, isBottom), 11, BLANK);

    return (1);
}

int     DrawClockOnly(int isBottom) 
{

    char buf[30] = {0};

    GetTimeString(buf);

    //DrawBackground
    OvDrawTranspartBlackRect(ADJ(352, isBottom), 9, 38, 12, 1);
    // Draw clock
    OvDrawString(buf, ADJ(356, isBottom), 11, 255, 255, 255);
    return (1);
}
