#include <windows.h>
#include <iostream>

int main() {
    SYSTEM_POWER_STATUS powerStatus;

    while (true) {
        GetSystemPowerStatus(&powerStatus);
        if (powerStatus.BatteryLifePercent == 100) {
            MessageBox(NULL, "Battery level is 100%!", "Battery Alert", MB_ICONWARNING | MB_OK);
        }
        Sleep(30000); // Check every 30 seconds
    }

    return 0;
}
