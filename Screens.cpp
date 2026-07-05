#include "Screens.h"

#include "Display.h"
#include "VehicleData.h"

static bool firstDraw = true;

void Screens_ShowPerformance()
{
    Display_DrawPerformanceScreen();

    firstDraw = false;
}

void Screens_Update()
{
    if(firstDraw)
    {
        Screens_ShowPerformance();
        return;
    }

    if(vehicle.rpmValid)
    {
        Display_UpdateRPM();
    }

    if(vehicle.tempValid)
    {
        Display_UpdateTemperature();
    }

    if(vehicle.batteryValid)
    {
        Display_UpdateBattery();
    }
}