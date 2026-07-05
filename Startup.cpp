#include "Startup.h"

#include "Display.h"

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
    Display_ShowMessage("Connection Failed");

    delay(2000);
}