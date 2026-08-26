#include "Screens.h"

#include "Display.h"
#include "VehicleData.h"

static bool firstDraw = true;

static int lastTemp = -1000;
static float lastBattery = -1.0f;

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

    // =========================
    // RPM - 30 FPS
    // =========================

    static unsigned long lastRPMUpdate = 0;

    if(millis() - lastRPMUpdate >= 33)
    {
        lastRPMUpdate = millis();

        Display_UpdateRPM();
    }

    // =========================
    // TEMPERATURE
    // =========================

    if(vehicle.tempValid &&
       vehicle.coolantTemp != lastTemp)
    {
        lastTemp = vehicle.coolantTemp;

        Display_UpdateTemperature();
    }

    // =========================
    // BATTERY
    // =========================

    if(vehicle.batteryValid &&
       abs(vehicle.batteryVoltage - lastBattery) >= 0.1f)
    {
        lastBattery = vehicle.batteryVoltage;

        Display_UpdateBattery();
    }
}