#include "global.h"

static u8 *menuEntries[10] =
{
    "Disable Clock",
    "Display Clock only",
    "Display Clock + Battery",
    "Enable/Disable Battery percentage",
    "Change Clock widget's screen",
    "Disable FPS Counter",
    "Display FPS of both screens",
    "Display FPS of Top Screen",
    "Display FPS of Bottom Screen",
    "Display FPS on Bottom screen"
};

extern u32         g_percentage;
extern u32         g_clockScreen;
extern u32         g_clockMode; // 0 = none, 1 = Clock Only, 2 = Clock + Battery
extern u32         g_fpsScreen;
extern u32         g_fpsCounter; // 0 = disabled, 1 = both screen, 2 = top screen only, 3 = bottom screen only

int     OverlayMenu(void)
{
    static int displayMenu = 0;
    static int selector = 0;

    u8 buf[200];
    int res = 0;
    
    if (getKey() == (BUTTON_L | BUTTON_X | BUTTON_Y))
    {
        waitKeyRelease();
        displayMenu = 1;
    }

    if (!displayMenu)
        return (0);

    res = showMenu("Overlay tools menu", 10, menuEntries, &selector);
    if (res >= 0 && res <= 2)
        g_clockMode = res;
    else if (res == 3)
        g_percentage = !g_percentage;
    else if (res == 4)
        g_clockScreen = !g_clockScreen;
    else if (res >= 5 && res <= 8)
        g_fpsCounter = res - 5;
    else if (res == 9)
        g_fpsScreen = !g_fpsScreen;

    if (res == -1)
    {
        displayMenu = 0;
        selector = 0;
    }
    return (1);
}
