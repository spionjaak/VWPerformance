#include "Display.h"
#include "Startup.h"
#include "OBD.h"
#include "Screens.h"
#include "VehicleData.h"
#include "Config.h"

void setup()
{
    Serial.begin(115200);

    Display_Init();

    Startup_Boot();

    Startup_Connecting();
    if(!RPM_TEST_MODE){
        if(OBD_Init()){
            Startup_Connected();

            Screens_ShowPerformance();
            
        }
        else
        {
            Startup_Error();

            while(true)
            {
                delay(1000);
            }
        }
    }
}

void loop()
{
    if(RPM_TEST_MODE)
    {
        if(RPM_TEST_MODE)
    {
    static unsigned long stateStart = 0;
    static uint8_t state = 0;

    unsigned long now = millis();

    switch(state)
    {
        // =========================
        // LER
        // =========================

        case 0:
            vehicle.rpm = 850;
            vehicle.rpmValid = true;

            if(now - stateStart > 2000)
            {
                state = 1;
                stateStart = now;
            }
            break;

        // =========================
        // NAGLI GAS
        // =========================

        case 1:
            vehicle.rpm = 6000;
            vehicle.rpmValid = true;

            if(now - stateStart > 2500)
            {
                state = 2;
                stateStart = now;
            }
            break;

        // =========================
        // PUSTI GAS
        // =========================

        case 2:
            vehicle.rpm = 800;
            vehicle.rpmValid = true;

            if(now - stateStart > 2500)
            {
                state = 0;
                stateStart = now;
            }
            break;
    }
}
else
{
    OBD_Update();
}
    }
    else
    {
        OBD_Update();
    }

    Screens_Update();
}