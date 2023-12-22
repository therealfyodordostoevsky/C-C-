#include <windows.h>
#include <stdio.h>

int main()
{
    SYSTEM_POWER_STATUS powerStatus;

    while (1) {
        GetSystemPowerStatus(&powerStatus);
        if (powerStatus.BatteryLifePercent == 100) {
            MessageBox(NULL, "Battery level is 100%!", "Battery Alert", MB_OK | MB_ICONWARNING);
        }
        Sleep(30000); // Check every 30 seconds
    }

    return 0;
}
