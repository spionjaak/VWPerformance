#include "Startup.h"

#include "Display.h"

#include "Config.h"

void Startup_Boot()
{
    Display_ShowLogo();

    delay(1500);
}

void Startup_Connecting()
{
    Display_ShowConnecting();
}

void Startup_Connected()
{
    Display_ShowConnected();

    delay(700);
}

void Startup_Error()
{
    Display_ShowMessage("Connection Failed",COLOR_RED);

    delay(2000);
}