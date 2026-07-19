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
    Display_ShowError();

    delay(2000);
}