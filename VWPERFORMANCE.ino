#include "Display.h"
#include "Startup.h"
#include "OBD.h"
#include "Screens.h"

void setup()
{
    Serial.begin(115200);

    Display_Init();

    Startup_Boot();

    Startup_Connecting();

    if(OBD_Init())
    {
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

void loop()
{
    OBD_Update();

    Screens_Update();
}