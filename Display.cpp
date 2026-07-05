#include "Display.h"

#include "Config.h"
#include "VehicleData.h"

Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

//====================================
// PRIVATE FUNCTIONS
//====================================

static uint16_t rpmColor = COLOR_GREEN;

static void drawHeader()
{
    tft.setTextColor(COLOR_TEXT);
    tft.setTextSize(2);

    tft.setCursor(10,20);
    tft.print("VW PERFORMANCE");

    tft.drawLine(
        0,
        50,
        SCREEN_WIDTH,
        50,
        COLOR_RED
    );
}

static void drawRPMBar()
{
    tft.fillRect(
        BAR_X,
        BAR_Y,
        SCREEN_WIDTH,
        BAR_SEGMENT_HEIGHT,
        COLOR_BACKGROUND
    );

    int activeSegments =
        map(
            vehicle.rpm,
            0,
            MAX_RPM,
            0,
            BAR_SEGMENTS
        );

    rpmColor = COLOR_GREEN;

    for(int i=0;i<activeSegments;i++)
    {
        if(i < BAR_GREEN_LIMIT)
            rpmColor = COLOR_GREEN;
        else if(i < BAR_YELLOW_LIMIT)
            rpmColor = COLOR_YELLOW;
        else
            rpmColor = COLOR_RED;

        int x =
            BAR_X +
            i*(BAR_SEGMENT_WIDTH+BAR_GAP);

        tft.fillRect(
            x,
            BAR_Y,
            BAR_SEGMENT_WIDTH,
            BAR_SEGMENT_HEIGHT,
            rpmColor
        );
    }
}

static void drawRPMText()
{
    tft.fillRect(
        0,
        110,
        SCREEN_WIDTH,
        45,
        COLOR_BACKGROUND
    );

    tft.setTextSize(5);
    tft.setTextColor(rpmColor);

    tft.setCursor(20,120);
    tft.print(vehicle.rpm);

    tft.setTextSize(2);
    tft.print(" rpm");
}

static void drawInfo()
{
    tft.fillRect(
        0,
        170,
        SCREEN_WIDTH,
        70,
        COLOR_BACKGROUND
    );

    tft.setTextSize(2);
    tft.setTextColor(COLOR_INFO);

    tft.setCursor(20,180);

    if(vehicle.tempValid)
    {
        tft.print("TEMP: ");
        tft.print(vehicle.coolantTemp);
        tft.print(" C");
    }
    else
    {
        tft.print("TEMP: --");
    }

    tft.setCursor(20,210);

    if(vehicle.batteryValid)
    {
        tft.print("BAT: ");
        tft.print(vehicle.batteryVoltage,1);
        tft.print(" V");
    }
    else
    {
        tft.print("BAT: --.-V");
    }
}

//====================================
// PUBLIC FUNCTIONS
//====================================

void Display_Init()
{
    tft.begin();

    tft.setRotation(1);

    tft.fillScreen(COLOR_BACKGROUND);
}

void Display_Clear()
{
    tft.fillScreen(COLOR_BACKGROUND);
}

void Display_ShowLogo()
{
    Display_Clear();

    tft.setTextColor(COLOR_TEXT);

    tft.setTextSize(5);
    tft.setCursor(105,60);
    tft.print("VW");

    tft.setTextSize(3);
    tft.setCursor(45,130);
    tft.print("PERFORMANCE");
}

void Display_ShowConnecting()
{
    Display_ShowLogo();

    tft.setTextSize(2);

    tft.setCursor(85,190);
    tft.print("Connecting...");
}

void Display_ShowConnected()
{
    Display_ShowLogo();

    tft.setTextSize(2);

    tft.setCursor(95,190);
    tft.setTextColor(COLOR_GREEN);
    tft.print("Connected");
}

void Display_ShowMessage(const char* message)
{
    tft.fillRect(
        0,
        190,
        SCREEN_WIDTH,
        30,
        COLOR_BACKGROUND
    );

    tft.setTextSize(2);
    tft.setTextColor(COLOR_TEXT);

    tft.setCursor(20,190);
    tft.print(message);
}

void Display_DrawPerformanceScreen()
{
    Display_Clear();

    drawHeader();

    drawRPMBar();

    drawRPMText();

    drawInfo();
}

void Display_UpdateRPM()
{
    drawRPMBar();
    drawRPMText();
}

void Display_UpdateTemperature()
{
    drawInfo();
}

void Display_UpdateBattery()
{
    drawInfo();
}

void Display_UpdateAll()
{
    drawRPMBar();

    drawRPMText();

    drawInfo();
}